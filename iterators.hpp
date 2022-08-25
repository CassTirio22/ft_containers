/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:20:44 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/25 18:13:58 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include "utils.hpp"

namespace ft {

	/*----- All tags of type Iterators -----*/

	class InputIteratorTag {};
	class OutputIteratorTag {};
	class ForwardIteratorTag {};
	class BidirectionalIteratorTag {};
	class RandomAccessIteratorTag {};

	/*----- Iterator traits -----*/

	template <typename T>
	class iterator_traits {
		typedef std::ptrdiff_t				difference_type;
		typedef T*							pointer;
		typedef	T&							reference;
		typedef T							type_value;
		typedef	RandomAccessIteratorTag	iterator_category;
	};

	/*----- My Iterator struct -----*/

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct Iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};


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
		RandomAccessIterator(void) : _ptr(NULL) {}

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


	/*---------- RBT ITERATORS ----------*/

	template<class T, class Node>
	class MapIterator {
	public:

		typedef	T				value_type;

	private:

		Node	*_root;
		Node	*_node;
		Node	*_null_node;

	public:

		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/

		/*----- Const operator -----*/

		operator MapIterator<const T, Node>() const { return (MapIterator<const T, Node>(_node, _null_node, _root)); }

		/*----- Constructors -----*/

		MapIterator(void) : _node(NULL), _null_node(NULL), _root(NULL) {}
		MapIterator(Node *node, Node *null_node, Node *root) : _node(node), _null_node(null_node), _root(root) {}
		MapIterator(const MapIterator &it) : _node(it.getNode()), _null_node(it.getNullNode()), _root(it.getRoot()) {}

		/*----- Assign operator -----*/

		MapIterator	&operator=(const MapIterator &it) {
			_node = it.getNode();
			return (*this);
		}

		/*----- Getters -----*/

		Node	*getNode(void) const { return (_node); }
		Node	*getNullNode(void) const {return (_null_node); }
		Node	*getRoot(void) const {return (_root); }

		/*----- Access operator -----*/

		value_type	&operator*(void) const { return (_node->_data); }

		value_type	*operator->(void) const { return (&_node->_data); }

		/*----- Increment operators -----*/

		MapIterator&	operator++(void) {
			_node = ft_next(_node);
			return (*this);
		}

		MapIterator	operator++(int n) {
			static_cast<void>(n);
			Node	*tmp = _node;
			_node = ft_next(_node);
			return (MapIterator(tmp, _null_node, _root));
		}

		/*----- Decrement operators -----*/

		MapIterator&	operator--(void) {
			if (_node == _null_node) {
				_node = _root;
				while (_node->_right != _null_node)
					_node = _node->_right;
				return (*this);
			}
			_node = ft_prev(_node);
			return (*this);
		}

		MapIterator	operator--(int n) {
			static_cast<void>(n);
			Node	*tmp = _node;
			if (_node == _null_node) {
				_node = _root;
				while (_node->_right != _null_node)
					_node = _node->_right;
				return (MapIterator(tmp, _null_node, _root));
			}
			_node = ft_prev(_node);
			return (MapIterator(tmp, _null_node));
		}

		/*----- Utils -----*/

		Node	*ft_next(Node *node) {
			Node	*tmp;

			if (node->_right == _null_node) {
				if (node->_left == _null_node && node == node->_parent->_right)
					return (_null_node);
				tmp = node;
				while (tmp->_parent != _null_node && tmp == tmp->_parent->_right)
					tmp = tmp->_parent;
				tmp = tmp->_parent;
				return (tmp);
			}
			tmp = node->_right;
			while (tmp->_left != _null_node)
				tmp = tmp->_left;
			return (tmp);
		}

		Node	*ft_prev(Node *node) {		// !!!! SI PREV DU MINIMUN
			Node	*tmp;

			if (node->_left == _null_node) {
				tmp = node;
				while (tmp->_parent != _null_node && tmp == tmp->_parent->_left)
					tmp = tmp->_parent;
				tmp = tmp->_parent;
				return (tmp);
			}
			tmp = node->_left;
			while (tmp->_right != _null_node)
				tmp = tmp->_right;
			return (tmp);
		}
	};
};

#endif
