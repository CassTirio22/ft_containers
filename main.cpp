/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:15:21 by ctirions          #+#    #+#             */
/*   Updated: 2022/08/18 20:17:25 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "rbt.hpp"
#include "iterators.hpp"
#include "map.hpp"

int main(void) {

	ft::map<const int, int>	map1, map2;

	map1.insert(ft::make_pair(42, 1));
	map1.insert(ft::make_pair(19, 0));
	map1.insert(ft::make_pair(88, 0));
	map1.insert(ft::make_pair(22, 3));
	map1.insert(ft::make_pair(0, 0));
	std::cout << map1.insert(ft::make_pair(1000, 2))._second << std::endl;
	std::cout << map1.insert(ft::make_pair(1000, 2))._second << std::endl;;

	map1.affRbt();

	map1.swap(map2);


	return (0);
}
