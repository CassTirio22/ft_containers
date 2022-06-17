/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:07:28 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/17 17:05:21 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_containers.hpp"

namespace ft {

	template <class value_type, class allocator_type = std::allocator<value_type> >
	class vector {
	public:
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		typedef typename ft::RandomAccessIterator<value_type>		iterator;
		typedef	typename ft::RandomAccessIterator<const value_type>	const_iterator;
		typedef	typename ft::ReverseIterator<iterator>				reverse_iterator;
		typedef	typename ft::ReverseIterator<const_iterator>		const_reverse_iterator;

	private:

		/*----- Allocator -----*/

		allocator_type _alloc;

		/*----- Max capacity -----*/

		size_type	_capacity;

		/*----- Actual size -----*/

		size_type	_size;

		/*----- Value -----*/

		pointer	_value;

	public:

		/*----- Constructors -----*/

		explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _capacity(0), _size(0) {
			this->_value = this->_alloc.allocate(0);
		}

		explicit vector(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _capacity(n), _size(n) {
			if (n < 0)
				throw (std::out_of_range("Capacity must be positif"));
			this->_value = this->_alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(&this->_value[i], value);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _alloc(alloc), _size(0) {
			InputIterator tmp = first;
			while (tmp++ != last)
				this->_size++;
			this->_capacity = this->_size;
			this->_value = this->_alloc.allocate(this->_size);
			for (size_type i = 0; i < this->_size; i++) {
				this->_alloc.construct(&this->_value[i], *first);
				first++;
			}
		}

		vector(const vector &src) : _alloc(src.get_allocator()), _capacity(src.capacity()), _size(src.size()) {
			this->_value = this->_alloc.allocate(this->_size);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&this->_value[i], src.get_value()[i]);
		}

		vector	&operator=(const vector &v) {
			this->_alloc = v.get_allocator();
			this->_capacity = v.capacity();
			this->_size = v.size();
			this->_value = this->_alloc.allocate(this->_capacity);

			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&this->_value[i], v.get_value()[i]);
			return (*this);
		}

		/*----- Destructor -----*/

		~vector(void) {
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&this->_value[i]);
			this->_alloc.deallocate(this->_value, this->_capacity);
		}

		/*----- Getter -----*/

		allocator_type	get_allocator(void) const { return (this->_alloc); }
		pointer			get_value(void) const { return (this->_value); }

		/*----- Setter -----*/

		void	set_allocator(allocator_type alloc) { this->_alloc = alloc; }
		void	set_size(size_type size) { this->_size = size; }
		void	set_capacity(size_type capacity) { this->_capacity = capacity; }
		void	set_value(pointer p) { this->_value = p; }

		/*----- Iterators -----*/

		iterator	begin(void) { return (this->_value); }

		const_iterator	begin(void) const { return (const_iterator(this->_value)); }

		iterator	end(void) { return (iterator(this->_value + this->_size)); }

		const_iterator	end(void) const { return (const_iterator(this->_value + this->_size)); }

		reverse_iterator	rbegin(void) { return (reverse_iterator(this->_value + this->_size)); }

