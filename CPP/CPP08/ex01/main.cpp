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
#include <algorithm>

#include "Span.hpp"

int	main(int argc, char **argv)
{
    Span                s(argc - 1);
    std::vector<int>    v;

    for (int i = 1; i < argc; i++)
        v.push_back(std::atoi(argv[i]));

    for (int i = 1; i < argc; i++)
    {
        try { s.addNumber(v.begin(), v.end());}
        catch (std::exception &e) {std::cout << e.what() << std::endl;}
    }

    std::cout << s << std::endl;
    try {
    std::cout << "Shortest span: " << s.shortestSpan() << std::endl;
    std::cout << "Longest span: " << s.longestSpan() << std::endl;
    } catch (std::exception &e) {std::cout << e.what() << std::endl;}

	return (0);
}
