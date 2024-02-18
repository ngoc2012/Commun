/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 10:25:58 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "Span.hpp"

int	main(int argc, char **argv)
{
    Span sp = Span(5);
    
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    try
    {
        sp.addNumber(12);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
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
