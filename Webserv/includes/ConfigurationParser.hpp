/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/15 08:59:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

#include "Server.hpp"
#include "main.hpp"

#ifndef CONFIGURATIONPARSER_HPP
# define CONFIGURATIONPARSER_HPP

class ConfigurationParser
{
	private:
		static const char*	keys_server[];
		static const char*	keys_location[];

		ConfigurationParser();
		ConfigurationParser(const ConfigurationParser&);
		ConfigurationParser	&operator=(const ConfigurationParser& op);
	public:
		ConfigurationParser(std::vector<Server*>& servers, const char* conf);
		virtual			~ConfigurationParser();

		int			listen(Server*, std::string);
};

#endif
