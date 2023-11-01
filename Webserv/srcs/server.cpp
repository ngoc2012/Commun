/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/01 05:59:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>	// htons
#include <unistd.h>	// close
#include <iostream>

# define BUFFER	1028
# define MAX_CLIENTS 128
# define PORT 128

int	main()
{
	int	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
	{
		perror("socket() failed");
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
