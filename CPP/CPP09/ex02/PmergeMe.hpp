/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 21:19:33 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// Class for paired values
template <typename T>
class   PairedValue
{
    public:
        T   smaller;
        T   larger;

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
            return larger < other.larger;
        }

        bool operator>(const PairedValue& other) const {
            return larger > other.larger;
        }
};

//std::ostream& operator<<(std::ostream& s, PairedValue

template <typename T>
class PmergeMe
{
	private:
        std::vector<T>*                   _a;

		PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int         binarySearch(std::vector<T>& arr, T target);
        void        insertInSortedArray(std::vector<T>& arr, T num);

	public:
        std::vector<PairedValue<T> >    _p;
        std::vector<T>                  _S;
		PmergeMe(std::vector<T>&);
		virtual ~PmergeMe();

        bool        isSorted(std::vector<T>& arr);
        void        sort();
        void        print();
        void        print_p();
};

#endif
