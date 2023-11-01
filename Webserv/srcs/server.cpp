/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 08:02:19 by ngoc             ###   ########.fr       */
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

# define BUFFER	1028
# define MAX_CLIENTS 128
# define PORT 4242
# define IP_ADDRESS "127.0.0.1"

int	main()
{
	int	listen_sk = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sk < 0)
	{
		perror("listen socket() failed");
		exit(-1);
	}
	int    on = 1;
	//To manipulate options at the sockets API level, level is specified as SOL_SOCKET.
	/*
	Socket options can be set at different levels, depending on the scope of their effect. The two most common levels are:

    Socket-Level Options (SOL_SOCKET): These options apply to the socket as a whole and control general socket behavior. They affect how the socket operates at the transport layer of the network stack. Some common socket-level options include:
        SO_REUSEADDR: Allows multiple sockets to bind to the same local address and port.
        SO_KEEPALIVE: Enables the sending of keep-alive messages to check if the connection is still alive.
        SO_RCVBUF and SO_SNDBUF: Control the receive and send buffer sizes for the socket.
        SO_LINGER: Specifies the behavior of the socket when it is closed (e.g., whether to wait for unsent data to be sent).

    IP-Level Options (SOL_IP or IPPROTO_IP): These options apply specifically to IP (Internet Protocol) sockets and control aspects related to IP networking. They affect how the IP layer handles the data. Some common IP-level options include:
        IP_TTL: Sets the Time-To-Live (TTL) value for outgoing IP packets.
        IP_TOS: Specifies the Type of Service (TOS) field for outgoing IP packets.
        IP_MULTICAST_TTL: Sets the TTL for multicast packets.
        IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP: Used for joining and leaving multicast groups.
	*/
	//The arguments optval and optlen are used to access option values for  setsockopt(). 
	if (setsockopt(listen_sk, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on)) < 0)
	{
		perror("reusable socket: setsockopt() failed");
		close(listen_sk);
		exit(-1);
	}
	//The  second  argument  is  a  device-dependent  request code.  The third argument is an untyped pointer to memory.  It's traditionally char *argp (from the days before void *  was  valid  C), and will be so named for this discussion.
	//When FIONBIO is set, the socket is marked nonblocking
	//https://www.ibm.com/docs/en/ztpf/2020?topic=overview-blocking-nonblocking
	if (ioctl(listen_sk, FIONBIO, (char *)&on) < 0)
	{
		perror("non-blocking socket: ioctl() failed");
		close(listen_sk);
		exit(-1);
	}

	struct sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

	if (bind(listen_sk, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		close(listen_sk);
		exit(-1);
	}

	//The  backlog  argument defines the maximum length to which the queue of pending connections for sockfd may grow.
	if (listen(listen_sk, MAX_CLIENTS) < 0)
	{
		perror("listen() failed");
		close(listen_sd);
		exit(-1);
	}
	int	c = connect(s_fd, (struct sockaddr*)&addr, sizeof(addr)); 
	if (c < 0)
		std::cerr << "Client : connect error" << std::endl;
	char	response[BUFFER + 1];
	int	ret = recv(s_fd, response, BUFFER, 0);
	std::cout << "ret = " << ret << std::endl;
	response[ret] = 0;
	std::cout << response ;
	//std::cout << std::endl;
	//c = connect(s_fd, (struct sockaddr*)&addr, sizeof(addr)); 
	ret = recv(s_fd, response, BUFFER, 0);
	std::cout << "ret = " << ret << std::endl;
	response[ret] = 0;
	std::cout << response ;
	//while (ret && ret > 0)
	//{
	//	ret = recv(s_fd, response, BUFFER, 0);
	//	response[ret] = 0;
	//	std::cout << response ;
	//}
	std::cout << std::endl;
	close(s_fd);
	std::cout << "End client" << std::endl;
}
