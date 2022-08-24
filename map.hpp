/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:04:47 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/24 18:51:06 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define  MAP_HPP

# include <functional>
# include "pair.hpp"
# include "iterators.hpp"
# include "rbt.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:

		typedef	Key															key_type;
		typedef	T															mapped_type;
		typedef	size_t														size_type;
		typedef	ft::pair<const Key, T>										value_type;
		typedef	Compare														key_compare;
		typedef	Alloc														allocator_type;
		typedef	value_type*													pointer;
		typedef	value_type&													reference;
		typedef	const value_type*											const_pointer;
		typedef	const value_type&											const_reference;
		typedef	ft::MapIterator<value_type, ft::Node<const Key, T> >		iterator;
		typedef	ft::MapIterator<const value_type, ft::Node<const Key, T> >	const_iterator;
		typedef	ft::ReverseIterator<iterator>								reverse_iterator;
		typedef	ft::ReverseIterator<const_iterator>							const_reverse_iterator;
		typedef	ft::rbTree<Key, T>											rbt_type;

	private:

		rbt_type		_rbt;
		size_type		_size;
		key_compare		_comp;
		allocator_type	_alloc;

	public:

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructors -----*/

		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _comp(comp), _alloc(alloc), _rbt(rbt_type()), _size(0) {}

		/*----- Getter -----*/

		rbt_type	getRbt(void) const { return (_rbt); }


		/*----- Iterators -----*/

		iterator	begin(void) { return(iterator(_rbt.minimum(_rbt.getRoot()), _rbt.getNullNode(), _rbt.getRoot())); }

		const_iterator	begin(void) const { return(const_iterator(_rbt.minimum(_rbt.getRoot()), _rbt.getNullNode(), _rbt.getRoot())); }

		iterator	end(void) { return(iterator(_rbt.getNullNode(), _rbt.getNullNode(), _rbt.getRoot())); }

		const_iterator	end(void) const { return(const_iterator(_rbt.getNullNode(), _rbt.getNullNode(), _rbt.getRoot()));}

		reverse_iterator	rbegin(void) {}

		const_reverse_iterator	rbegin(void) const {}

		reverse_iterator	rend(void) {}

		const_reverse_iterator	rend(void) const {}

		/*----- Capacity -----*/

		bool	empty(void) const { return (!_size); }

		size_type	size(void) const { return (_size); }

		size_type	max_size(void) { return (_rbt._node_alloc.max_size()); }

		/*----- Element access -----*/

		T	&operator[](const Key &key) {
			return ((_rbt.findNode(key))->_data._second);
		}

		/*----- Modifiers -----*/

		ft::pair<iterator, bool>	insert(const value_type &value) {
			ft::pair<Node<const Key, T> *, bool>	ret = _rbt.insert(_rbt.getRoot(), value);
			iterator	it(ret._first, _rbt.getNullNode(), _rbt.getRoot());
			if (ret._second)
				_size++;
			return (ft::make_pair<iterator, bool>(it, ret._second));
		}

		iterator	insert(iterator position, const value_type &val) {
			static_cast<void>(position);
			return (insert(val)._first);
		}

		template <class InputIt>
		void	insert(InputIt first, InputIt last) {
			while (first != last) {
				insert(*first);
				first++;
			}
		}

		void	erase(iterator pos) {
			erase(pos.getNode()->_data._first);
		}

		void	erase(iterator first, iterator last) {
			for (; first != last; first++)
				erase(first);
		}

		size_type	erase(const key_type &key) {
			if (!_size)
				return (0);
			Node<const Key, T>	*node = _rbt.findNode(key);
			if (node->_data._first != key)
				return (0);
			_size--;
			_rbt.deleteNode(node->_data._first);
			return (1);
		}

		void	swap(map &x) {
			size_type	sizeTmp = x._size;

			_rbt.swap(x._rbt);
			x._size = _size;
			_size = sizeTmp;
		}

		void	clear(void) {
			_rbt.destroyRbt(_rbt.getRoot());
			_rbt.setRoot(_rbt.getNullNode());
		}

		/*----- Observers -----*/

		key_compare	key_comp(void) const { return (_rbt.getKeyCompare()); }
		
		/*----- Operations -----*/

		iterator	find(const key_type	&k) { return (iterator(_rbt.findNode(k), _rbt.getNullNode())); }

		const_iterator	find(const key_type &k) const { return (const_iterator(_rbt.findNode(k), _rbt.getNullNode())); }

		size_type	count(const key_type &k) const {
			if (k == _rbt.findNode(k)->_data._first)
				return (1);
			return (0);
		}

		// iterator	lower_bound(const key_type &k) const {}

		// const_iterator	lower_bound(const key_type &k) const {}

		// iterator	upper_bound(const key_type &k) const {}

		// const_iterator	upper_bound(const key_type &k) const {}

		// ft::pair<const_iterator, const_iterator>	equal_range(const key_type &k) const {}

		// ft::pair<iterator, iterator>	equal_range(const key_type &k) {}

		/*----- Allocator -----*/

		allocator_type	get_allocator(void) const { return (_alloc); }

		/*----- Utils -----*/

		void	affRbt(void) const { _rbt.aff_tree(_rbt.getRoot(), 0); }

		void	affNode(Node<const Key, T> *node) const { _rbt.aff_node(node); }
		
		Node<const Key, T>	*getRoot(void) const { return (_rbt.getRoot()); }
	};

	/*---------- NON-MEMBER FUNCTIONS ----------*/

	// template<class Key, class T, class Compare, class Alloc>
	// bool	operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		
	// }

	// template<class Key, class T, class Compare, class Alloc>
	// bool	operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		
	// }

	// template<class Key, class T, class Compare, class Alloc>
	// bool	operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		
	// }

	// template<class Key, class T, class Compare, class Alloc>
	// bool	operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		
	// }

	// template<class Key, class T, class Compare, class Alloc>
	// bool	operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		
	// }

	// template<class Key, class T, class Compare, class Alloc>
	// bool	operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		
	// }

}

#endif
