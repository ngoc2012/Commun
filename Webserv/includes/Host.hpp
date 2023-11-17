/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Host.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/17 09:18:10 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>

#include <vector>
#include <map>

#include "ConfigurationParser.hpp"

#ifndef HOST_HPP
# define HOST_HPP
# define BUFFER	2048

// Forward declaration
class	Server;
class	ClientRequest;

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

		bool				select_available_sk(void);
		void  				add_new_sk_2_master_set(int, Server*);

		Host();
		Host(const Host&);
		Host &operator=(const Host& op);

	public:
		Host(const char *);
		virtual ~Host();

		void    			start(void);
		void				end(void);
		void				new_client_request_sk(int, Server*);
		void				close_client_sk(int);

		int				get_max_clients(void) const;
		std::map<int, Server*>		_sk_server;
};

#endif
