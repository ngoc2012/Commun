/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 17:51:37 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// Class for paired values
template <typename T>
class PairedValue {
public:
    T smaller;
    T larger;

    PairedValue(const T& first, const T& second) : smaller(std::min(first, second)), larger(std::max(first, second)) {}

    // Define comparison operations as needed
    bool operator<(const PairedValue& other) const {
        return smaller < other.smaller;
    }

    bool operator>(const PairedValue& other) const {
        return larger > other.larger;
    }
};

class PmergeMe
{
	private:
        std::vector<int>*    _a;

		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int         binarySearch(std::vector<int>& arr, int target);

	public:
		PmergeMe();
		virtual ~PmergeMe();

        void        insertInSortedArray(std::vector<int>& arr, int num);
        bool        isSorted(std::vector<int>& arr);
        void        print();

        std::vector<int>*   get_a(void) const;
        void                set_a(std::vector<int>*);
};

#endif
