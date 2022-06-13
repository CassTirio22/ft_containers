/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:07:28 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/13 16:40:12 by ctirions         ###   ########.fr       */
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

		typedef ft::RandomAccessIterator<value_type>		iterator;
		typedef	ft::RandomAccessIterator<const value_type>	const_iterator;
		typedef	ft::ReverseIterator<value_type>				reverse_iterator;
		typedef	ft::ReverseIterator<const value_type>		const_reverse_iterator;

	private:

		/*----- Allocator -----*/

		allocator_type _alloc;

		/*----- Max capacity -----*/

		size_type	_capacity;

		/*----- Actual size -----*/

		size_type	_size;

		/*----- Value -----*/

		value_type	*_value;

	public:

		/*----- Constructors -----*/

		explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _capacity(0), _size(0) {
			this->_value = this->_alloc.allocate(0);
		}

		explicit vector(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _capacity(n), _size(n) {
			if (n < 0)
				throw (std::out_of_range("Capacity must be positif"));
			this->_value = this->_alloc.allocate(n);
			for (int i = 0; i < n; i++)
				this->_alloc.construct(&this->_value[i], value);
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) {
			if (first > last)
				throw (std::out_of_range("<first> iterator must be lower than <last> iterator"));
			while (first++ != last)
				this->_size++;
			this->_capacity = this->_size;
			first -= size;
			this->_value = this->_alloc.allocate(this->_size);
			for (int i = 0; i < this->_size; i++) {
				this->_alloc.construct(&this->_value[i], *first);
				first++;
			}
		}

		vector(const vector &src) : _alloc(src.get_allocator()), _size(src.size()), _capacity(src.capacity()) {
			this->_value = this->_alloc.allocate(this->_size);
			for (int i = 0; i < this->_size; i++)
				this->_alloc.construct(&this->_value[i], src.value()[i]);
		}

		/*----- Destructor -----*/

		~vector(void) {
			for (int i = 0; i < this->_size; i++)
				this->_alloc.destroy(&this->_value[i]);
			this->_alloc.deallocate(this->_value, this->_size);
		}

		/*----- Iterators -----*/

		iterator	begin(void) { return (iterator(this->_value)); }

		const_iterator	begin(void) const { return (const_iterator(this->_value)); }

		iterator	end(void) { return (iterator(this->_value + this->_size)); }

		const_iterator	end(void) { return (const_iterator(this->_value + this->_size)); }

		reverse_iterator	rbegin(void) { return (reverse_iterator(this->_value + this->_size)); }

		const_reverse_iterator	rbegin(void) { return (const_reverse_iterator(this->_value + this->_size)); }

		reverse_iterator	rend(void) { return (reverse_iterator(this->_value)); }

		const_reverse_iterator	rend(void) { return (const_reverse_iterator(this->_value)); }

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
			for (int i = 0; i < this->_size; i++)
				this->_alloc.construct(&this->_value[i], old_value[i]);
			for	(int i = 0; i < this->_size; i++)
				this->_alloc.destroy(&old_value[i]);
			this->_alloc.deallocate(old_value, this->_capacity);
			this->_capacity = n;

		}

		/*----- Element access -----*/

		reference	operator[](size_type pos) const {
			if (pos > this->_size || pos < 0)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[pos]);
		}

		const_reference	operator[](size_type pos) const {
			if (pos > this->_size || pos < 0)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[pos]);
		}

		reference	at(size_type pos) const {
			if (pos > this->_size || pos < 0)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[pos]);
		}

		const_reference	at(size_type pos) const {
			if (pos > this->_size || pos < 0)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[pos]);
		}

		reference	front(void) const {
			if (!this->_size)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[0]);
		}

		const_reference	front(void) const {
			if (!this->_size)
				throw (std::out_of_range("vector: out of range"));
			return (this->_value[0]);
		}

		reference	back(void) const {
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
		void	assign(InputIterator first, InputIterator last) {
			int	i = 0;
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
			for (int i = 0; i < n; i++)
				this->_alloc.construct(&this->_value[i], val);
			this->_size = n;
		}

		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
	};

}

#endif
