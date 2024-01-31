/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/30 10:05:29 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <vector>

#include "PmergeMe.hpp"
#include "PmergeMe.cpp"

int	main(int argc, char **argv)
{
    if (argc < 2)
        std::cout << "Use: ./exe 1 2 .. " << std::endl;
    std::vector<int> a;
    for (int i = 1; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
    /*
    PmergeMe<int>    p(a);
    p.sort();
    std::cout << "========================================================" << std::endl;
    p.print_s();
    */
    //if (p.isSorted(a))
    //    std::cout << "Sorted" << std::endl;
    //else
    //    std::cout << "Not sorted" << std::endl;

    return (0);
}
