/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/23 15:38:19 by ngoc             ###   ########.fr       */
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
		ClientRequest*	_request;

		Response();
		Response(const Response&);
		Response &operator=(const Response& op);
	public:
		Response(int, Host*, Server*, ClientRequest*);
		virtual ~Response();

		void		send(void);
};

#endif
