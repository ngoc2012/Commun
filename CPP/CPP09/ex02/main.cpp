/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 13:48:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <vector>

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
    PmergeMe    p;
    std::vector<int> a;

	for (int i = 1; i < argc; i++)
	{
        std::cout << std::atoi(argv[i]) << " ";
        a.push_back(std::atoi(argv[i]));
	}
    std::cout << std::endl;
    p.set_a(&a);
    p.print();

	return (0);
}
