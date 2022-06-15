/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:57:07 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/15 16:03:35 by ctirions         ###   ########.fr       */
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

};

#endif


/*-----  -----*/
