/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigurationParser.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 17:06:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"

#ifndef CONFIGURATIONPARSER_HPP
# define CONFIGURATIONPARSER_HPP

class ConfigurationParser
{
	private:
		ConfigurationParser();
	public:
		ConfigurationParser(const ConfigurationParser&);
		ConfigurationParser &operator=(const ConfigurationParser& op);
		ConfigurationParser(const char*, int);
		virtual ~ConfigurationParser();

		char			*get_ip_address(void) const;
		short unsigned int	get_port(void) const;
		int			get_max_clients(void) const;
		int			get_listen_sk(void) const;

		void			set_listen_sk(int);
};

#endif
