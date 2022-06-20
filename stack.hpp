/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:14:26 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/20 16:28:59 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class	stack {

	public:
		typedef	T									value_type;
		typedef Container							container_type;
		typedef typename container_type::size_type	size_type;

	private:
		container_type _cntr;

	public:

		/*---------- MEMBER FUNCTIONS ----------*/

		/*----- Constructor -----*/

		explicit stack(const container_type &cntr = container_type()) { this->_cntr = cntr; }

		/*----- Getter of _ctnr -----*/

		container_type	getCtnr(void) const { return (this->_cntr); }

		/*----- Size -----*/

		size_type	size(void) const { return (this->_cntr.size()); }

		/*----- Empty -----*/

		bool	empty(void) const { return (this->_cntr.empty()); }

		/*----- Top -----*/

		value_type	&top(void) { return (this->_cntr.back()); }

		const value_type	&top(void) const { return (this->_cntr.back()); }

		/*----- Push -----*/

		void	push(const value_type &val) { this->_cntr.push_back(val); }

		/*----- Pop -----*/

		void	pop(void) { this->_cntr.pop_back(); }

	};

	/*---------- NON MEMBER FUNCTIONS ----------*/

	/*----- Relational operators -----*/

	template <class T, class Container>
	bool	operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.getCtnr() == rhs.getCtnr()); }

	template <class T, class Container>
	bool	operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.getCtnr() != rhs.getCtnr()); }

	template <class T, class Container>
	bool	operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.getCtnr() < rhs.getCtnr()); }

	template <class T, class Container>
	bool	operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.getCtnr() <= rhs.getCtnr()); }

	template <class T, class Container>
	bool	operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.getCtnr() > rhs.getCtnr()); }

	template <class T, class Container>
	bool	operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.getCtnr() >= rhs.getCtnr()); }

}

#endif
