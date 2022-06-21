/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:59:28 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/21 18:54:41 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

	template <class T1, class T2>
	struct pair {


	public:
		T1	_first;
		T2	_second;

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructors -----*/

		pair(void) : _first(), _second() {}
		pair(const T1 &a, const T2 &b) : _first(a), _second(b) {}
		template <typename U1, typename U2>
		pair(const pair<U1, U2> &p) : _first(p._first), _second(p._second) {}

		/*----- Assignation operator -----*/

		pair	&operator=(const pair &p) {
			_first = p._first;
			_second = p._second;
			return (*this);
		}

		/*---------- NON MEMBER FUNCTIONS ----------*/

		/*----- Relational operators -----*/

		template <class T1, class T2>
		bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return (lhs._first == rhs._first && lhs._second == rhs._second);
		}

		template <class T1, class T2>
		bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return (!(lsh == rhs));
		}

		template <class T1, class T2>
		bool	operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return (lhs._first < rhs._first || (!(rhs._first < lhs._first) && lhs._second < rhs._second));
		}

		template <class T1, class T2>
		bool	operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return (rhs < lhs);
		}

		template <class T1, class T2>
		bool	operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return (!(lhs > rhs));
		}

		template <class T1, class T2>
		bool	operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return (!(lhs < rhs));
		}
	};

	/*---------- MAKE PAIR ----------*/

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y) { return (pair<T1, T2>(x, y)); }

}

#endif
