/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:54:12 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/10 17:53:02 by ctirions         ###   ########.fr       */
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
		bool					_color;
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
			bool				_f;
			bool				_ll;
			bool				_rr;
			bool				_rl;
			bool				_lr;

		public:

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructors -----*/

		rbTree(key_compare &cmp = key_compare(), allocator_type &alloc = allocator_type()) : _cmp(cmp), _alloc(alloc), _node_alloc(node_allocator_type()), _f(false), _ll(false), _rr(false), _rl(false), _lr(false) {
			_null_node = _node_alloc.allocate(1);
			_alloc.construct(&_null_node, value_type());
			_null_node->_parent = NULL;
			_null_node->_left = NULL;
			_null_node->_right = NULL;
			_null_node->_color = rbTreeColor._black;
			_root = _null_node;
		}

		/*----- Destructor -----*/

		~rbTree(void) {
			_node_alloc.destroy(_null_node);
			_node_alloc.deallocate(_null_node, 1);
		}

		/*-----  -----*/

		/*----- Insert -----*/

		Node	*insert(Node *node, value_type val) {
			if (_root == _null_node)
				return (_root = newNode(val, rbTreeColor._black));
			else if (node == _null_node)
				return (node = newNode(val, rbTreeColor._red));
			else if (_cmp(val._first, node->_data._first)) {
				node->_left = insert(node->_left, val);
				node->left->_parent = node;
				if (node != _root)
					if (!node->_color && !node->_left->_color)
						_f = true;
			}
			else if (_cmp(node->_data._first, val._first)) {
				node->_right = insert(node->_right, val);
				node->right->_parent = node;
				if (node != _root)
					if (!node->_color && !node->_right->_color)
						_f = true;
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

		Node *newNode(value_type val, bool color) {
			Node	*ret = _node_alloc.allocate(1);
			_node_alloc.construct(&ret->_data, val);
			ret->_parent = NULL;
			ret->_left = _null_node;
			ret->_right = _null_node;
			ret->_color = color;
			return (ret);
		}

		void	aff_node(node_type *node) const {
			std::string	color;
			node->_color ? color = "red" : color = "black";
			std::cout << node->_data._first << " | " << node->_data._second << " | " << color << std::endl;
		}

		void	aff_tree(node_type *node, int space) const {
			int i;
			if(node != _null_node) {
				space = space + 10;
				aff_tree(node->_right, space);
				std::cout << std::endl;
				for (i = 10; i < space; i++)
					std::cout << " ";
				aff_node(node);
				std::cout << std::endl;
				aff_tree(node->_left, space);
			}
		}

		Node	*minimum(Node* x) {
			while (x->_left)
				x = x->_left;
			return (x);
		}

		Node*	maximum(Node* x) {
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
