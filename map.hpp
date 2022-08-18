/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:04:47 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/18 20:18:25 by ctirions         ###   ########.fr       */
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

		/*----- Element access -----*/

		T	&operator[](const Key &key) {
			return (_rbt.findNode(key)->_data._second);
		}

		/*----- Capacity -----*/

		bool	empty(void) const {
			if (_size)
				return (true);
			return (false);
		}

		size_type	size(void) const { return (_size); }

		size_type	max_size(void) { return (_rbt._node_alloc.max_size()); }

		/*----- Modifiers -----*/


		ft::pair<iterator, bool>	insert(const value_type &value) {
			ft::pair<Node<Key, T> *, bool>	ret = _rbt.insert(_rbt.getRoot(), value);
			iterator	it(ret._first, _rbt.getNullNode());
			if (ret._second)
				_size++;
			return (ft::make_pair<iterator, bool>(it, ret._second));
		}

		iterator	insert(iterator position, const value_type &val) {}

		template <class InputIt>
		void	insert(InputIt first, InputIt last) {}

		void	erase(iterator pos) {}

		void	erase(iterator first, iterator last) {}

		size_type	erase(const key_type &key) {}

		void	swap(map &x) {
			// x.affRbt();
			rbt_type	rbtTmp = x.getRbt();
			size_type	sizeTmp = x._size;

			// x._rbt = _rbt;
			// x._size = _size;
			// _rbt = rbtTmp;
			// _size = sizeTmp;
		}

		void	clear(void) {
			_rbt.destroyRbt(_rbt.getRoot());
			_rbt.setRoot(_rbt.getNullNode());
		}
		/*----- Utils -----*/

		void	affRbt(void) const { _rbt.aff_tree(_rbt.getRoot(), 0); }

		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
	};
}

#endif
