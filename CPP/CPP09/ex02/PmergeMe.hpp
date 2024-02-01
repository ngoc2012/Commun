/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/01 13:18:03 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class PmergeMe
{
	private:
		
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int         binarySearch(std::vector<int>& arr, int target, int start, int end);
        void        insertInSortedArray(std::vector<int>& arr, int num, int start, int end);

	public:
        bool        _debug;
        PmergeMe() {_debug = false;}

		virtual     ~PmergeMe() {}

        bool        isSorted(std::vector<int>&);
        void        sort(std::vector<int>&, std::vector<int>&);
        void        print(std::vector<int>&);
        void        print_p(std::map<int, int>&);
};

#endif
