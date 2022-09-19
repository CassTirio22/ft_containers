/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:54:12 by ctirions          #+#    #+#             */
/*   Updated: 2022/09/19 16:51:41 by ctirions         ###   ########.fr       */
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
		bool					_db;
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

		public:

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructors -----*/

		rbTree(const key_compare &cmp = key_compare(), const allocator_type &alloc = allocator_type()) : _cmp(cmp), _alloc(alloc), _node_alloc(node_allocator_type()) {
			_null_node = _node_alloc.allocate(1);
			_alloc.construct(&_null_node->_data, value_type());
			_null_node->_parent = NULL;
			_null_node->_left = NULL;
			_null_node->_right = NULL;
			_null_node->_color = BLACK;
			_null_node->_db = false;
			_root = _null_node;
		}

		/*----- Destructor -----*/

		~rbTree(void) {
			destroyRbt(_root);
			_alloc.destroy(&_null_node->_data);
			_node_alloc.deallocate(_null_node, 1);
		}

		void	destroyRbt(Node *node) {
			if (node != _null_node) {
				destroyRbt(node->_left);
				destroyRbt(node->_right);
				_alloc.destroy(&node->_data);
				_node_alloc.deallocate(node, 1);
			}
		}

		/*----- Getter -----*/

		Node	*getRoot(void) const { return (_root); }
		Node	*getNullNode(void) const { return (_null_node); }
		key_compare	getKeyCompare(void) const { return (_cmp); }
		node_allocator_type	getNodeAlloc(void) const { return (_node_alloc); }

		Node	*getUncle(Node *node) const {
			if (node->_parent == _root || node == _root || node == NULL || node == _null_node)
				return (NULL);
			if (node->_parent == node->_parent->_parent->_left)
				return (node->_parent->_parent->_right);
			return (node->_parent->_parent->_left);
		}

		Node	*getSibling(Node *node) const {
			if (node == node->_parent->_right) {
				return (node->_parent->_left);
			}
			return (node->_parent->_right);
		}

		Node	*getFarSiblingChild(Node *node) {
			if (node == node->_parent->_right)
				return (node->_parent->_left->_left);
			return (node->_parent->_right->_right);
		}

		Node	*getNearSiblingChild(Node *node) {
			if (node == node->_parent->_right)
				return (node->_parent->_left->_right);
			return (node->_parent->_right->_left);
		}

		/*----- Setter -----*/

		void	setRoot(Node *node) { _root = node; }

		/*----- Rotate -----*/

		Node	*rotateLeft(Node *node) {
			Node	*tmp_a = node;
			Node	*tmp_b = node->_right->_left;

			node = node->_right;
			node->_left = tmp_a;
			tmp_a->_right = tmp_b;
			node->_parent = tmp_a->_parent;
			if (node->_parent) {
				if (tmp_a == tmp_a->_parent->_right)
					node->_parent->_right = node;
				else
					node->_parent->_left = node;
			}
			else
				_root = node;
			tmp_a->_parent = node;
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
			if (node->_parent) {
				if (tmp_a == tmp_a->_parent->_right)
					node->_parent->_right = node;
				else
					node->_parent->_left = node;
			}
			else
				_root = node;
			tmp_a->_parent = node;
			if (tmp_b != _null_node)
				tmp_b->_parent = tmp_a;
			return (node);
		}

		/*----- Insert -----*/

		ft::pair<Node *, bool>	insert(value_type val) {
			Node	*tmp = _root;
			if (_root == _null_node)
				return (ft::make_pair(_root = newNode(val, NULL, BLACK), true));
			while (true) {
				if (_cmp(val.first, tmp->_data.first)) {
					if (tmp->_left == _null_node) {
						tmp->_left = newNode(val, tmp, RED);
						return (balanceTree(tmp->_left));
					}
					else
						tmp = tmp->_left;
				}
				else if (_cmp(tmp->_data.first, val.first)) {
					if (tmp->_right == _null_node) {
						tmp->_right = newNode(val, tmp, RED);
						return (balanceTree(tmp->_right));
					}
					else
						tmp = tmp->_right;
				}
				else
					return (ft::make_pair(tmp, false));
			}
		}

		ft::pair<Node *, bool>	balanceTree(Node *node) {
			if (node == _root || node == _null_node || node == NULL)
				return (ft::make_pair(node, true));
			if (node->_parent->_color == BLACK)
				return (ft::make_pair(node, true));
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
			return (ft::make_pair(node, true));
		}

		/*----- Delete -----*/

		void	deleteNode(const key_type key) {
			Node	*node = findNode(key);
			if (node->_data.first != key)
				return ;
			if (node->_left == _null_node && node->_right == _null_node) {
				if (node->_color == RED || node == _root)
					destroyNode(node);
				else {
					Node	*db = newNode(value_type(), node->_parent, BLACK);
					db->_db = true;
					bool parentPos = node == node->_parent->_left ? true : false;
					destroyNode(node);
					parentPos ? db->_parent->_left = db : db->_parent->_right = db;
					balanceDelTree(db);
				}
			}
			else {
				Node	*tmp = node->_left != _null_node ? maximum(node->_left) : minimum(node->_right);
				if (tmp->_left != _null_node || tmp->_right != _null_node) {
					if (tmp->_left != _null_node) {
						tmp->_left->_color = BLACK;
						tmp->_left->_parent = tmp->_parent;
						tmp == tmp->_parent->_left ? tmp->_parent->_left = tmp->_left : tmp->_parent->_right = tmp->_left;
					}
					else {
						tmp->_right->_color = BLACK;
						tmp->_right->_parent = tmp->_parent;
						tmp == tmp->_parent->_left ? tmp->_parent->_left = tmp->_right : tmp->_parent->_right = tmp->_right;
					}
					copyNode(node, tmp);
				}
				else {
					if (tmp->_color == RED) {
						tmp == tmp->_parent->_left ? tmp->_parent->_left = _null_node : tmp->_parent->_right = _null_node;
						copyNode(node, tmp);
					}
					else {
						Node	*db = newNode(value_type(), tmp->_parent, BLACK);
						db->_db = true;
						tmp == tmp->_parent->_left ? tmp->_parent->_left = db : tmp->_parent->_right = db;
						copyNode(node, tmp);
						balanceDelTree(db);
					}
				}
			}
		}

		void	balanceDelTree(Node *db) {
			if (db == _root) {
				db->_color = BLACK;
				return ;
			}
			Node	*sibling = getSibling(db);
			if (sibling->_color == RED) {
				sibling->_color = db->_parent->_color;
				db->_parent->_color = RED;
				db == db->_parent->_left ? rotateLeft(db->_parent) : rotateRight(db->_parent);
				balanceDelTree(db);
			}
			else {
				Node	*farSiblingChild = getFarSiblingChild(db);
				if (farSiblingChild->_color == RED) {
					sibling->_color = db->_parent->_color;
					db->_parent->_color = BLACK;
					db == db->_parent->_left ? rotateLeft(db->_parent) : rotateRight(db->_parent);
					farSiblingChild->_color = BLACK;
					if (db->_db)
						destroyNode(db);
				}
				else {
					Node	*nearSiblingChild = getNearSiblingChild(db);
					if (nearSiblingChild->_color == RED) {
						nearSiblingChild->_color = sibling->_color;
						sibling->_color = RED;
						sibling == sibling->_parent->_left ? rotateLeft(sibling) : rotateRight(sibling);
						balanceDelTree(db);
					}
					else {
						if (db->_db)
							destroyNode(db);
						sibling->_color = RED;
						if (sibling->_parent->_color == BLACK)
							balanceDelTree(sibling->_parent);
						else
							sibling->_parent->_color = BLACK;
					}
				}
			}
		}

		void	destroyNode(Node *node) {
			if (node != _root) {
				if (node == node->_parent->_left)
					node->_parent->_left = _null_node;
				else
					node->_parent->_right = _null_node;
			}
			else
				_root = _null_node;
			_alloc.destroy(&node->_data);
			_node_alloc.deallocate(node, 1);
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
			ret->_db = false;
			return (ret);
		}

		void	copyNode(Node *a, Node *b) {
			if (a != _root)
				a->_parent->_left == a ? a->_parent->_left = b : a->_parent->_right = b;
			else
				_root = b;
			b->_parent = a->_parent;
			if (b == a->_left)
				b->_left = a;
			else
				b->_left = a->_left;
			if (b == a->_right)
				b->_right = a;
			else
				b->_right = a->_right;
			b->_left->_parent = b;
			b->_right->_parent = b;
			b->_color = a->_color;
			b->_db = a->_db;
			_alloc.destroy(&a->_data);
			_node_alloc.deallocate(a, 1);
		}

		void	swapNode(Node *a, Node *b) {
			Node	*tmpParent = b->_parent;
			Node	*tmpLeft = b->_left;
			Node	*tmpRight = b->_right;
			bool	tmpColor = b->_color;
			bool	tmpDb = b->_db;

			if (a != _root)
				a->_parent->_left == a ? a->_parent->_left = b : a->_parent->_right = b;
			else
				_root = b;
			if (a->_left != b && a->_right != b)
				b == b->_parent->_left ? b->_parent->_left = a : b->_parent->_right = a;
			else
				b->_parent = a->_parent;
			if (b == a->_left)
				b->_left = a;
			else
				b->_left = a->_left;
			if (b == a->_right)
				b->_right = a;
			else
				b->_right = a->_right;
			b->_left->_parent = b;
			b->_right->_parent = b;
			b->_color = a->_color;
			b->_db = a->_db;

			if (b->_left == a || b->_right == a)
				a->_parent = b;
			else
				a->_parent = tmpParent;
			a->_left = tmpLeft;
			a->_right = tmpRight;
			a->_color = tmpColor;
			a->_db = tmpDb;
		}

		void	aff_node(Node *node) const {
			std::string	color;
			node->_color ? color = "black" : color = "red";
			std::cout << node->_data.first << " | " << node->_data.second << " | " << color << std::endl;
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

		Node	*minimum(Node* x) const {
			if (x == _null_node)
				return (x);
			while (x->_left != _null_node)
				x = x->_left;
			return (x);
		}

		Node*	maximum(Node* x) const {
			if (x == _null_node)
				return (x);
			while (x->_right != _null_node)
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

		Node	*findNode(const key_type key) const {
			Node	*toFind = _root;

			while (_cmp(key, toFind->_data.first) || _cmp(toFind->_data.first, key)) {
				if (_cmp(key, toFind->_data.first)) {
					if (toFind->_left == _null_node)
						return (toFind);
					toFind = toFind->_left;
				}
				else if (_cmp(toFind->_data.first, key)) {
					if (toFind->_right == _null_node)
						return (toFind);
					toFind = toFind->_right;
				}
			}
			return (toFind);
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

		void	swap(rbTree	&rbt) {
			Node	*rootTmp = rbt._root;
			Node	*nullNodeTmp = rbt._null_node;

			rbt._root = _root;
			rbt._null_node = _null_node;

			_root = rootTmp;
			_null_node = nullNodeTmp;
		}

	};

}

#endif
