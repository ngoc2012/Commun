/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:14:49 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 22:41:18 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>

std::vector<std::string>	split_string(const std::string& input, std::string delimiters)
{
	std::vector<std::string>	tokens;
	std::string			token;

	for (std::size_t i = 0; i < input.length(); ++i)
		if (delimiters.find(input[i]) == std::string::npos)
			token += input[i];
		else
		{
			if (token.length() > 0)
			{
				tokens.push_back(token);
				token.clear();
			}
		}
	tokens.push_back(token);
	return (tokens);
}
