/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/10 09:13:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

class Configuration
{
	private:
		std::string	_http_request;
		std::string	_method;
		std::string	_url;

		Configuration(const Configuration&);
		Configuration &operator=(const Configuration& op);
	public:
		Configuration();
		virtual ~Configuration();

		void		clean(void);
		void		set_http_request(std::string);

		std::string	get_http_request(void);
};

#endif
