/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/28 11:36:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

# include <iostream>
# include "AForm.hpp"

class ShrubberyCreationForm: public AForm
{
	public:
		AForm(const AForm&);
		AForm &operator=(const AForm& op);
		AForm(const std::string, int, int);
		virtual ~AForm();

		std::string	getName( void ) const;
		bool		getSign( void ) const;
		int		getSignGrade( void ) const;
		int		getExecGrade( void ) const;

		void		beSigned( Bureaucrat& );
		void		setSign( void );

		class GradeTooHighException : public std::exception
		{
			public: virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
			public: virtual const char* what() const throw();
		};
};

#std::ostream&   operator<<(std::ostream&, const AForm&);

#endif
