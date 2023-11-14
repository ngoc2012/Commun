/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 17:50:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"

#ifndef CONFIGURATIONPARSER_HPP
# define CONFIGURATIONPARSER_HPP

class ConfigurationParser
{
	private:
		static const char*	keys_level_0[] = {"server"}
		static const char*	keys_level_1[] = {"listen", "server_name", "location"}
		static const char*	keys_location[] = {"listen", "server_name", "location"}

		ConfigurationParser();
		ConfigurationParser(const ConfigurationParser&);
		ConfigurationParser &operator=(const ConfigurationParser& op);
	public:
		ConfigurationParser(std::vector<Server>& servers, const char conf*);
		virtual			~ConfigurationParser();
};

#endif