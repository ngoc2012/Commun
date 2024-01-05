/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/05 12:45:52 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHEADER_HPP
# define REQUESTHEADER_HPP
 
class	Server;
class	Location;
class	Request;
class	Configuration;
class	Response;

class	Header
{
	private:
		size_t		    _pos;
		std::string*    _str;

		Header();
		Header(const Header&);
		Header		&operator=(const Header& op);
	public:
		Header(Response*, std::string);
		virtual ~Header();

        bool    parse_method_url_host(std::string&, std::string&, e_method&);
        bool    parse_content_type(Host*, std::string&, std::string&);
        bool    parse_content_length(std::string&, size_t&);

		std::string*    _str;
};

#endif
