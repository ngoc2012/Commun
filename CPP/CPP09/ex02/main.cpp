/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/02 06:11:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>

#include "PmergeMe.hpp"

void    vector_sort(int argc, char **argv, std::vector<int>& a, std::vector<int>& S)
{
    ;
    for (int i = 1; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
    PmergeMe    p;
    
    p.sort(a, S);
    /*
    std::cout << S.size() << " ";
    if (p.isSorted(S))
        std::cout << "Sorted" << std::endl;
    else
    {
        std::cout << "Not sorted" << std::endl;
        p.print(a);
        p.print(S);
    }
    */
}

void    deque_sort(int argc, char **argv, std::deque<int>& a, std::deque<int>& S)
{
    for (int i = 1; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
    PmergeMe    p;
    p.sortD(a, S);
    /*
    std::cout << S.size() << " ";
    if (p.isSortedD(S))
        std::cout << "Sorted" << std::endl;
    else
    {
        std::cout << "Not sorted" << std::endl;
        p.printD(a);
        p.printD(S);
    }
    */
}

int	main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Use: ./exe 1 2 .. " << std::endl;
        return (1);
    }
    
    clock_t start1 = clock();
    std::vector<int>    a;
    std::vector<int>    S;
    vector_sort(argc, argv, a, S);
    clock_t end1 = clock();
    double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1e6;
    std::cout << "Elapsed time: " << time1 << " microseconds" << std::endl;

    deque_sort(argc, argv);

    return (0);
}
