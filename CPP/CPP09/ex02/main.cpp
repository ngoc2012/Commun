/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 14:36:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
    PmergeMe    p;

    for (int j = 0; j < argc - 2; j++)
    {
        std::vector<int> a;
        for (int i = 2; i < j + 3; i++)
            a.push_back(std::atoi(argv[i]));
        p.set_a(&a);
        p.print();
        std::sort(a.begin(), a.end());
        p.print();
        p.insertInSortedArray(a, std::atoi(argv[1]));
        p.print();
        if (p.isSorted(a))
            std::cout << "Sorted" << std::endl;
        else
            std::cout << "Not sorted" << std::endl;
    }

	return (0);
}
