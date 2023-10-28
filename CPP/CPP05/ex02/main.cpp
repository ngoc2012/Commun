/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/28 17:49:57 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

int	main()
{
	Bureaucrat	b2("b2", 2);
	std::cout << b2;
	Bureaucrat	b145("b145", 145);
	std::cout << b145;
	ShrubberyCreationForm s0("home");
	s0.execute(b145);
	s0.execute(b2);
	return (0);
}
