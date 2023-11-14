/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/14 18:27:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef SERVER_HPP
# define SERVER_HPP

class Server
{
	private:
		std::string		*_ip_address;
		short unsigned int	_port;
		int			_max_clients;

		int			_listen_sk;

	public:
		Server();
		Server(const Server&);
		Server &operator=(const Server& op);
		Server(const char*, int);
		virtual ~Server();

		char			*get_ip_address(void) const;
		short unsigned int	get_port(void) const;
		int			get_max_clients(void) const;
		int			get_listen_sk(void) const;

		void			set_listen_sk(int);
};

#endif
