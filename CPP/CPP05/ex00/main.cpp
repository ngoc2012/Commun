/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 08:09:30 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main()
{
	Bureaucrat b2("b2", 2);
	std::cout << b2;
	Bureaucrat b145("b145", 145);
	std::cout << b145;
	try {
		for (int i = 0; i < 3; i++)
			b2.upGrade();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		for (int i = 0; i < 10; i++)
			b145.downGrade();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "========== Test constructor ==========" << std::endl;
	try {
		Bureaucrat b160("b160", 160);
		std::cout << b160;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
