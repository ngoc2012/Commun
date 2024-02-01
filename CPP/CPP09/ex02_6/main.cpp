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
//#include "PmergeMe.cpp"

int	main(int argc, char **argv)
{
    if (argc < 2)
        std::cout << "Use: ./exe 1 2 .. " << std::endl;
    std::vector<int> a;
    
    for (int i = 1; i < argc; i++)
        a.push_back(std::atoi(argv[i]));
        
    PmergeMe    p;
    //p._debug = true;
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
        

    return (0);
}
