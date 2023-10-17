/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/17 16:57:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>	// htons
#include <iostream>

# define SA struct sockaddr_in
# define BUFFER	1028

int	main()
{
	int	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	SA	addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int	c = connect(s_fd, const (SA *) &addr, sizeof(addr)); 
	if (c < 0)
		std::cerr << "Client : connect error" << std::endl;
	char	response[BUFFER + 1];
	int	ret = recv(s_fd, response, BUFFER, 0);
	response[ret] = 0;
	std::cout << response ;
	while (ret && ret > 0)
	{
		ret = recv(s, response, BUFFER, 0);
		response[ret] = 0;
		std::cout << response ;
	}
	std::cout << std::endl;
}
