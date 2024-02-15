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
#include <algorithm>


#include "PmergeMe.hpp"

std::ostream& operator<<(std::ostream& s, PairedValue& a)
{
    return s << "(" << a._y << ", " << a._x << ")";
}

template <typename T>
void    print(T& s)
{
    for (typename T::iterator it = s.begin(); it != s.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

template <typename T>
bool    isSorted(T& a)
{
    for (size_t i = 0; i < a.size() - 1; i++)
        if (a[i] > a[i + 1])
            return false;
    return true;
}

void    print_p(std::vector<PairedValue>& p)
{
    std::cout << "P:" << std::endl;
    for (size_t i = 0; i < p.size(); i++)
        std::cout << i << ":" << p[i]._pos << ":" << p[i] << " ";
    std::cout << std::endl;
}

bool    isPositiveNumber(const char* str) {
    const char*     s = str;
    if (!str || !*str)
        return false;
    while (*str)
    {
        if (!isdigit(*str))
            return false;
        ++str;
    }
    return (atoi(s) > 0);
}

void    vector_sort(std::vector<int>& s, std::vector<int>& a, std::vector<int>& S, PmergeMe<std::vector<int>, std::vector<PairedValue> >& p)
{
    for (std::vector<int>::iterator it = s.begin(); it != s.end(); ++it)
        a.push_back(*it);
    p.sort(a, S);

}

void    deque_sort(std::vector<int>& s, std::deque<int>& a, std::deque<int>& S, PmergeMe<std::deque<int>, std::deque<PairedValue> >& p)
{
    for (std::vector<int>::iterator it = s.begin(); it != s.end(); ++it)
        a.push_back(*it);
    p.sort(a, S);
}

int	main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Use: ./exe 1 2 .. " << std::endl;
        return (1);
    }

    int                 e;
    std::vector<int>    a0;
    for (int i = 1; i < argc; i++)
    {
        e = std::atoi(argv[i]);
        if (std::find(a0.begin(), a0.end(), e) != a0.end())
        {
            std::cerr << "Error: Duplicates" << std::endl;
            return (1);
        }
        if (!isPositiveNumber(argv[i]))
        {
            std::cerr << "Error: Non positive number" << std::endl;
            return (1);
        }
        a0.push_back(e);
    }
    std::cout << "Before: ";
    print(a0);

    PmergeMe<std::vector<int>, std::vector<PairedValue> >   p;
    PmergeMe<std::deque<int>, std::deque<PairedValue> >    pD;
    
    clock_t start1 = clock();
    std::vector<int>    a;
    std::vector<int>    S;
    vector_sort(a0, a, S, p);
    clock_t end1 = clock();

    clock_t start2 = clock();
    std::deque<int>    aD;
    std::deque<int>    SD;
    deque_sort(a0, aD, SD, pD);
    clock_t end2 = clock();

    std::cout << "After:  ";
    print(S);
    double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1e6;
    double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1e6;
    std::cout << "Time to process a range of " << S.size() << " elements with std::vector : " << time1 << " us" << std::endl;
    std::cout << "Time to process a range of " << SD.size() << " elements with std::deque  : " << time2 << " us" << std::endl;

    /*
    std::cout << argc - 1 << ": ";
    if (isSorted(S) && isSorted(SD))
        std::cout << "Sorted" << std::endl;
    else
        std::cout << "Not sorted" << std::endl;
    */
    return (0);
}
