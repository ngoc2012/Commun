/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 07:53:51 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main()
{
	try {
		Bureaucrat b2("b2", 2);
		std::cout << b2 << std::endl;
		for (int i = 0; i < 3; i++)
			b2.upGrade();

		Bureaucrat b145("b145", 145);
		std::cout << b145 << std::endl;
		for (int i = 0; i < 10; i++)
			b145.downGrade();
	} catch (Bureaucrat::GradeTooHighException &e) {
		std::cout << e.what() << std::endl;
	}
	} catch (Bureaucrat::GradeTooLowException &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
