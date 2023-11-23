/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Host.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/23 17:55:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

#ifndef HOST_HPP
# define HOST_HPP

// Forward declaration
class	Server;
class	ClientRequest;
class	Response;
class	ConfigurationParser;

//https://www.ibm.com/docs/en/ztpf/2020?topic=overview-blocking-nonblocking
class	Host
{
	private:

		int				_max_clients;
		size_t				_client_max_body_size;
		size_t				_client_body_buffer_size;

		bool				_parser_error;

		int				_sk_ready;
		int				_max_sk;		// Max of all fd
		fd_set              		_master_read_set;	// Set of all read fd
		fd_set              		_master_write_set;	// Set of all read fd
		fd_set              		_read_set;		// Set of active read fd
		fd_set              		_write_set;		// Set of active write fd
		fd_set              		_server_set;
		std::vector<Server*>		_servers;
		std::map<int, Response*>	_sk_response;
		std::map<int, Server*>		_sk_server;
		std::map<int, ClientRequest*>	_sk_client_request;

		bool				select_available_sk(void);
		void  				add_sk_2_master_read_set(int, Server*);

		Host();
		Host(const Host&);
		Host &operator=(const Host& op);

	public:
		Host(const char *);
		virtual ~Host();

		void    		start(void);
		void			new_client_request_sk(int, Server*);
		void			new_response_sk(int, Server*, ClientRequest*);
		void			close_client_sk(int);
		void			delete_response(int);
		bool			check_servers_conf(void);

		int			get_max_clients(void) const;
		std::map<int, Server*>	get_sk_server(void) const;
		size_t			get_client_max_body_size(void) const;
		size_t			get_client_body_buffer_size(void) const;

		void			set_client_max_body_size(size_t);
		void			set_client_body_buffer_size(size_t);
		void			set_parser_error(bool);
};

#endif
