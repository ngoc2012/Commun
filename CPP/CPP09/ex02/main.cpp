/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 19:39:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "PmergeMe.hpp"
#include "PmergeMe.cpp"

int	main(int argc, char **argv)
{
    std::vector<int> a;
    for (int i = 1; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
    PmergeMe<int>    p(a);
    p.print();
    p.sort();
    std::cout << "========================================================" << std::endl;
    p.print_p();
    std::cout << "========================================================" << std::endl;
    std::sort(p._p.begin(), p._p.end());
    std::cout << "========================================================" << std::endl;
    p.print_p();
    //std::sort(a.begin(), a.end());
    //p.print();
    //if (p.isSorted(a))
    //    std::cout << "Sorted" << std::endl;
    //else
    //    std::cout << "Not sorted" << std::endl;

    return (0);
}
