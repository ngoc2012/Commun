/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/17 16:24:53 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>	// htons
#include <ostream>

# define SA struct sockaddr_in
# define BUFFER	1028

int	main()
{
	int	s = socket(AF_INET, SOCK_STREAM, 0);
	SA	addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int	c = connect(s_fd, (SA *) &addr, sizeof(addr)); 
	if (c < 0)
		printf("Client : connect error\n");
	char	response[BUFFER + 1];
	int	ret = recv(s, response, BUFFER, 0);
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
