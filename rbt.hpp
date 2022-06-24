/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:54:12 by ctirions          #+#    #+#             */
/*   Updated: 2022/06/24 16:27:57 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

namespace ft {

	enum rb_tree_color { _red = false, _black = true };

	struct rb_tree {

		typedef	rb_tree*		base_ptr;
		typedef	const rb_tree*	const_base_ptr;

		rb_tree_color	_color;
		base_ptr		_parent;
		base_ptr		_left;
		base_ptr		_right;

		/*---------- FUNCTIONS ----------*/

		static base_ptr	minimum(base_ptr x) {
			while (x->_left)
				x = x->_left;
			return (x);
		}

		static const_base_ptr	minimum(const_base_ptr x) {
			while (x->_left)
				x = x->_left;
			return (x);
		}

		static base_ptr	maximum(base_ptr x) {
			while (x->_right)
				x = x->_right;
			return (x);
		}

		static const_base_ptr	maximum(const_base_ptr x) {
			while (x->_right)
				x = x->_right;
			return (x);
		}
	};

}

#endif
