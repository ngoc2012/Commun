/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Host.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 09:21:42 by ngoc             ###   ########.fr       */
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

#include "ClientRequest.hpp"
#include "Configuration.hpp"

#ifndef SERVER_HPP
# define SERVER_HPP
# define BUFFER	2048

//https://www.ibm.com/docs/en/ztpf/2020?topic=overview-blocking-nonblocking
class Host
{
	private:

		//int				_listen_sk;
		int				_sk_ready;
		int				_max_sk;
		fd_set              		_master_set;
		fd_set              		_working_set;
		std::vector<Configuration>	*_confs;
		std::vector<ClientRequest>	*_client_requests;
		bool				_end_server;

		void			get_listen_sk(Configuration&);
		void			bind_addr(Configuration&);
		void			accept_client_sk(int);
		bool			select_available_sk(void);
		void			connect_client_sk(int);
		void			server_response(int);
		void			get_client_request(int);
		void			close_connection(int);
		void			connect_sk(int);

		Host();
		Host(const Host&);
		Host &operator=(const Host& op);

	public:
		Host(std::vector<Configuration>*);
		virtual ~Host();

		void				set_end_server(bool);

		std::vector<Configuration>	*get_confs(void) const;
		void    			start(void);
		void				end(void);
};

#endif
