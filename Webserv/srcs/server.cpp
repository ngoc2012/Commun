/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 22:01:42 by ngoc             ###   ########.fr       */
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
#include <cstdio.h>

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

	fd_set              master_set, working_set;
	FD_ZERO(&master_set);
	int	max_sk = listen_sk;
	FD_SET(listen_sk, &master_set);

	// Time out 3 minutes
	//struct timeval      timeout;
	//timeout.tv_sec  = 3 * 60;
	//timeout.tv_usec = 0;

	end_server = 0;
	do
	{
		memcpy(&working_set, &master_set, sizeof(master_set));
		/*
		select()  allows  a  program to monitor multiple file descriptors, waiting until one or more of the file descriptors become "ready" for some class of I/O operation (e.g., input possible).   A file  descriptor is considered ready if it is possible to perform a corresponding I/O operation (e.g., read(2), or a sufficiently small write(2)) without blocking
		nfds   This  argument should be set to the highest-numbered file descriptor in any of the three sets, plus 1.  The indicated file descriptors in each set are checked, up to this  limit (but see BUGS).
		timeout
              The  timeout  argument  is a timeval structure (shown below) that specifies the interval that select() should block waiting for a file descriptor to become ready.  The call will block until either:
              • a file descriptor becomes ready;
              • the call is interrupted by a signal handler; or
              • the timeout expires.
              Note  that  the timeout interval will be rounded up to the system clock granularity, and kernel scheduling delays mean that the blocking interval may overrun by a small amount.
              If both fields of the timeval structure are zero,  then  select()  returns  immediately.  (This is useful for polling.)
              If  timeout  is  specified  as NULL, select() blocks indefinitely waiting for a file de‐ scriptor to become ready.
		*/
		//int	sk_ready = select(max_sk + 1, &working_set, NULL, NULL, &timeout);
		int	sk_ready = select(max_sk + 1, &working_set, NULL, NULL, NULL);
		if (sk_ready < 0)
		{
			perror("working set select() failed");
			break;
		}
		//if (!sk_ready)
		//{
		//	perror("working set select() time out.");
		//	break;
		//}
		for (int i = 0; i <= max_sk && sk_ready > 0; ++i)
		{
			if (FD_ISSET(i, &working_set))
			{
				sk_ready = -1;
				if (i == listen_sk)
				{
					//Accept all the new connections, create a new socket and add to the master set
					do
					{
						int	new_sk = accept(listen_sk, NULL, NULL);
						if (new_sk < 0)
						{
							if (errno != EWOULDBLOCK)
							{
								perror("  accept() failed");
								end_server = TRUE;
							}
							break;
						}
						std::cout << "  New incoming connection - " << new_sk << std::endl;
						FD_SET(new_sk, &master_set);
						if (new_sk > max_sk)
							max_sk = new_sk;
					} while (new_sk != -1)
				}
			}
			else
			{
				int	close_conn = 0;
				do
				{
					//Receive data from client
					int	ret = recv(s_fd, response, BUFFER, 0);
					if (ret < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							perror("  recv() failed");
							close_conn = TRUE;
						}
						break;
					}
					if (ret == 0)
					{
						std::cout << "  Connection closed" << std::endl;
						close_conn = TRUE;
						break;
					}
					response[ret] = 0;
					std::cout << response ;
					//while (ret && ret > 0)
					//{
					//	ret = recv(s_fd, response, BUFFER, 0);
					//	response[ret] = 0;
					//	std::cout << response ;
					//}

					//Send back data
					char	buffer[] = "data";
					rc = send(i, buffer, strlen(buffer), 0);
					if (rc < 0)
					{
						perror("  send() failed");
						close_conn = TRUE;
						break;
					}
					std::cout << std::endl;

				} while (1);

				if (close_conn)
				{
					close(i);
					FD_CLR(i, &master_set);
					if (i == max_sk)
						while (!FD_ISSET(max_sk, &master_set))
							max_sk -= 1;
				}
			}
		}
	} while (!end_server);

	for (int i = 0; i <= max_sk; ++i)
	{
		if (FD_ISSET(i, &master_set))
			close(i);
	}
	std::cout << "End server" << std::endl;
}
