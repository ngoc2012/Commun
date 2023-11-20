/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/20 11:53:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>

#include <iostream>
#include <vector>
#include <fstream>

#include "Server.hpp"
#include "main.hpp"

#ifndef CONFIGURATIONPARSER_HPP
# define CONFIGURATIONPARSER_HPP

class ConfigurationParser
{
	private:
		int			err;
		static const char*	keys_server[];
		static const char*	keys_location[];

		ConfigurationParser();
		ConfigurationParser(const ConfigurationParser&);
		ConfigurationParser	&operator=(const ConfigurationParser& op);
	public:
		ConfigurationParser(std::vector<Server*>& servers, Host&, const char* conf);
		virtual			~ConfigurationParser();

		int			listen(Server*, std::vector<std::string>);
		void			conf_file_error(std::string, int);
		std::string		remove_comments(std::string&);
		std::string		remove_spaces_end(std::string&);
		bool			server_parser(std::string, Server&, std::vector<std::string>&);
		bool			host_parser(std::string, Server&, std::vector<std::string>&);
};

#endif
