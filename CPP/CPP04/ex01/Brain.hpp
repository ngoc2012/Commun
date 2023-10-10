/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 13:03:26 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP
# define MAX_BRAIN 100

#include <iostream>

class Brain
{
	private:
		std::string	ideas[MAX_BRAIN];
	public:
		Brain();
		Brain(const Brain&);
		Brain &operator=(const Brain& op);
		virtual ~Brain();

		void	show(void) const;
};

#endif
