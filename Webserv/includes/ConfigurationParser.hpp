/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 17:36:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"

#ifndef CONFIGURATIONPARSER_HPP
# define CONFIGURATIONPARSER_HPP

class ConfigurationParser
{
	private:
		const char*	keys_level_0[] = {"server"}
		const char*	keys_level_1[] = {"listen", "server_name", "location"}
		const char*	keys_location[] = {"listen", "server_name", "location"}

		ConfigurationParser(const ConfigurationParser&);
		ConfigurationParser &operator=(const ConfigurationParser& op);
	public:
		ConfigurationParser();
		std::vector<Server>	get_servers(const char *);
		virtual			~ConfigurationParser();
};

#endif
