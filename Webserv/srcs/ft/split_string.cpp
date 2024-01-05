/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:14:49 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/05 21:38:53 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#include "webserv.hpp"

namespace ft {

std::vector<std::string>	split_string(const std::string& input, std::string delimiters)
{
	std::vector<std::string>	tokens;
    std::size_t                 start;
    std::size_t                 end;

    start = 0;
    end = 0;
    while (start < input.size())
    {
		if (delimiters.find(input[start]) != std::string::npos)
        {
            if (end > start)
                tokens.push_back(input.substr(start, end));
            start++;
            end = start;
        }
        else
            end++;
    }
	if (token.length() > 0)
		tokens.push_back(token);
	return (tokens);
}

}
