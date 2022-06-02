/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:20:44 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/02 16:40:11 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <cstddef>

namespace ft {

	// My Iterator struct
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct Iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	// All tags of type Iterators
	class BasicIteratorTag {};
	class InputIteratorTag {};
	class OutputIteratorTag {};
	class ForwardIteratorTag {};
	class BidirectionalIteratorTag {};
	class RandomAccessIteratorTag {};

	// BasicIterator
	template <typename T>
	class BasicIterator : public ft::Iterator<ft::BasicIteratorTag, T> {
	public:
		typedef typename ft::Iterator<ft::BasicIteratorTag, T>::value_type value_type;
		typedef typename ft::Iterator<ft::BasicIteratorTag, T>::difference_type difference_type;
		typedef typename ft::Iterator<ft::BasicIteratorTag, T>::pointer pointer;
		typedef typename ft::Iterator<ft::BasicIteratorTag, T>::reference reference;
		typedef typename ft::Iterator<ft::BasicIteratorTag, T>::iterator_category iterator_category;


		// Copy constructor
		BasicIterator(const BasicIterator &src) : _ptr(src.getPtr()) {}

		// Assignation operator
		const BasicIterator &operator=(const BasicIterator &rhs) {
			if (this->_ptr != rhs.getPtr())
				this->_ptr = rhs.getPtr();
			return (*this);
		}

		// Destructor
		virtual ~BasicIterator(void) {}

		// Getter of _ptr
		pointer	getPtr(void) const { return (this->_ptr); }

		// Pre increment operator
		BasicIterator	&operator++(void) {
			this->_ptr++;
			return (*this);
		}

		// Post increment operator
		BasicIterator	operator++(int n) {
			static_cast<void>(n);
			BasicIterator ret(*this);

			this->_ptr++;
			return (ret);
		}

	protected:
		pointer	_ptr;
	};

	// Input iterator
	template <typename T>
	class InputIterator : public virtual ft::BasicIterator<T> {
	public:
		typedef typename ft::Iterator<ft::InputIteratorTag, T>::value_type value_type;
		typedef typename ft::Iterator<ft::InputIteratorTag, T>::difference_type difference_type;
		typedef typename ft::Iterator<ft::InputIteratorTag, T>::pointer pointer;
		typedef typename ft::Iterator<ft::InputIteratorTag, T>::reference reference;
		typedef typename ft::Iterator<ft::InputIteratorTag, T>::iterator_category iterator_category;

		// Equality comparaison
		bool	operator==(const InputIterator &rhs) {
			return (this->_ptr == rhs.getPtr())
		}

		// Inequality comparaison
		bool	operator!=(const InputIterator &rhs) {
			return (this->_ptr != rhs.getPtr())
		}

		// Dereference as rvalue
		const reference	operator*(void) const { return (*this->_ptr); }
		const pointer	operator->(void) const { return (this->_ptr); }

	};
	
	// Output iterator
	template <typename T>
	class OutputIterator : public virtual ft::BasicIterator<T> {
	public:
		typedef typename ft::Iterator<ft::OutputIteratorTag, T>::value_type value_type;
		typedef typename ft::Iterator<ft::OutputIteratorTag, T>::difference_type difference_type;
		typedef typename ft::Iterator<ft::OutputIteratorTag, T>::pointer pointer;
		typedef typename ft::Iterator<ft::OutputIteratorTag, T>::reference reference;
		typedef typename ft::Iterator<ft::OutputIteratorTag, T>::iterator_category iterator_category;

		// Dereference as lvalue
		reference	operator*(void) const { return (*this->_ptr); }
		pointer		operator->(void) const { return (this->_ptr); }
	};

	// Forward iterator
	template <typename T>
	class ForwardIterator : public ft::Iterator<ForwardIteratorTag, T>, public ft::InputIterator<T>, public ft::OutputIterator<T> {
	public:
		typedef typename ft::Iterator<ft::ForwardIteratorTag, T>::value_type value_type;
		typedef typename ft::Iterator<ft::ForwardIteratorTag, T>::difference_type difference_type;
		typedef typename ft::Iterator<ft::ForwardIteratorTag, T>::pointer pointer;
		typedef typename ft::Iterator<ft::ForwardIteratorTag, T>::reference reference;
		typedef typename ft::Iterator<ft::ForwardIteratorTag, T>::iterator_category iterator_category;

		// Default constructor
		ForwardIterator(void) {
			this->_ptr = NULL;
		}
	};

	// Bidirectional iterator
	template <typename T>
	class BidirectionalIterator : public ft::Iterator<BidirectionalIteratorTag, T>, public ft::ForwardIterator<T> {
	public:
		typedef typename ft::Iterator<ft::BidirectionalIteratorTag, T>::value_type value_type;
		typedef typename ft::Iterator<ft::BidirectionalIteratorTag, T>::difference_type difference_type;
		typedef typename ft::Iterator<ft::BidirectionalIteratorTag, T>::pointer pointer;
		typedef typename ft::Iterator<ft::BidirectionalIteratorTag, T>::reference reference;
		typedef typename ft::Iterator<ft::BidirectionalIteratorTag, T>::iterator_category iterator_category;

		// Pre decrement operator
		BidirectionalIterator	&operator--(void) {
			this->_ptr--;
			return (*this);
		}

		// Post decrement operator
		BidirectionalIterator	operator--(int n) {
			static_cast<void>(n);
			BidirectionalIterator ret(*this);

			this->_ptr--;
			return (ret);
		}
	};

	// Random access iterator
	template <typename T>
	class RandomAccessIterator : public ft::Iterator<RandomAccessIteratorTag, T>, public ft::BidirectionalIterator<T> {
	public:
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::value_type value_type;
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::difference_type difference_type;
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::pointer pointer;
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::reference reference;
		typedef typename ft::Iterator<ft::RandomAccessIteratorTag, T>::iterator_category iterator_category;

		// Arithmetic + and - operators
		const RandomAccessIterator	operator+(difference_type n) const {
			RandomAccessIterator	ret(*this);

			ret += n;
			return (ret);
		}

		const RandomAccessIterator	operator+(difference_type n, RandomAccessIterator x) const {
			x += n;
			return (x);
		}

		const RandomAccessIterator	operator-(difference_type n) const {
			RandomAccessIterator	ret(*this);

			ret -= n;
			return (ret);
		}

		const RandomAccessIterator	operator-(difference_type n, RandomAccessIterator x) const {
			x -= n;
			return (x);
		}
	}
};

#endif