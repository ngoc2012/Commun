/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 07:12:07 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main()
{
	try {
		Bureaucrat bureaucrat("ash", 1);

		std::cout << bureaucrat << std::endl;

		bureaucrat.incrementGrade();
		// bureaucrat.decrementGrade();
	} catch (Bureaucrat::GradeTooHighException &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
