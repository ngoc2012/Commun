/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/02 06:43:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>	// htons
#include <unistd.h>	// close
#include <iostream>
#include <cstring>
#include <cstdio>

# define BUFFER	1028

int	main()
{
	int	sk = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4242);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	std::cout << "Create connect socket" << std::endl;
	int	c = connect(sk, (struct sockaddr*)&addr, sizeof(addr)); 
	if (c < 0)
		std::cerr << "Client : connect error" << std::endl;

	char	buffer[] = "client data";
	if (send(sk, buffer, strlen(buffer), 0) < 0)
		perror("  send() failed");

	char	response[BUFFER + 1];

	std::cout << "Receive response" << std::endl;

	int	ret = recv(sk, response, BUFFER, 0);
	response[ret] = 0;
	std::cout << "Server send: " << response << std::endl;
	//std::cout << std::endl;
	//c = connect(sk, (struct sockaddr*)&addr, sizeof(addr)); 
	//ret = recv(sk, response, BUFFER, 0);
	//while (ret && ret > 0)
	//{
	//	ret = recv(sk, response, BUFFER, 0);
	//	response[ret] = 0;
	//	std::cout << response ;
	//}

	close(sk);
	std::cout << "End client" << std::endl;
}
