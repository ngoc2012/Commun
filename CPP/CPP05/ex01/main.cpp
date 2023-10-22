/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/22 13:55:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

int	main()
{
	Bureaucrat	b2("b2", 2);
	std::cout << b2;
	Bureaucrat	b145("b145", 145);
	std::cout << b145;
	Form	f2("f2", 2, 100);
	try {
		f2.beSigned(b145);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		f2.beSigned(b2);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
