/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Address.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/03 11:34:01 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef ADDRESS_HPP
# define ADDRESS_HPP

class	Address
{
	private:
		std::vector<Server*>    _servers;
		std::string		        _ip_address;
		short unsigned int	    _port;

		Address(const Address&);
		Address	&operator=(const Address& op);
	public:
		Address();
		virtual ~Address();

        void    push(Server*);
        int	    bind_addr(void);
};

#endif
