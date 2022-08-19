/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:04:47 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/19 19:26:55 by ctirions         ###   ########.fr       */
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
		typedef	ft::ReverseIterator<const_iterator>							reverse_const_iterator;
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

		iterator	begin(void) {}

		const_iterator	begin(void) const {}

		iterator	end(void) {}

		const_iterator	end(void) const {}

		reverse_iterator	rbegin(void) {}

		const_reverse_iterator	rbegin(void) const {}

		reverse_iterator	rend(void) {}

		const_reverse_iterator	rend(void) const {}

		/*----- Capacity -----*/

		bool	empty(void) const {
			if (_size)
				return (true);
			return (false);
		}

		size_type	size(void) const { return (_size); }

		size_type	max_size(void) { return (_rbt._node_alloc.max_size()); }

		/*----- Element access -----*/

		T	&operator[](const Key &key) {
			return ((_rbt.findNode(key))->_data._second);
		}

		/*----- Modifiers -----*/

		ft::pair<iterator, bool>	insert(const value_type &value) {
			ft::pair<Node<Key, T> *, bool>	ret = _rbt.insert(_rbt.getRoot(), value);
			iterator	it(ret._first, _rbt.getNullNode());
			if (ret._second)
				_size++;
			return (ft::make_pair<iterator, bool>(it, ret._second));
		}

		iterator	insert(iterator position, const value_type &val) {
			std::static_cast<void>(position);
			return (insert(val)._first);
		}

		template <class InputIt>
		void	insert(InputIt first, InputIt last) {
			while (first != last) {
				insert(*first);
				first++;
			}
		}

		void	erase(iterator pos) {}

		void	erase(iterator first, iterator last) {}

		size_type	erase(const key_type &key) {}

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

		size_type	count(const key_type &k) const { k == _rbt.findNode(k)->_data._first ? return (1) : return (0); }

		iterator	lower_bound(const key_type &k) const {}

		const_iterator	lower_bound(const key_type &k) const {}

		iterator	upper_bound(const key_type &k) const {}

		const_iterator	upper_bound(const key_type &k) const {}

		ft::pair<const_iterator, const_iterator>	equal_range(const key &k) const {}

		ft::pair<iterator, iterator>	equal_range(const key &k) {}

		/*----- Allocator -----*/

		allocator_type	get_allocator(void) const { return (_alloc); }

		/*----- Utils -----*/

		void	affRbt(void) const { _rbt.aff_tree(_rbt.getRoot(), 0); }

	};
}

#endif
