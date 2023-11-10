/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/10 09:21:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

class Configuration
{
	private:
		int			_max_clients;
		short unsigned int	_port;
		const char		*_ip_address;

		Configuration();
		Configuration(const Configuration&);
		Configuration &operator=(const Configuration& op);
	public:
		Configuration(const char*, int);
		virtual ~Configuration();

		char			*get_ip_address(void);
		short unsigned int	get_port();
};

#endif
