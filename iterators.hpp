/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:20:44 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/20 16:37:46 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include "utils.hpp"

namespace ft {

	/*----- My Iterator struct -----*/

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct Iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	/*----- All tags of type Iterators -----*/

	class InputIteratorTag {};
	class OutputIteratorTag {};
	class ForwardIteratorTag {};
	class BidirectionalIteratorTag {};
	class RandomAccessIteratorTag {};


	/*---------- RANDOM ACCESS ITERATORS ----------*/

	template <typename T>
	class RandomAccessIterator : public ft::Iterator<ft::RandomAccessIteratorTag, T> {

	public:
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::value_type value_type;
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::difference_type difference_type;
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::pointer pointer;
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::reference reference;
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::iterator_category iterator_category;

	private:
		pointer	_ptr;

	public:

		/*----- Constructors -----*/

		RandomAccessIterator(const RandomAccessIterator &src) : _ptr(src.base()) {}
		RandomAccessIterator(pointer p) : _ptr(p) {}
		RandomAccessIterator(void) { this->_ptr = NULL; }

		/*----- Destructor -----*/

		virtual ~RandomAccessIterator(void) {}

		/*----- Assignation operator -----*/

		const RandomAccessIterator &operator=(const RandomAccessIterator &rhs) {
			if (this->_ptr != rhs.base())
				this->_ptr = rhs.base();
			return (*this);
		}

		operator RandomAccessIterator<const T>(void) const { return (this->_ptr); }

		/*----- Base -----*/

		pointer	base(void) const { return (this->_ptr); }

		/*----- Pre increment operator -----*/

		RandomAccessIterator	&operator++(void) {
			this->_ptr++;
			return (*this);
		}

		/*----- Post increment operator -----*/

		RandomAccessIterator	operator++(int n) {
			static_cast<void>(n);
			RandomAccessIterator ret(*this);

			this->_ptr++;
			return (ret);
		}

		/*----- Dereferenced value -----*/

		reference	operator*(void) const { return (*this->_ptr); }
		pointer		operator->(void) const { return (this->_ptr); }

		/*----- Pre decrement operator -----*/

		RandomAccessIterator	&operator--(void) {
			this->_ptr--;
			return (*this);
		}

		/*----- Post decrement operator -----*/

		RandomAccessIterator	operator--(int n) {
			static_cast<void>(n);
			RandomAccessIterator ret(*this);

			this->_ptr--;
			return (ret);
		}

		/*----- Arithmetic + and - operators -----*/

		RandomAccessIterator	operator+(difference_type n) {
			return (this->base() + n);
		}

		RandomAccessIterator	operator-(difference_type n) const {
			return (this->base() - n);
		}

		/*----- Operator += -----*/

		RandomAccessIterator	&operator+=(difference_type n) {
			this->_ptr += n;
			return (*this);
		}

		/*----- Operator -= -----*/

		RandomAccessIterator	&operator-=(difference_type n) {
			this->_ptr -= n;
			return (*this);
		}

		/*----- Offset dereference operator -----*/

		reference	operator[](difference_type n) const {
			return (*(this->_ptr + n));
		}

	};

	/*----- Relationals operators -----*/

