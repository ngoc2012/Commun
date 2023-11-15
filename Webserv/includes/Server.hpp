/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/15 22:40:23 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Host.hpp"

#ifndef SERVER_HPP
# define SERVER_HPP

class Server
{
	private:
		int			_error;
		Host*			_host;
		std::string		_ip_address;
		short unsigned int	_port;
		int			_listen_sk;

		Server(const Server&);
		Server			&operator=(const Server& op);

	public:
		Server();
		virtual ~Server();

		int			bind_addr(void);

		const char*		get_ip_address(void) const;
		short unsigned int	get_port(void) const;
		int			get_listen_sk(void) const;
		Host*			get_host(void) const;

		void			set_listen_sk(int);
		void			set_ip_address(std::string);
		void			set_port(short unsigned int);
};

#endif
