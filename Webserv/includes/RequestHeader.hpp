/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestHeader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/05 12:51:21 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTHEADER_HPP
# define REQUESTHEADER_HPP
 
class	Server;
class	Location;
class	Request;
class	Configuration;
class	Response;

class	RequestHeader
{
	private:
		Host*		    _host;
		std::string*    _str;
		size_t		    _pos;

		RequestHeader(const RequestHeader&);
		RequestHeader		&operator=(const RequestHeader& op);
	public:
		RequestHeader();
		virtual ~RequestHeader();

        bool    parse_method_url_host(std::string&, std::string&, e_method&);
        bool    parse_content_type(Host*, std::string&, std::string&);
        bool    parse_content_length(std::string&, size_t&);

        void	set_host(Host*);
        void    set_str(std::string*);
};

#endif
