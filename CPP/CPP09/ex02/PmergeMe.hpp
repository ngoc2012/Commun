/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 13:45:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

class PmergeMe
{
	private:
        std::vector<int>*    _a;

		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int     PmergeMe::binarySearch(std::vector<int>& arr, int target)
	public:
		PmergeMe();
		virtual ~PmergeMe();

        void        insertInSortedArray(std::vector<int>& arr, int num);
        void        print();

        //std::vector*    get_a(void) const;
        void        set_a(std::vector<int>*);
};

#endif
