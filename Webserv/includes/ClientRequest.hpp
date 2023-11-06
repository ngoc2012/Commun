/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/06 12:22:59 by minh-ngu         ###   ########.fr       */
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

class ClientRequest
{
	private:
		std::string	httpRequest;
	public:
		ClientRequest();
		ClientRequest(const ClientRequest&);
		ClientRequest &operator=(const ClientRequest& op);
		virtual ~ClientRequest();

		void    start( void );
};

#endif
