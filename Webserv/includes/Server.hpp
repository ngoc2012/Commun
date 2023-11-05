/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/05 21:53:35 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>	// htons
#include <unistd.h>	// close
#include <iostream>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <stdlib.h>
#include <cstdio> // perror
#include <cstring> // memcpy

# define BUFFER	1028
# define MAX_CLIENTS 128
# define PORT 4242
# define IP_ADDRESS "127.0.0.1"

#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>

class Server
{
	public:
		Server();
		Server(const Server&);
		Server &operator=(const Server& op);
		virtual ~Server();

		void    start( void );
};

#endif
