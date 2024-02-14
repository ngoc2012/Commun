/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 09:51:02 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int	main(int argc, char **argv)
{
    Span    s(argc - 1);

    for (int i = 1; i < argc; i++)
        s.addNumber(std::atoi(argv[i]));
    std::cout << s << std::endl;
    std::cout << "Shortest span: " << s.shortestSpan() << std::endl;
    std::cout << "Longest span: " << s.longestSpan() << std::endl;

	return (0);
}
