/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/06 12:02:43 by minh-ngu         ###   ########.fr       */
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
#include <sys/ioctl.h>

#include <stdlib.h>
#include <cstdio>	// perror
#include <cstring>	// memcpy

#ifndef SERVER_HPP
# define SERVER_HPP

# define BUFFER	1024

#include <iostream>

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

		void			get_listen_sk(void);
		void			bind_addr(void);
		void			accept_client_sk(void);
		bool			select_available_sk(void);
		void			connect_client_sk(int);
		void			server_response(int);
		void			client_request(int);
	public:
		Server();
		Server(const Server&);
		Server &operator=(const Server& op);
		virtual ~Server();

		void    start( void );
};

#endif
