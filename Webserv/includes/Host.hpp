/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Host.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/16 14:47:07 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>

#include <vector>

#include "ClientRequest.hpp"

#ifndef HOST_HPP
# define HOST_HPP
# define BUFFER	2048

// Forward declaration of Class Server
class	Server;

//https://www.ibm.com/docs/en/ztpf/2020?topic=overview-blocking-nonblocking
class	Host
{
	private:

		int				_max_clients;

		int				_sk_ready;
		int				_max_sk;	// Max of all fd
		fd_set              		_master_set;	// Set of all fd
		fd_set              		_working_set;	// Set of active fd
		fd_set              		_server_set;
		std::vector<Server*>		_servers;
		std::vector<ClientRequest*>	_client_requests;
		std::map<int, Server*>		_sk_server;
		std::map<int, ClientRequest*>	_sk_client_request;
		bool				_end_host;

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
		Host(std::string);
		virtual ~Host();

		int				get_max_clients(void) const;

		void				set_end_host(bool);

		void    			add_new_sk_2_master_set(int, Server*);
		void    			start(void);
		void				end(void);
};

#endif
