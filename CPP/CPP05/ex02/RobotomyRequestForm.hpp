/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/30 08:59:02 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

# include <cstdlib>
# include "AForm.hpp"

class RobotmyRequestForm: public AForm
{
	private:
		void		beExecuted() const;
	public:
		RobotmyRequestForm(const RobotmyRequestForm&);
		RobotmyRequestForm &operator=(const RobotmyRequestForm& op);
		RobotmyRequestForm(const std::string);
		virtual ~RobotmyRequestForm();
};

#endif
