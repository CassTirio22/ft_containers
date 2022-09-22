/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:04:47 by ctirions          #+#    #+#             */
/*   Updated: 2022/09/22 16:50:01 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define  MAP_HPP

# include <functional>
# include "pair.hpp"
# include "iterators.hpp"
# include "rbt.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<const Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
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
		typedef	ft::rbTree<const Key, T, Compare>									rbt_type;

	private:

		class value_compare : public std::binary_function<value_type, value_type, bool> {

			friend class map;

		protected:

		  key_compare	comp;

		public:

		  value_compare(Compare c) : comp(c) {}

		  bool operator() (const value_type &x, const value_type &y) const { return comp(x.first, y.first); }

		};

		key_compare		_comp;
		allocator_type	_alloc;
		rbt_type		_rbt;
		size_type		_size;
		value_compare	_val_comp;

	public:

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructors -----*/

		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _comp(comp), _alloc(alloc), _rbt(rbt_type()), _size(0), _val_comp(value_compare(comp)) {}

		template <class InputIterator>
 		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _rbt(rbt_type()), _size(0), _val_comp(value_compare(comp)) { insert(first, last); }

		map(const map &x) : _comp(x.key_comp()), _alloc(x.get_allocator()), _rbt(rbt_type()), _size(0), _val_comp(x.value_comp()) { insert(x.begin(), x.end()); }

		/*----- Assign operator -----*/

		map	&operator=(const map &x) {
			clear();
			_comp = x.key_comp();
			_alloc = x.get_allocator();
			_size = 0;
			_val_comp = x.value_comp();
			insert(x.begin(), x.end());
			return (*this);
		}

		/*----- Getter -----*/

		rbt_type	getRbt(void) const { return (_rbt); }


		/*----- Iterators -----*/

		iterator	begin(void) { return(iterator(_rbt.minimum(_rbt.getRoot()), _rbt.getNullNode(), _rbt.getRoot())); }

		const_iterator	begin(void) const { return(const_iterator(_rbt.minimum(_rbt.getRoot()), _rbt.getNullNode(), _rbt.getRoot())); }

		iterator	end(void) { return(iterator(_rbt.getNullNode(), _rbt.getNullNode(), _rbt.getRoot())); }

		const_iterator	end(void) const { return(const_iterator(_rbt.getNullNode(), _rbt.getNullNode(), _rbt.getRoot()));}

		reverse_iterator	rbegin(void) { return (reverse_iterator(end())); }

		const_reverse_iterator	rbegin(void) const { return (const_reverse_iterator(end())); }

		reverse_iterator	rend(void) { return(reverse_iterator(begin())); }

		const_reverse_iterator	rend(void) const { return (const_reverse_iterator(begin())); }

		/*----- Capacity -----*/

		bool	empty(void) const { return (!_size); }

		size_type	size(void) const { return (_size); }

		size_type	max_size(void) const { return (_rbt.getNodeAlloc().max_size()); }

		/*----- Element access -----*/

		T	&operator[](const Key &key) {
			return (insert(ft::make_pair(key, T())).first->second);
		}

		/*----- Modifiers -----*/

		ft::pair<iterator, bool>	insert(const value_type &value) {
			ft::pair<Node<const Key, T> *, bool>	ret = _rbt.insert(value);
			iterator	it(ret.first, _rbt.getNullNode(), _rbt.getRoot());
			if (ret.second)
				_size++;
			return (ft::make_pair<iterator, bool>(it, ret.second));
		}

		iterator	insert(iterator position, const value_type &val) {
			static_cast<void>(position);
			return (insert(val).first);
		}

		template <class InputIt>
		void	insert(InputIt first, InputIt last) {
			while (first != last) {
				insert(*first);
				first++;
			}
		}

		void	erase(iterator pos) {
			erase(pos->first);
		}

		void	erase(iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}

		size_type	erase(const key_type &key) {
			if (!_size)
				return (0);
			Node<const Key, T>	*node = _rbt.findNode(key);
			if (node->_data.first != key)
				return (0);
			_size--;
			_rbt.deleteNode(node->_data.first);
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
			_size = 0;
		}

		/*----- Observers -----*/

		key_compare		key_comp(void) const { return (_comp); }
		value_compare	value_comp(void) const { return (_val_comp); }

		/*----- Operations -----*/

		iterator	find(const key_type	&k) {
			iterator	ret(_rbt.findNode(k), _rbt.getNullNode(), _rbt.getRoot());
			if (ret->first == k)
				return (ret);
			return (iterator(_rbt.getNullNode(), _rbt.getNullNode(), _rbt.getRoot()));
		}

		const_iterator	find(const key_type &k) const { return (const_iterator(_rbt.findNode(k), _rbt.getNullNode(), _rbt.getRoot())); }

		size_type	count(const key_type &k) const {
			if (k == _rbt.findNode(k)->_data.first)
				return (1);
			return (0);
		}

		iterator	lower_bound(const key_type &k) {
			iterator it(begin());
			iterator ite(end());
			for (; it != ite; it++) {
				if (it->first == k)
					return (it);
				else if (it->first > k) {
					if (it->first == begin()->first)
						return (it);
					return (--it);
				}
			}
			return (end());
		}

		const_iterator	lower_bound(const key_type &k) const {
			const_iterator it(begin());
			const_iterator ite(end());
			for (; it != ite; it++) {
				if (it->first == k)
					return (it);
				else if (it->first > k) {
					if (it->first == begin()->first)
						return (it);
					return (--it);
				}
			}
			return (end());
		}

		iterator	upper_bound(const key_type &k) {
			iterator it(begin());
			iterator ite(end());
			for (; it != ite; it++) {
				if (it->first == k)
					return (++it);
				else if (it->first > k)
					return (it);
			}
			return (end());
		}

		const_iterator	upper_bound(const key_type &k) const {
			const_iterator it(begin());
			const_iterator ite(end());
			for (; it != ite; it++) {
				if (it->first == k)
					return (++it);
				else if (it->first > k)
					return (const_iterator(it));
			}
			return (end());
		}

		ft::pair<const_iterator, const_iterator>	equal_range(const key_type &k) const {
			return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
		}

		ft::pair<iterator, iterator>	equal_range(const key_type &k) {
			return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
		}

		/*----- Allocator -----*/

		allocator_type	get_allocator(void) const { return (_alloc); }

	};

	/*---------- NON-MEMBER FUNCTIONS ----------*/

	/*----- Relational operator -----*/

	template<class Key, class T, class Compare, class Alloc>
	bool	operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
			if (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
				return (true);
			return (false);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs == rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (!(rhs < lhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs < rhs));
	}

	/*----- Swap -----*/

	template <class Key, class T, class Compare, class Alloc>
  	void	swap(map<Key, T, Compare ,Alloc> &x, map<Key, T, Compare, Alloc> &y) {
		x.swap(y);
	}
}

#endif
