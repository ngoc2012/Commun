/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 13:19:03 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

class PmergeMe
{
	private:
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);
	public:
		PmergeMe();
		virtual ~PmergeMe();

		PmergeMe*	generate(void);
		void	identify(PmergeMe* b);
		void	identify(PmergeMe& b);
};

class A: public PmergeMe {};
class B: public PmergeMe {};
class C: public PmergeMe {};

#endif
