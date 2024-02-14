/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 09:03:02 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int	main(int argc, char **argv)
{
    std::vector<int>	v;

    for (int i = 1; i < argc; i++)
    {
        int     n = std::atoi(argv[i]);
    }
        std::cout << easyfind(v, n) << " found in vector" << std::endl;

	return (0);
}