		const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(this->_value + this->_size)); }

		reverse_iterator	rend(void) { return (reverse_iterator(this->_value)); }

		const_reverse_iterator	rend(void) const { return (const_reverse_iterator(this->_value)); }

		/*----- Capacity -----*/

		size_type	size(void) const { return (this->_size); }

		size_type	max_size(void) const { return (this->_alloc.max_size()); }

		void	resize(size_type n, value_type val = value_type()) {
			if (n < this->_size)
				while (n < this->_size)
					this->_alloc.destroy(&this->_value[this->_size--]);
			else if (n > this->_size && n > this->_capacity)
				this->reserve(n);
			if (n > this->_size)
				while (this->_size < n)
					this->_alloc.construct(&this->_value[this->_size++], val);
		}

		size_type	capacity(void) const { return (this->_capacity); }

		bool empty(void) const { return (!this->_size); }

		void	reserve(size_type n) {
			if (n > this->max_size())
				throw (std::out_of_range("vector: out of range"));
			if (n < this->_capacity)
				return ;

			pointer old_value = this->_value;
			this->_value = this->_alloc.allocate(n);
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(&this->_value[i], old_value[i]);
			for	(size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&old_value[i]);
			this->_alloc.deallocate(old_value, this->_capacity);
			this->_capacity = n;

		}

		/*----- Element access -----*/

		reference	operator[](size_type pos) {
			if (pos >= this->_size || pos < 0)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[pos]);
		}

		const_reference	operator[](size_type pos) const {
			if (pos >= this->_size || pos < 0)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[pos]);
		}

		reference	at(size_type pos) {
			if (pos >= this->_size || pos < 0)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[pos]);
		}

		const_reference	at(size_type pos) const {
			if (pos >= this->_size || pos < 0)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[pos]);
		}

		reference	front(void) {
			if (!this->_size)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[0]);
		}

		const_reference	front(void) const {
			if (!this->_size)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[0]);
		}

		reference	back(void) {
			if (!this->_size)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[this->_size - 1]);
		}

		const_reference	back(void) const {
			if (!this->_size)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[this->_size - 1]);
		}

		/*----- Modifiers -----*/

		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
			size_type	i = 0;
			InputIterator tmp = first;
			while (tmp++ != last)
				i++;
			this->resize(0);
			this->reserve(i);
			this->_size = i;
			i = 0;
			while (first != last) {
				this->_alloc.construct(&this->_value[i], *first);
				i++;
				first++;
			}
		}

		void	assign(size_type n, const_reference val) {
			this->resize(0);
			this->reserve(n);
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(&this->_value[i], val);
			this->_size = n;
		}

		void push_back(const_reference val) {
			if (this->_size == this->_capacity)
				this->reserve((!this->_size) ? 1 : 2 * this->_size);
			this->_alloc.construct(&this->_value[this->_size], val);
			this->_size++;
		}

		void	pop_back(void) {
			if (!this->_size)
				return ;
			this->_alloc.destroy(&this->_value[--this->_size]);
		}

		iterator	insert(iterator position, const_reference val) {
			size_type	pos = 0;
			size_type	end = this->_size;

			for (; pos <= this->_size; pos++)
				if (&*position == &this->_value[pos])
					break ;
			if (pos == this->_size && position != this->end())
				return (iterator());
			this->_size++;
			this->reserve(this->_size);
			while (pos < end) {
				this->_value[end] = this->_value[end - 1];
				end--;
			}
			this->_alloc.construct(&this->_value[end], val);
			return (iterator(&this->_value[pos]));
		}

		void	insert(iterator position, size_type n, const_reference val) {
			size_type	pos = 0;

			for (; pos <= this->_size; pos++) {
				if (&*position == &this->_value[pos])
					break ;
			}
			if (pos == this->_size && position != this->end())
				return ;
			this->_size += n;
			this->reserve(this->_size);
			for (size_type i = 0; i < this->_size - n - pos; i++)
				this->_value[this->_size - i - 1] = this->_value[this->_size - n - i - 1];
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(&this->_value[pos + i], val);
		}

		template <class InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
			size_type	n = 0;
			InputIterator tmp = first;
			while (tmp++ != last)
				n++;
			size_type pos = 0;
			for (; pos <= this->_size; pos++)
				if (&*position == &this->_value[pos])
					break ;
			if (pos == this->_size && position != this->end())
				return ;
			this->_size += n;
			this->reserve(this->_size);
			for (size_type i = 0; i < this->_size - n - pos; i++)
				this->_value[this->_size - i - 1] = this->_value[this->_size - n - i - 1];
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(&this->_value[pos + i], *first++);
		}

		iterator	erase(iterator position) {
			size_type	pos = 0;

			for (; pos <= this->_size; pos++)
				if (&*position == &this->_value[pos])
					break ;
			if (pos == this->_size)
				return (iterator());
			this->_alloc.destroy(&this->_value[pos]);
			size_type	tmp = pos;
			while (tmp < this->_size) {
				this->_value[tmp] = this->_value[tmp + 1];
				tmp++;
			}
			this->_size--;
			return (&this->_value[pos]);
		}

		iterator	erase(iterator first, iterator last) {
			size_type	pos = 0;
			size_type	len = 0;
			for (; pos <= this->_size; pos++)
				if (&*first == &this->_value[pos])
					break ;
			if (pos == this->_size)
				return (iterator());
			iterator tmp = first;
			while (tmp++ != last)
				len++;
			for (size_type i = 0; i < this->_size - len - pos; i++) {
				this->_alloc.destroy(&this->_value[pos + i]);
				this->_value[pos + i] = this->_value[pos + i + len];
			}
			this->_size -= len;
			return (first);
		}

		void	swap(vector &x) {

			allocator_type	alloc_tmp = x.get_allocator();
			size_type		capacity_tmp = x.capacity();
			size_type		size_tmp = x.size();
			pointer			value_tmp = x.begin().base();

			x.set_allocator(this->_alloc);
			x.set_capacity(this->_capacity);
			x.set_size(this->_size);
			x.set_value(this->begin().base());

			this->set_allocator(alloc_tmp);
			this->set_capacity(capacity_tmp);
			this->set_size(size_tmp);
			this->set_value(value_tmp);
		}

		void	clear(void) {
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.destroy(&this->_value[i]);
			this->_size = 0;
		}
	};

	/*----- NON MEMBER FONCTION -----*/

	/*----- Relational operator -----*/

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (false);
		return (true);
	}


	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return (true);
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); i++) {
			if (lhs[i] > rhs[i])
				return (false);
			else if (lhs[i] < rhs[i])
				return (true);
		}
		if (lhs.size() < rhs.size())
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size() && i < rhs.size(); i++) {
			if (lhs[i] < rhs[i])
				return (false);
			else if (lhs[i] > rhs[i])
				return (true);
		}
		if (lhs.size() > rhs.size())
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		if (lhs == rhs || lhs < rhs)
			return (true);
		return (false);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		if (lhs == rhs || lhs > rhs)
			return (true);
		return (false);
	}
};

#endif
