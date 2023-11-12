/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/12 08:39:31 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP

class ClientRequest
{
	private:
		std::string	_http_request;
		std::string	_method;
		std::string	_url;

		ClientRequest(const ClientRequest&);
		ClientRequest &operator=(const ClientRequest& op);
	public:
		ClientRequest();
		virtual ~ClientRequest();

		void		clean(void);
		void		set_method(std::string);
		void		set_http_request(std::string);

		std::string	get_http_request(void) const;
};

#endif
