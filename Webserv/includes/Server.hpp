/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/16 10:37:43 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>	// htons
#include <unistd.h>	// close
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>	// fcntl
#include <cstdio>	// perror
#include <cstring>	// memcpy

#include <iostream>
#include <vector>

#ifndef SERVER_HPP
# define SERVER_HPP

// Forward declaration
class	Host;

class	Server
{
	private:
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
		int			new_listen_sk(void);

		const char*		get_ip_address(void) const;
		short unsigned int	get_port(void) const;
		int			get_listen_sk(void) const;
		Host*			get_host(void) const;

		void			set_listen_sk(int);
		void			set_ip_address(std::string);
		void			set_port(short unsigned int);
};

#endif
