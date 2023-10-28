/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/28 13:54:04 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include <iostream>
# include "ShrubberyCreationForm.hpp"

class ShrubberyCreationForm: public ShrubberyCreationForm
{
	public:
		ShrubberyCreationForm(const ShrubberyCreationForm&);
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm& op);
		ShrubberyCreationForm(const std::string, int, int);
		virtual ~ShrubberyCreationForm();
};

//std::ostream&   operator<<(std::ostream&, const ShrubberyCreationForm&);

#endif
