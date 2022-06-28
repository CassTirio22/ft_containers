/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:59:28 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/28 18:59:00 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

	/*---------- PAIR STRUCT ----------*/

	template < class T1, class T2 >
	struct pair {
	public:
		T1	_first;
		T2	_second;

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructors -----*/

		pair(void) : _first(T1()), _second(T2()) {}
		pair(const T1 &a, const T2 &b) : _first(a), _second(b) {}
		template <class U1, class U2>
		pair(const pair<U1, U2> &p) : _first(p._first), _second(p._second) {}

		/*----- Assignation operator -----*/

		pair	&operator=(const pair &p) {
			_first = p._first;
			_second = p._second;
			return (*this);
		}
	};

	/*---------- NON MEMBER FUNCTIONS ----------*/

	/*----- Relational operators -----*/

	template <class T1, class T2>
	bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs._first == rhs._first && lhs._second == rhs._second);
	}

	template <class T1, class T2>
	bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (!(lhs == rhs));
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

	/*---------- MAKE PAIR ----------*/

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 x, T2 y) { return (pair<T1, T2>(x, y)); }

}


// namespace ft
// {
// 	template < class T1, class T2 >
// 	struct pair
// 	{
// 		public:
// 			typedef T1 first_type;
// 			typedef T2 second_type;
// 			first_type	first;
// 			second_type	second;
// 			pair(): first(first_type()), second(second_type())
// 			{
// 				return ;
// 			}
// 			pair( const T1& x, const T2& y ): first(x), second(y)
// 			{
// 				return ;
// 			}
// 			template< class U1, class U2 >
// 			pair( const pair<U1, U2>& p ): first(p.first), second(p.second)
// 			{
// 				return ;
// 			}
// 			pair& operator=( const pair& ref )
// 			{
// 				first = ref.first;
// 				second = ref.second;
// 				return (*this);
// 			}
// 	};

// 	template <class T1, class T2>
// 	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
// 	{
// 		return (lhs.first == rhs.first && lhs.second == rhs.second);
// 	}

// 	template <class T1, class T2>
// 	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
// 	{
// 		return (!(lhs == rhs));
// 	}

// 	template <class T1, class T2>
// 	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
// 	{
// 		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
// 	}

// 	template <class T1, class T2>
// 	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
// 	{
// 		return (!(rhs < lhs));
// 	}

// 	template <class T1, class T2>
// 	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
// 	{
// 		return (rhs < lhs);
// 	}

// 	template <class T1, class T2>
// 	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
// 	{
// 		return (!(lhs<rhs));
// 	}

// 	template <class T1, class T2>
// 	pair<const T1,T2> make_pair (T1 x, T2 y)
// 	{
// 		return (pair<const T1, T2>(x, y));
// 	}
// }

#endif

