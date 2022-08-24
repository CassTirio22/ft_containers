/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:15:21 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/24 19:04:22 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include "rbt.hpp"
#include "iterators.hpp"
#include "map.hpp"

int main(void) {

	ft::map<const int, char> map;

	map.insert(ft::make_pair(5, 65));
	map.insert(ft::make_pair(6, 65));
	map.insert(ft::make_pair(7, 65));
	map.insert(ft::make_pair(8, 65));
	map.insert(ft::make_pair(18, 65));
	map.insert(ft::make_pair(1, 65));
	map.insert(ft::make_pair(-4, 65));
	map.insert(ft::make_pair(1000, 65));
	map.insert(ft::make_pair(2, 65));
	map.insert(ft::make_pair(84, 65));
	map.insert(ft::make_pair(69, 65));
	map.insert(ft::make_pair(420, 65));
	map.insert(ft::make_pair(42, 65));
	map.insert(ft::make_pair(19, 65));
	map.insert(ft::make_pair(101, 65));


	map.affRbt();

	std::cout << "-------------" << std::endl;

	map.erase(6);
	map.erase(5);
	map.erase(7);
	map.erase(8);
	map.erase(1);

	std::cout << map.size() << std::endl;
	std::cout << map.empty() << std::endl;
	
	ft::map<const int, char>::const_iterator	it = (map.end());

	std::cout << (it).getNode()->_data._first << std::endl;

	std::cout << "-------------" << std::endl;

	map.affRbt();
	

	
	return (0);
}
