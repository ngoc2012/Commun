/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/08 15:04:51 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>	// htons
#include <unistd.h>	// close
#include <iostream>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>	// fcntl
#include <sys/ioctl.h>	// fcntl

#include <stdlib.h>
#include <cstdio>	// perror
#include <cstring>	// memcpy
#include "ClientRequest.hpp"

#ifndef SERVER_HPP
# define SERVER_HPP

# define BUFFER	4


//https://www.ibm.com/docs/en/ztpf/2020?topic=overview-blocking-nonblocking

class Server
{
	private:
		int			max_clients;
		short unsigned int	port;
		char			*ip_address;

		int			listen_sk;
		int			sk_ready;
		int			max_sk;
		fd_set              	master_set, working_set;
		bool			end_server;
		ClientRequest		req;

		void			get_listen_sk(void);
		void			bind_addr(void);
		void			accept_client_sk(void);
		bool			select_available_sk(void);
		void			connect_client_sk(int);
		bool			server_response(int);
		bool			client_request(int);
	public:
		Server();
		Server(const Server&);
		Server &operator=(const Server& op);
		virtual ~Server();

		void    start( void );
};

#endif