	template <class L_T, class R_T>
	bool operator==(const RandomAccessIterator<L_T> &lhs, const RandomAccessIterator<R_T> &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename L_T, typename R_T>
	bool operator!=(const RandomAccessIterator<L_T> &lhs, const RandomAccessIterator<R_T> &rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename L_T, typename R_T>
	bool operator>(const RandomAccessIterator<L_T> &lhs, const RandomAccessIterator<R_T> &rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename L_T, typename R_T>
	bool operator>=(const RandomAccessIterator<L_T> &lhs, const RandomAccessIterator<R_T> &rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename L_T, typename R_T>
	bool operator<(const RandomAccessIterator<L_T> &lhs, const RandomAccessIterator<R_T> &rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename L_T, typename R_T>
	bool operator<=(const RandomAccessIterator<L_T> &lhs, const RandomAccessIterator<R_T> &rhs) {
		return (lhs.base() <= rhs.base());
	}

	/*----- Subtraction operator -----*/

	template <typename L_T, typename R_T>
	typename RandomAccessIterator<L_T>::difference_type	operator-(const RandomAccessIterator<L_T> &lhs, const RandomAccessIterator<R_T> &rhs) {
		return (lhs.base() - rhs.base());
	}

	template <class Iterator>
	RandomAccessIterator<Iterator> operator-(typename RandomAccessIterator<Iterator>::difference_type n, const RandomAccessIterator<Iterator> &x) {
		return (RandomAccessIterator<Iterator>(x.base() - n));
	}

	/*----- Addition operator -----*/

	template <class Iterator>
	RandomAccessIterator<Iterator> operator+(typename RandomAccessIterator<Iterator>::difference_type n, const RandomAccessIterator<Iterator> &x) {
		return (RandomAccessIterator<Iterator>(x.base() + n));
	}


	/*---------- REVERSE ITERATORS ----------*/

	template <class Iterator>
	class ReverseIterator {
	public:
		typedef Iterator 											iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;

	private:
		iterator_type	_it;

	public:

		/*----- Constructors -----*/

		ReverseIterator(void) : _it() {}
		explicit ReverseIterator(iterator_type it) : _it(it) {}
		ReverseIterator(pointer	p) : _it(iterator_type(p)) {}
		template <class Iter>
		ReverseIterator(const ReverseIterator<Iter> &src) : _it(src.base()) {}

		/*----- Destructor -----*/

		~ReverseIterator(void) {}

		/*----- Base -----*/

		iterator_type	base(void) const { return (this->_it); }

		/*----- Assignation operator -----*/

		const ReverseIterator<iterator_type> &operator=(const ReverseIterator<iterator_type> &it) {
			this->_it = it.base();
			return (*this);
		}

		/*----- Const operator -----*/

		operator ReverseIterator<const iterator_type>(void) const { return (this->_it); }

		/*----- Dereference operator -----*/

		reference	operator*(void) const {
			iterator_type	ret = this->_it;
			ret--;
			return (*ret);
		}

		/*----- Pointer to the value -----*/

		pointer	operator->(void) const { return (&this->operator*()); }

		/*----- Pre increment operator -----*/

		ReverseIterator	&operator++(void) {
			this->_it--;
			return (*this);
		}

		/*----- Post increment operator -----*/

		ReverseIterator	operator++(int n) {
			static_cast<void>(n);
			ReverseIterator	ret = *this;
			this->_it--;
			return (ret);
		}

		/*----- Pre decrement operator -----*/

		ReverseIterator	&operator--(void) {
			this->_it++;
			return (*this);
		}

		/*----- Post decrement operator -----*/

		ReverseIterator	operator--(int n) {
			static_cast<void>(n);
			ReverseIterator	ret = *this;

			this->_it++;
			return (ret);
		}

		/*----- Arithmetic + operator -----*/

		ReverseIterator	operator+(difference_type n) { return (ReverseIterator(this->_it - n)); }

		/*----- Arithmetic - operator -----*/

		ReverseIterator operator-(difference_type n) { return (ReverseIterator(this->_it + n)); }

		/*----- Arithmetic += operator -----*/

		ReverseIterator	&operator+=(difference_type n) {
			this->_it -= n;
			return (*this);
		}

		/*----- Arithmetic -= operator -----*/

		ReverseIterator	&operator-=(difference_type n) {
			this->_it += n;
			return (*this);
		}

		/*----- Dereference [] operator -----*/

		reference	operator[](difference_type n) const { return (this->_it[-n - 1]); }
	};

	/*----- Relational == operator -----*/

	template <typename L_I, typename R_I>
	bool	operator==(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() == rhs.base()); }

	/*----- Relational != operator -----*/

	template <typename L_I, typename R_I>
	bool	operator!=(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() != rhs.base()); }

	/*----- Relational < operator -----*/

	template <typename L_I, typename R_I>
	bool	operator<(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() > rhs.base()); }

	/*----- Relational <= operator -----*/

	template <typename L_I, typename R_I>
	bool	operator<=(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() >= rhs.base()); }

	/*----- Relational > operator -----*/

	template <typename L_I, typename R_I>
	bool	operator>(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() < rhs.base()); }

	/*----- Relational >= operator -----*/

	template <typename L_I, typename R_I>
	bool	operator>=(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() <= rhs.base()); }

	/*----- Subtraction operator -----*/

	template <class Iterator>
	ReverseIterator<Iterator> operator-(typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator> &x){ return (ReverseIterator<Iterator>(x.base() + n)); }

	template <typename L_T, typename R_T>
	typename ReverseIterator<L_T>::difference_type	operator-(const ReverseIterator<L_T> &lhs, const ReverseIterator<R_T> &rhs) {
		return (rhs.base() - lhs.base());
	}

	/*----- Addition operator -----*/

	template <class Iterator>
	ReverseIterator<Iterator> operator+(typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator> &x){ return (ReverseIterator<Iterator>(x.base() - n)); }

};

#endif
