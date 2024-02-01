/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/01 10:59:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
    if (argc < 2)
        std::cout << "Use: ./exe 1 2 .. " << std::endl;
    std::vector<PairedValue<int>> a;

    /*
    // Check insert sort
    for (int i = 2; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
    int     b = std::atoi(argv[1]);
    PmergeMe<int>    p(a);
    std::sort(a.begin(), a.end());
    p.print();
    p.insertInSortedArray(a, b*b, 0, argc - 15);
    p.print();
    if (p.isSorted(a))
        std::cout << "Sorted" << std::endl;
    else
        std::cout << "Not sorted" << std::endl;
    */
    
    for (int i = 1; i < argc; i++)
        a.push_back(PairedValue(std::atoi(argv[i])));
    PmergeMe    p;

    //p._debug = true;
    std::vector<int>    S;
    p.sort(a, S);
    
    //std::cout << "========================================================" << std::endl;
    //p.print_s();
    std::cout << S.size() << " ";
    if (p.isSorted(S))
        std::cout << "Sorted" << std::endl;
    else
    {
        std::cout << "Not sorted" << std::endl;
        p.print(a);
        p.print_s(S);
    }
        

    return (0);
}
