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
#include <set>

#include "PmergeMe.hpp"

void    vector_sort(std::set<int>& s, std::vector<int>& a, std::vector<int>& S, PmergeMe& p)
{
    for (std::set<int>::iterator it = s.begin(); it != s.end(); ++it)
        a.push_back(*it);
    p.sort(a, S);

}

void    deque_sort(std::set<int>& s, std::deque<int>& a, std::deque<int>& S, PmergeMe& p)
{
    for (std::set<int>::iterator it = s.begin(); it != s.end(); ++it)
        a.push_back(*it);
    p.sortD(a, S);
}

int	main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Use: ./exe 1 2 .. " << std::endl;
        return (1);
    }

    int     e;
    std::set<int>    s;
    for (int i = 1; i < argc; i++)
    {
        e = std::atoi(argv[i]);
        if (s.find(e) != s.end())
        {
            std::cerr << "Error" << std::endl;
            return (1);
        }
        s.insert(e);
    }
        

    PmergeMe    p;

    clock_t start1 = clock();
    std::vector<int>    a;
    std::vector<int>    S;
    vector_sort(s, a, S, p);
    clock_t end1 = clock();
    
    

    clock_t start2 = clock();
    std::deque<int>    aD;
    std::deque<int>    SD;
    deque_sort(s, aD, SD, p);
    clock_t end2 = clock();

    std::cout << "Before: ";
    p.print(a);
    std::cout << "After: ";
    p.print(a);
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
