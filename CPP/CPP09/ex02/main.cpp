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
#include <list>

#include "PmergeMe.hpp"

void    vector_sort(int argc, char **argv)
{
    std::vector<int> a;
    for (int i = 1; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
    PmergeMe    p;
    std::vector<int>    S;
    p.sort(a, S);

    std::cout << S.size() << " ";
    if (p.isSorted(S))
        std::cout << "Sorted" << std::endl;
    else
    {
        std::cout << "Not sorted" << std::endl;
        p.print(a);
        p.print(S);
    }
}

void    array_sort(int argc, char **argv)
{
    std::list<int> a;

    std::array<int, 100> a; // Assuming a maximum of 100 elements

    for (int i = 1; i < argc; i++)
        a[i-1] = std::atoi(argv[i]);

    PmergeMe p;
    //p._debug = true;

    std::array<int, 100> S;
    p.sort(a, S);

    std::cout << S.size() << " ";
    if (p.isSorted(S))
        std::cout << "Sorted" << std::endl;
    else
    {
        std::cout << "Not sorted" << std::endl;
        p.print(a);
        p.print(S);
    }

}

int	main(int argc, char **argv)
{
    if (argc < 2 || argc > 4001)
        std::cout << "Use: ./exe 1 2 .. " << std::endl;

    //vector_sort(argc, argv);
    array_sort(argc, argv);

    return (0);
}