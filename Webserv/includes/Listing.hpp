/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/31 10:19:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef LISTING_HPP
# define LISTING_HPP

class	Listing
{
	private:
		Listing(const Listing&);
		Listing	&operator=(const Listing& op);
	public:
		Listing();
		virtual ~Listing();
};

#endif
