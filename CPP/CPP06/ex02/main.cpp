/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 19:31:24 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int	main()
{
	Base*	x;
	Base	b;

	std::srand(static_cast<unsigned>(std::time(0)));
	for (int i  = 0; i < 10; i++)
	{
		x = b.generate();
		std::cout << "*x = "; b.identify(x);
		std::cout << ", &a = "; b.identify(*x);
		std::cout << std::endl;
	}

	return (0);
}
