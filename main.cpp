/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:15:21 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/15 16:15:23 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rbt.hpp"

int main(void){
	ft::rbTree<const int, char>	rbt;

	rbt.insert(rbt.getRoot(), ft::make_pair(50, 65));
	rbt.insert(rbt.getRoot(), ft::make_pair(55, 65));
	rbt.insert(rbt.getRoot(), ft::make_pair(35, 65));
	rbt.insert(rbt.getRoot(), ft::make_pair(40, 65));
	rbt.insert(rbt.getRoot(), ft::make_pair(20, 65));
	rbt.insert(rbt.getRoot(), ft::make_pair(10, 65));
	rbt.insert(rbt.getRoot(), ft::make_pair(5, 65));
	rbt.insert(rbt.getRoot(), ft::make_pair(25, 65));
	rbt.insert(rbt.getRoot(), ft::make_pair(17, 65));
	return (0);
}
