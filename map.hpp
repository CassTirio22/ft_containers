/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:04:47 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/22 04:26:13 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define  MAP_HPP

# include <functional>
# include "pair.hpp"
# include "iterators.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
	public:
		typedef	Key						key_type;
		typedef	T						mapped_type;
		typedef	ft::pair<const Key, T>	value_type;
		typedef	Compare					key_compare;
		typedef	Alloc					allocator_type;
		typedef	value_type*				pointer;
		typedef	value_type&				reference;
		typedef	const value_type*		const_pointer;
		typedef	const value_type&		const_reference;
		typedef	ft::Iterator<BidirectionalIteratorTag, value_type>	iterator;
	private:
		key_compare		_comp;
		allocator_type	_alloc;

	public:

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructors -----*/

		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _comp(comp), _alloc(alloc) {}
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
		/*-----  -----*/
	};
}

#endif
