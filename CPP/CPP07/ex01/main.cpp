/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 07:24:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib> // Required for atoi function

#include "iter.hpp"

int	main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        std::cout << std::atoi(argv[i]) << " ";
    }
    std::cout << std::endl;
    iter(argv + 1, argc - 1, print);
	std::cout << std::endl;
	return (0);
}
