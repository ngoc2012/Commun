/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 19:13:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// Class for paired values
template <typename T>
class   PairedValue
{
    public:
        T*   smaller;
        T*   larger;

        PairedValue(T& a, T& b)
        {
            if (a > b)
            {
                larger = a;
                smaller = b;
            }
            else
            {
                larger = b;
                smaller = a;
            }
        }

        void    print() { std::cout << "(" << smaller << ", " << larger << ")";}

        bool operator<(const PairedValue& other) const {
            return *larger < *(other.larger);
        }

        bool operator>(const PairedValue& other) const {
            return *larger > *(other.larger);
        }
};

template <typename T>
class PmergeMe
{
	private:
        std::vector<int>*               _a;
        std::vector<PairedValue<T> >    _p;

		PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int         binarySearch(std::vector<int>& arr, int target);
        void        insertInSortedArray(std::vector<int>& arr, int num);

	public:
		PmergeMe(std::vector<T>&);
		virtual ~PmergeMe();

        bool        isSorted(std::vector<int>& arr);
        void        sort();
        void        print();
        void        print_p();

        std::vector<int>*   get_a(void) const;
};

#endif
