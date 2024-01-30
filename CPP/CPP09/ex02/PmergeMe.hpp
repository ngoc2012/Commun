/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/30 09:53:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

// Class for paired values
template <typename T>
class   PairedValue
{
    public:
        T       _smaller;
        T       _larger;
        bool    _nan;

        PairedValue(T& a, T& b)
        {
            if (a > b)
            {
                _larger = a;
                _smaller = b;
            }
            else
            {
                _larger = b;
                _smaller = a;
            }
            _nan = false;
        }

        PairedValue(T& b)
        {
            _larger = b;
            _smaller = b;
            _nan = true;
        }

        void    print() { std::cout << "(" << _smaller << ", " << _larger << ")";}

        bool operator<(const PairedValue& other) const {
            return _larger < other._larger;
        }

        bool operator>(const PairedValue& other) const {
            return _larger > other._larger;
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
        std::vector<T>                  _Y;
		PmergeMe(std::vector<T>&);
		virtual ~PmergeMe();

        bool        isSorted(std::vector<T>& arr);
        void        sort();
        void        print();
        void        print_p();
        void        print_s();
};

#endif
