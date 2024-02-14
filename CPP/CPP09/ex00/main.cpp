/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 17:42:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <algorithm>

#include "Span.hpp"

int	main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./btc filename." << std::endl;
        return (1);
    }
    struct stat	info;
    if (stat(argv[1], &info) || S_ISDIR(info.st_mode))
    {
        std::cerr << "Error: File does not exist." << std::endl;
        return (1);
    }

        
    Span sp = Span(5);
    
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;

    Span                s(argc - 1);
    std::vector<int>    v;

    for (int i = 1; i < argc; i++)
        v.push_back(std::atoi(argv[i]));

    try {
        s.addNumber(v.begin(), v.end());
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    
    std::cout << s << std::endl;
    try {
        std::cout << "Shortest span: " << s.shortestSpan() << std::endl;
        std::cout << "Longest span: " << s.longestSpan() << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        s.addNumber(-14);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        std::cout << "Shortest span: " << s.shortestSpan() << std::endl;
        std::cout << "Longest span: " << s.longestSpan() << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    
	return (0);
}
