/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/10 17:34:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

class Configuration
{
	private:
		const char		*_ip_address;
		short unsigned int	_port;
		int			_max_clients;

		Configuration();
		Configuration(const Configuration&);
	public:
		Configuration &operator=(const Configuration& op);
		Configuration(const char*, int);
		virtual ~Configuration();

		char			*get_ip_address(void);
		short unsigned int	get_port(void);
		int			get_max_clients(void);
};

#endif
