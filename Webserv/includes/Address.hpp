/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Address.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/04 10:45:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef ADDRESS_HPP
# define ADDRESS_HPP

class	Server;

class	Address
{
	private:
		std::vector<Server*>    _servers;
		std::string		        _ip_address;
		short unsigned int	    _port;

		Address();
		Address(const Address&);
		Address	&operator=(const Address& op);
	public:
		Address(std::string, short unsigned int);
		virtual ~Address();

        void    push(Server*);
        int     listen_socket(Host* host);
        int	    bind_addr(Host* host, int socket);

        //std::string		    get_ip_address(void) const;
        //short unsigned int	get_port(void) const;

        //void                  set_ip_address(std::string);
        //void	            set_port(short unsigned int);
};

#endif
