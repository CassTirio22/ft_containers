/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainVector.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:15:21 by ctirions          #+#    #+#             */
/*   Updated: 2022/09/19 17:30:11 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "vector.hpp"
#include <iostream>

int main(void) {
	std::cout << "######################### VECTOR #########################" << std::endl << std::endl;

	std::cout << std::endl << "---------- STD ----------" << std::endl << std::endl;

	std::vector<char>	Vect1(10, 'a');
	ft::vector<char>	MyVect1(10, 'a');

	for (size_t i = 0; i < Vect1.size(); i++)
		std::cout << Vect1[i] << std::endl;

	std::cout << std::endl << "---------- FT ----------" << std::endl << std::endl;

	for (size_t i = 0; i < MyVect1.size(); i++)
		std::cout << MyVect1[i] << std::endl;

	std::cout << std::endl << "-------------------------" << std::endl << std::endl;

	std::vector<char>	Vect2(Vect1.begin(), Vect1.end());
	ft::vector<char>	MyVect2(MyVect1.begin(), MyVect1.end());

	return (0);
}
