/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:57:07 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/21 19:24:40 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <type_traits>

namespace ft {

	/*----- Enable if -----*/

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	/*----- Is integral -----*/

	typedef	std::integral_constant<bool, true> true_type;
	typedef std::integral_constant<bool, false> false_type;


	template <class T> struct is_integral : public false_type {};


	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<char16_t> : public true_type {};
	template <> struct is_integral<char32_t> : public true_type {};
	template <> struct is_integral<wchar_t> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};

	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<short int> : public true_type {};
	template <> struct is_integral<long int> : public true_type {};
	template <> struct is_integral<long long int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<unsigned short int> : public true_type {};
	template <> struct is_integral<unsigned long int> : public true_type {};
	template <> struct is_integral<unsigned long long int> : public true_type {};

	/*----- Equal -----*/

	template <class It1, class It2>
	bool	equal(It1 first1, It1 last1, It2 first2) {
		for (; first1 != last1; first1++, first2++)
			if (!(*first1 == *first2))
				return (false);
		return (true);
	}

	template <class It1, class It2, class BinaryPredictate>
	bool	equal(It1 first1, It1 last1, It2 first2, BinaryPredictate pred) {
		for (; first1 != last1; first1++, first2++)
			if (!pred(*first1, *first2))
				return (false);
		return (true);
	}

	/*----- Lexicographical compare -----*/

	template <class It1, class It2>
	bool lexicographicla_compare(It1 first1, It1 last1, It2 first2, It2 last2) {
		for (; first1 != last1; first1++, first2++)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
		}
		return (first2 != last2);
	}

};

#endif


/*-----  -----*/
