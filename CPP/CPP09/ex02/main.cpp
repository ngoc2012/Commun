/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 13:54:45 by ngoc             ###   ########.fr       */
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

	for (int i = 2; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
    p.set_a(&a);
    p.print();
    p.insertInSortedArray(a, std::atoi(argv[1]));
    p.print();

	return (0);
}
