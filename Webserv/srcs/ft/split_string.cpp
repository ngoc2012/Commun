/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:14:49 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/05 21:36:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>
#include "webserv.hpp"

namespace ft {

std::vector<std::string>	split_string(const std::string& input, std::string delimiters)
{
	std::vector<std::string>	tokens;
	std::string			        token;
    std::size_t                 start;
    std::size_t                 end;

    start = 0;
    end = 0;
    while (start < input.size())
    {
		if (delimiters.find(input[start]) != std::string::npos)
            start++;
	for (std::size_t i = 0; i < input.length(); ++i)
			token += input[i];
		else
		{
			if (token.length() > 0)
			{
				tokens.push_back(token);
				token.clear();
			}
		}
    }
	if (token.length() > 0)
		tokens.push_back(token);
	return (tokens);
}

}
