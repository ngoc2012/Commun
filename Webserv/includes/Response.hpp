/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/23 11:21:59 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
 
class	Response
{
	private:
		int		_socket;
		Host*		_host;
		Server*		_server;

		Response();
		Response(const Response&);
		Response &operator=(const Response& op);
	public:
		Response(int, Host*, Server*);
		virtual ~Response();

		void		send(void);
};

#endif
