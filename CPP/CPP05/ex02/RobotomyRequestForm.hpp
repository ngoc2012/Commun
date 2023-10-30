/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/30 10:45:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include <cstdlib>
# include "AForm.hpp"

class RobotomyRequestForm: public AForm
{
	private:
		void		beExecuted() const;
	public:
		RobotomyRequestForm(const RobotomyRequestForm&);
		RobotomyRequestForm &operator=(const RobotomyRequestForm& op);
		RobotomyRequestForm(const std::string);
		virtual ~RobotomyRequestForm();
};

#endif
