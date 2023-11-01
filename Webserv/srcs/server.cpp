/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 07:27:49 by ngoc             ###   ########.fr       */
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
# define PORT 128

int	main()
{
	int	listen_sk = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sk < 0)
	{
		perror("listen socket() failed");
		exit(-1);
	}
	if (setsockopt(listen_sk, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on)) < 0)
	{
		perror("reusable socket: setsockopt() failed");
		close(listen_sk);
		exit(-1);
	}
	int    on = 1;
	//The  second  argument  is  a  device-dependent  request code.  The third argument is an untyped pointer to memory.  It's traditionally char *argp (from the days before void *  was  valid  C), and will be so named for this discussion.
	if (ioctl(listen_sk, FIONBIO, (char *)&on) < 0)
	{
		perror("non-blocking socket: ioctl() failed");
		close(listen_sk);
		exit(-1);
	}
	struct sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4242);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
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
