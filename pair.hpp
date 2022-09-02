/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:59:28 by ctirions          #+#    #+#             */
/*   Updated: 2022/09/02 17:50:10 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

	/*---------- PAIR STRUCT ----------*/

	template < class T1, class T2 >
	struct pair {
	public:
		T1	first;
		T2	second;

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructors -----*/

		pair(void) : first(T1()), second(T2()) {}
		pair(const T1 &a, const T2 &b) : first(a), second(b) {}
		template <class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

		/*----- Assignation operator -----*/

		pair	&operator=(const pair &p) {
			first = p.first;
			second = p.second;
			return (*this);
		}
	};

	/*---------- NON MEMBER FUNCTIONS ----------*/

	/*----- Relational operators -----*/

	template <class T1, class T2>
	bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool	operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
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

	/*---------- MAKE PAIR ----------*/

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y) { return (pair<T1, T2>(x, y)); }

}

#endif

