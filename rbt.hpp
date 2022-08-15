/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:54:12 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/15 18:32:46 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

# define BLACK true
# define RED false

# include "pair.hpp"
# include <iostream>
# include <functional>
# include <memory>

namespace ft {

	template <class Key, class T>
	struct Node {
		ft::pair<const Key, T>	_data;
		Node					*_left;
		Node					*_right;
		Node					*_parent;
		bool					_color;
	};

	template <class Key, class T, class Compare = std::less<Key> >
	class rbTree {

		public:
			typedef	Key										key_type;
			typedef	T										mapped_type;
			typedef	ft::Node<const Key, T>					Node;
			typedef	ft::pair<const Key, T>						value_type;
			typedef	std::allocator<ft::pair<const Key, T> >	allocator_type;
			typedef	std::allocator<ft::Node<const Key, T> >	node_allocator_type;
			typedef	Compare									key_compare;
			typedef	typename	allocator_type::size_type						size_type;
			typedef	typename	allocator_type::difference_type					difference_type;

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

		rbTree(const key_compare &cmp = key_compare(), const allocator_type &alloc = allocator_type()) : _cmp(cmp), _alloc(alloc), _node_alloc(node_allocator_type()), _f(false), _ll(false), _rr(false), _rl(false), _lr(false) {
			_null_node = _node_alloc.allocate(1);
			_alloc.construct(&_null_node->_data, value_type());
			_null_node->_parent = NULL;
			_null_node->_left = NULL;
			_null_node->_right = NULL;
			_null_node->_color = BLACK;
			_root = _null_node;
		}

		/*----- Destructor -----*/

		~rbTree(void) {
			_node_alloc.destroy(_null_node);
			_node_alloc.deallocate(_null_node, 1);
		}

		/*----- Getter -----*/

		Node	*getUncle(Node *node) const {
			if (node->_parent == _root || node == _root || node == NULL || node == _null_node)
				return (NULL);
			if (node == node->_parent->_left)
				return (node->_parent->_parent->_right);
			return (node->_parent->_parent->_left);
		}

		Node	*getRoot(void) const { return (_root); }

		/*----- Rotate -----*/

		Node	*rotateLeft(Node *node) {
			Node	*tmp_a = node;
			Node	*tmp_b = node->_right->_left;

			node = node->_right;
			node->_left = tmp_a;
			tmp_a->_right = tmp_b;
			node->_parent = tmp_a->_parent;
			tmp_a->_parent = node;
			if (node->_parent)
				node->_parent->_right = node;
			else
				_root = node;
			if (tmp_b != _null_node)
				tmp_b->_parent = tmp_a;
			return (node);
		}

		Node	*rotateRight(Node *node) {
			Node	*tmp_a = node;
			Node	*tmp_b = node->_left->_right;

			node = node->_left;
			node->_right = tmp_a;
			tmp_a->_left = tmp_b;
			node->_parent = tmp_a->_parent;
			tmp_a->_parent = node;
			if (node->_parent)
				node->_parent->_left = node;
			else
				_root = node;
			if (tmp_b != _null_node)
				tmp_b->_parent = tmp_a;
			return (node);
		}

		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*----- Insert -----*/

		Node	*insert(Node *node, value_type val) {
			Node	*tmp = _root;
			if (_root == _null_node)
				return (newNode(val, NULL, BLACK));
			while (true) {
				if (_cmp(val._first, tmp->_data._first)) {
					if (tmp->_left == _null_node) {
						tmp->_left = newNode(val, tmp, RED);
						return (balanceTree(tmp->_left));
					}
					else
						tmp = tmp->_left;
				}
				else if (_cmp(tmp->_data._first, val._first)) {
					if (tmp->_right == _null_node) {
						tmp->_right = newNode(val, tmp, RED);
						return (balanceTree(tmp->_right));
					}
					else
						tmp = tmp->_right;
				}
				else
					return (tmp);
			}
		}

		/*----- Balance -----*/

		Node	*balanceTree(Node *node) {
			if (node->_parent->_color == BLACK)
				return (node);

			Node	*uncle = getUncle(node);
			if (uncle && uncle->_color == RED) {
				uncle->_color = BLACK;
				node->_parent->_color = BLACK;
				if (node->_parent->_parent != _root)
					node->_parent->_parent->_color = RED;
				balanceTree(node->_parent->_parent);
			}
			else {
				Node	*parent = node->_parent;
				Node	*grandParent = parent->_parent;
				if (!ThreeNodesMakeLine(node, parent, grandParent)) {
					if (parent->_left == node)
						rotateRight(node->_parent);
					else
						rotateLeft(node->_parent);
				}
				if (grandParent->_left == parent || grandParent->_left == node) {
					grandParent->_color = RED;
					grandParent->_left->_color = BLACK;
					rotateRight(grandParent);
				}
				else {
					grandParent->_color = RED;
					grandParent->_right->_color = BLACK;
					rotateLeft(grandParent);
				}
			}
			return (node);
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
			while (tmp->_right != _null_node)
				tmp = tmp->_right;
			return (tmp);
		}

		Node *newNode(value_type val, Node *parent, bool color) {
			Node	*ret = _node_alloc.allocate(1);
			_alloc.construct(&ret->_data, val);
			ret->_parent = parent;
			ret->_left = _null_node;
			ret->_right = _null_node;
			ret->_color = color;
			return (ret);
		}

		void	aff_node(Node *node) const {
			std::string	color;
			node->_color ? color = "red" : color = "black";
			std::cout << node->_data._first << " | " << node->_data._second << " | " << color << std::endl;
		}

		void	aff_tree(Node *node, int space) const {
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

		size_type	nodeCount(Node *node) {
			if (node == _null_node)
				return (0);
			else
				return (nodeCount(node->_left) + nodeCount(node->_right) + 1);
		}

		bool	ThreeNodesMakeLine(Node *node1, Node *node2, Node *node3) {
			if ((node1 == node2->_left && node2 == node3->_left) || (node1 == node2->_right && node2 == node3->_right))
				return (true);
			return (false);
		}

	};

}

#endif
