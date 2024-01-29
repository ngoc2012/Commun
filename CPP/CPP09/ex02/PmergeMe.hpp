/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 18:20:33 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// Class for paired values
template <typename T>
class   PairedValue
{
    public:
        T smaller;
        T larger;

        // Define comparison operations as needed
        bool operator<(const PairedValue& other) const {
            return larger < other.larger;
        }

        bool operator>(const PairedValue& other) const {
            return larger > other.larger;
        }
};

class PmergeMe
{
	private:
        std::vector<int>*    _a;

		PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int         binarySearch(std::vector<PairedValue<int> int>& arr, int target);

	public:
		PmergeMe(std::vector<int>&);
		virtual ~PmergeMe();

        void        insertInSortedArray(std::vector<PairedValue<int> >& arr, int num);
        bool        isSorted(std::vector<PairedValue<int> int>& arr);
        void        print();

        std::vector<int>*   get_a(void) const;
        void                set_a(std::vector<int>*);
};

#endif
