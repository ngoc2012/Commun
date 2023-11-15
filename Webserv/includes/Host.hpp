/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Host.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/15 21:28:35 by ngoc             ###   ########.fr       */
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
#include "Server.hpp"

#ifndef HOST_HPP
# define HOST_HPP
# define BUFFER	2048

//https://www.ibm.com/docs/en/ztpf/2020?topic=overview-blocking-nonblocking
class Host
{
	private:

		int				_max_clients;

		int				_sk_ready;
		int				_max_sk;
		fd_set              		_master_set;
		fd_set              		_working_set;
		std::vector<Server*>*		_servers;
		std::vector<ClientRequest>	_client_requests;
		bool				_end_host;

		void				get_listen_sk(Server*);
		void				bind_addr(Server*);
		void				accept_client_sk(int);
		bool				select_available_sk(void);
		void				connect_client_sk(int);
		void				server_response(int);
		void				get_client_request(int);
		void				close_connection(int);
		void				connect_sk(int);
		void				close_all_listen_sk(void);

		Host();
		Host(const Host&);
		Host &operator=(const Host& op);

	public:
		Host(std::vector<Server*>*);
		virtual ~Host();

		//std::vector<Server*>&		get_servers(void) const;

		void				set_end_host(bool);

		void    			start(void);
		void				end(void);
};

#endif
