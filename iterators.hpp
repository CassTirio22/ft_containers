/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:20:44 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/07 17:17:12 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

#include "ft_containers.hpp"

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

		/*----- Copy constructor -----*/

		RandomAccessIterator(const RandomAccessIterator &src) : _ptr(src.base()) {}


		/*----- Assignation operator -----*/

		const RandomAccessIterator &operator=(const RandomAccessIterator &rhs) {
			if (this->_ptr != rhs.base())
				this->_ptr = rhs.base();
			return (*this);
		}


		/*----- Default constructor -----*/

		RandomAccessIterator(void) {
			this->_ptr = NULL;
		}


		/*----- Destructor -----*/

		virtual ~RandomAccessIterator(void) {}


		/*----- Getter of _ptr -----*/

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


		/*----- Equality comparaison -----*/

		bool	operator==(const RandomAccessIterator &rhs) {
			return (this->_ptr == rhs.base());
		}


		/*----- Inequality comparaison -----*/

		bool	operator!=(const RandomAccessIterator &rhs) {
			return (this->_ptr != rhs.base());
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
			RandomAccessIterator	ret(*this);

			ret += n;
			return (ret);
		}

		RandomAccessIterator	operator-(difference_type n) {
			RandomAccessIterator	ret(*this);

			ret -= n;
			return (ret);
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
			RandomAccessIterator ret = this + n;
			return (*ret->base());
		}

	};


	/*----- Relationals operators -----*/
	
	template <typename L_T, typename R_T>
	bool operator==(const ft::RandomAccessIterator<L_T> &lhs, const ft::RandomAccessIterator<R_T> &rhs) {
		return (lhs->base() == rhs->base());
	}

	template <typename L_T, typename R_T>
	bool operator!=(const ft::RandomAccessIterator<L_T> &lhs, const ft::RandomAccessIterator<R_T> &rhs) {
		return (lhs->base() != rhs->base());
	}

	template <typename L_T, typename R_T>
	bool operator>(const ft::RandomAccessIterator<L_T> &lhs, const ft::RandomAccessIterator<R_T> &rhs) {
		return (lhs->base() > rhs->base());
	}

	template <typename L_T, typename R_T>
	bool operator>=(const ft::RandomAccessIterator<L_T> &lhs, const ft::RandomAccessIterator<R_T> &rhs) {
		return (lhs->base() >= rhs->base());
	}

	template <typename L_T, typename R_T>
	bool operator<(const ft::RandomAccessIterator<L_T> &lhs, const ft::RandomAccessIterator<R_T> &rhs) {
		return (lhs->base() < rhs->base());
	}

	template <typename L_T, typename R_T>
	bool operator<=(const ft::RandomAccessIterator<L_T> &lhs, const ft::RandomAccessIterator<R_T> &rhs) {
		return (lhs->base() <= rhs->base());
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

		/*----- Default constructor -----*/

		ReverseIterator(void) : _it() {}
		

		/*----- Parameter constructor -----*/

		ReverseIterator(iterator_type it) : _it(it) {}


		/*----- Copy constructor -----*/

		ReverseIterator(const ReverseIterator<iterator_type> &src) : _it(src.base()) {}


		/*----- Destructor -----*/

		~ReverseIterator(void) {}


		/*----- Getter of _it -----*/

		iterator_type	base(void) const { return (this->_it); }


		/*----- Dereference operator -----*/

		reference	operator*(void) const {
			iterator_type	ret = this->_it;
			return (*(--ret));
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

		reference	operator[](difference_type n) const { return (*(this->_it + n)); }
	};

	/*----- Relational == operator -----*/

	template <typename L_I, typename R_I>
	bool	operator==(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() == rhs.base()); }


	/*----- Relational != operator -----*/
	
	template <typename L_I, typename R_I>
	bool	operator!=(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() != rhs.base()); }
	
	
	/*----- Relational < operator -----*/

	template <typename L_I, typename R_I>
	bool	operator<(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() < rhs.base()); }


	/*----- Relational <= operator -----*/

	template <typename L_I, typename R_I>
	bool	operator<=(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() <= rhs.base()); }


	/*----- Relational > operator -----*/
	
	template <typename L_I, typename R_I>
	bool	operator>(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() > rhs.base()); }


	/*----- Relational >= operator -----*/

	template <typename L_I, typename R_I>
	bool	operator>=(const ReverseIterator<L_I> &lhs, const ReverseIterator<R_I> &rhs) { return (lhs.base() >= rhs.base()); }


	/*----- Subtraction operator -----*/

	template <typename Iterator>
	const ReverseIterator<Iterator> operator-(typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator> &x){ return (ReverseIterator<Iterator>(x.base() - n)); }


	/*----- Addition operator -----*/

	template <typename Iterator>
	const ReverseIterator<Iterator> operator+(typename ReverseIterator<Iterator>::difference_type n, const ReverseIterator<Iterator> &x){ return (ReverseIterator<Iterator>(x.base() + n)); }	

};

#endif