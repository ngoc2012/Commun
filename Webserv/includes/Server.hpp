/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/10 15:59:17 by ngoc             ###   ########.fr       */
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

#include "ClientRequest.hpp"
#include "Configuration.hpp"

#ifndef SERVER_HPP
# define SERVER_HPP
# define BUFFER	4

//https://www.ibm.com/docs/en/ztpf/2020?topic=overview-blocking-nonblocking
class Server
{
	private:

		int			_listen_sk;
		int			_sk_ready;
		int			_max_sk;
		fd_set              	_master_set;
		fd_set              	_working_set;
		ClientRequest		_request;
		vector<Configuration>	&_confs;
		//bool			_end_server;

		void			get_listen_sk(void);
		void			bind_addr(void);
		void			accept_client_sk(void);
		bool			select_available_sk(void);
		void			connect_client_sk(int);
		void			server_response(int);
		void			get_client_request(int);
		void			close_connection(int);
		void			end_server(void);
		Server(const Server&);
		Server &operator=(const Server& op);
	public:
		Server();
		virtual ~Server();

		void    start( void );
		void	set_confs(vector<Configuration>&);
};

#endif
