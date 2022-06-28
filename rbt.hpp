/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:54:12 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/28 18:59:04 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

# include "pair.hpp"
# include <functional>
# include <memory>

namespace ft {

	enum rbTreeColor { _red = false, _black = true };

	template <class Key, class T>
	struct Node {
		ft::pair<const Key, T>	_data;
		Node					*_left;
		Node					*_right;
		Node					*_parent;
	};

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<Key, T> >, class Node = Node<const Key, T> >
	class rbTree {

		public:
			typedef				Key										key_type;
			typedef				T										mapped_type;
			typedef				Compare									key_compare;
			typedef	typename	ft::pair<Key, T>						value_type;
			typedef				Alloc									allocator_type;
			typedef	typename	std::allocator<ft::Node<const Key, T> >	node_allocator_type;
			typedef	typename	Alloc::size_type						size_type;
			typedef	typename	Alloc::difference_type					difference_type;

		private:
			Node				*_root;
			Node				*_null_node;
			key_compare			_cmp;
			allocator_type		_alloc;
			node_allocator_type	_node_alloc;

		public:

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructors -----*/

		rbTree(key_compare &cmp = key_compare(), allocator_type &alloc = allocator_type()) : _cmp(cmp), _alloc(alloc), _node_alloc(node_allocator_type()) {
			_null_node = _node_alloc.allocate(1);
			_alloc.construct(&_null_node, value_type());
			_null_node->parent = NULL;
			_null_node->left = NULL;
			_null_node->right = NULL;
			_root = _null_node;
		}

		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		static Node	*minimum(Node* x) {
			while (x->_left)
				x = x->_left;
			return (x);
		}

		static Node*	maximum(Node* x) {
			while (x->_right)
				x = x->_right;
			return (x);
		}
	};

}

#endif
