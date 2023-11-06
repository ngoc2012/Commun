/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/06 18:06:51 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	char	ip[] = "127.0.0.1";
	port = 4242;
	ip_address = ip;
	max_clients = 128;
}
Server::Server(const Server& src) { *this = src; }
Server&	Server::operator=( Server const & src )
{
	(void) src;
	return (*this);
}
Server::~Server() {}

void	Server::get_listen_sk(void)
{
	listen_sk = socket(AF_INET, SOCK_STREAM, 0);
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
	if (ioctl(listen_sk, FIONBIO, (char *)&on) < 0)
	{
		perror("non-blocking socket: ioctl() failed");
		close(listen_sk);
		exit(-1);
	}
}

void	Server::bind_addr(void)
{
	struct sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip_address);

	std::cout << "Listening at " << ip_address << ":" << port << std::endl;

	if (bind(listen_sk, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		close(listen_sk);
		exit(-1);
	}

	//The  backlog  argument defines the maximum length to which the queue of pending connections for sockfd may grow.
	if (listen(listen_sk, max_clients) < 0)
	{
		perror("listen() failed");
		close(listen_sk);
		exit(-1);
	}

}

void	Server::accept_client_sk(void)
{
	int	new_sk;

	//Accept all the new connections, create a new socket and add to the master set
	std::cout << "Listening socket is readable" << std::endl;
	do
	{
		new_sk = accept(listen_sk, NULL, NULL);
		if (new_sk < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("accept() failed");
				end_server = true;
			}
			break;
		}
		std::cout << "  New incoming connection - " << new_sk << std::endl;
		FD_SET(new_sk, &master_set);
		if (new_sk > max_sk)
			max_sk = new_sk;
	} while (new_sk != -1);
}

bool	Server::select_available_sk(void)
{
	// Time out 3 minutes
	//struct timeval      timeout;
	//timeout.tv_sec  = 3 * 60;
	//timeout.tv_usec = 0;
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
	std::cout << "Waiting on select() ..." << std::endl;
	sk_ready = select(max_sk + 1, &working_set, NULL, NULL, NULL);
	if (sk_ready < 0)
	{
		perror("working set select() failed");
		return (false);
	}
	//if (!sk_ready)
	//{
	//	perror("working set select() time out.");
	//	break;
	//}
	return (true);
}

bool	Server::server_response(int i)
{
	//Send back data
	const char* httpResponse =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Connection: close\r\n"  // Close the connection after this response
		"\r\n"  // End of headers
		"<link rel=\"icon\" href=\"data:,\">"
		"<html><body><h1>Hello, client!</h1></body></html>";
	if (send(i, httpResponse, strlen(httpResponse), 0) < 0)
	{
		perror("  send() failed");
		//close_conn = 1;
		//break;
	}
	std::cout << "Data sent" << std::endl;
	return (true);
}

bool	Server::client_request(int i)
{
	char	response[BUFFER + 1];
	int	ret = 1;
	std::string	s = "";

	//Receive data from client
	std::cout << "Receive data from client" << std::endl;
	req.clean();
	//while (ret && ret > 0)
	//{
		ret = recv(i, response, BUFFER, 0);
		std::cout << "ret: " << ret << std::endl;
		if (ret < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("  recv() failed");
				//close_conn = 1;
			}
			return (false);
		}
		else if (ret == 0)
		{
			std::cout << "Connection closed" << std::endl;
			//close_conn = 1;
			//break;
		}
		else
		{
			response[ret] = 0;
			s += std::string(response);
		}
	//}
	req.setHttpRequest(s);
	std::cout << "Client send: \n"
		<< "=============================================\n"
		<< req.getHttpRequest();
	std::cout 
		<< "============================================="
		<< std::endl;
	return (true);
}

void	Server::connect_client_sk(int	i)
{
	std::cout << "Socket " << i << " is readable." << std::endl;
	//int	close_conn = 0;
	//do
	//{
		client_request(i);
		server_response(i);
	
	//} while (1);
	
	//if (close_conn)
	//{
		close(i);
		FD_CLR(i, &master_set);
		if (i == max_sk)
			while (!FD_ISSET(max_sk, &master_set))
				max_sk -= 1;
	//}
}
void	Server::start(void)
{
	get_listen_sk();
	bind_addr();

	FD_ZERO(&master_set);
	max_sk = listen_sk;
	FD_SET(listen_sk, &master_set);

	end_server = false;
	do
	{
		memcpy(&working_set, &master_set, sizeof(master_set));
		if (select_available_sk() == false)
			break;
		for (int i = 0; i <= max_sk && sk_ready > 0; ++i)
			if (FD_ISSET(i, &working_set))
			{
				sk_ready--;
				if (i == listen_sk)
					accept_client_sk();
				else
					connect_client_sk(i);
			}
	} while (end_server == false);

	for (int i = 0; i <= max_sk; ++i)
	{
		if (FD_ISSET(i, &master_set))
			close(i);
	}
	std::cout << "End server" << std::endl;
}
