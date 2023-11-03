/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 09:10:25 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

#include <iostream>
#include <string>

class Convert
{
	private:
		int	fp;
		int	fb;
	public:
		Convert();
		Convert(const Convert&);
		Convert &operator=(const Convert& op);
		virtual ~Convert();

		void     getChar( std::string );
		void     getInt( std::string );
		void     getFloat( std::string );
		void     getDouble( std::string );
};

#endif
