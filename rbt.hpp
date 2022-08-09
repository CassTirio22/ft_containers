/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:54:12 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/09 18:05:16 by ctirions         ###   ########.fr       */
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

		/*----- Destructor -----*/

		~rbTree(void) {
			_node_alloc.destroy(_null_node);
			_node_alloc.deallocate(_null_node, 1);
		}
		/*-----  -----*/
		/*-----  -----*/

		/*----- Insert -----*/

		void	insert(Node *node, value_type val) {
			if (_root == _null_node)
				_root = newNode(val);
			else if (node == _null_node)
				node = newNode(val);
			else if (_cmp(val._first, node->_data._first)) {
				node->_left = insert(node->_left, val);
				node->left->_parent = node;
			}
			else if (_cmp(node->_data._first, val._first)) {
				node->_right = insert(node->_right, val);
				node->right->_parent = node;
			}
		}

		/*----- Utils -----*/

		Node	*ft_next(Node *node) {
			Node	*tmp;

			if (node->_right == _null_node) {
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

		Node	*ft_prev(Node *node) {
			Node	*tmp;

			if (node->_left == _null_node) {
				tmp = node;
				while (tmp->_parent != _null_node && tmp == tmp->_parent->_left)
					tmp = tmp->_parent;
				tmp = tmp->_parent;
				return (tmp);
			}
			tmp = node->_left;
			while (tmp->_left != _null_node)
				tmp = tmp->_left;
			return (tmp);
		}

		Node *newNode(value_type val) {
			Node	*ret = _node_alloc.allocate(1);
			_node_alloc.construct(&ret->_data, val);
			ret->_parent = NULL;
			ret->_left = _null_node;
			ret->_right = _null_node;
			return (ret);
		}

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

		size_type	height(Node *node) {
			if (node == _null_node)
				return (0);
			else {
				size_type	left_depth = height(node->_left);
				size_type	right_depth = height(node->_right);
				if (left_depth > right_depth)
					return (left_depth + 1);
				else
					return (right_depth + 1);
			}
		}

		size_type nodeCount(Node *node) {
			if (node == _null_node)
				return (0);
			else
				return (nodeCount(node->_left) + nodeCount(node->_right) + 1);
		}
	};

}

#endif
