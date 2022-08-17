/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:15:21 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/17 18:43:15 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "rbt.hpp"
#include "iterators.hpp"

int main(void){
	ft::rbTree<const int, char>	rbt;

	rbt.insert(rbt.getRoot(), ft::make_pair(50, 0));
	rbt.insert(rbt.getRoot(), ft::make_pair(55, 2));
	rbt.insert(rbt.getRoot(), ft::make_pair(35, 3));
	rbt.insert(rbt.getRoot(), ft::make_pair(40, 4));
	rbt.insert(rbt.getRoot(), ft::make_pair(20, 4));
	rbt.insert(rbt.getRoot(), ft::make_pair(10, 4));
	rbt.insert(rbt.getRoot(), ft::make_pair(5, 4));
	rbt.insert(rbt.getRoot(), ft::make_pair(25, 4));
	rbt.insert(rbt.getRoot(), ft::make_pair(17, 4));
	rbt.insert(rbt.getRoot(), ft::make_pair(40, 4));

	ft::RbtIterator<ft::pair<const int, char>, ft::Node<const int, char> > it(rbt.findNode(ft::make_pair(20, 4)), rbt.getNullNode());

	// rbt.deleteNode(ft::make_pair(25, 4));
	// rbt.deleteNode(ft::make_pair(17, 4));
	// rbt.deleteNode(ft::make_pair(55, 2));
	rbt.deleteNode(ft::make_pair(35, 4));
	std::cout << "------------------------" << std::endl;

	// rbt.aff_node(rbt.getRoot());
	rbt.aff_tree(rbt.getRoot(), 0);
	std::cout << "------------------------" << std::endl;
	it++;

	std::cout << (*it)._first << std::endl;


	return (0);
}
