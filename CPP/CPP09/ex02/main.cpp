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

void    vector_sort(int argc, char **argv, std::vector<int>& a, std::vector<int>& S, PmergeMe& p)
{
    ;
    for (int i = 1; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
    p.sort(a, S);

}

void    deque_sort(int argc, char **argv, std::deque<int>& a, std::deque<int>& S, PmergeMe& p)
{
    for (int i = 1; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
    p.sortD(a, S);
}

int	main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Use: ./exe 1 2 .. " << std::endl;
        return (1);
    }
    PmergeMe    p;

    clock_t start1 = clock();
    std::vector<int>    a;
    std::vector<int>    S;
    vector_sort(argc, argv, a, S, p);
    clock_t end1 = clock();
    
    

    clock_t start2 = clock();
    std::deque<int>    aD;
    std::deque<int>    SD;
    deque_sort(argc, argv, aD, SD, p);
    clock_t end2 = clock();

    double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1e6;
    double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1e6;
    std::cout << "Elapsed time: " << time1 << " microseconds" << std::endl;

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

    return (0);
}
