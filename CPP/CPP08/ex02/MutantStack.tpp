#include "MutantStack.hpp"

template <typename T>
MutantStack& MutantStack::operator=(const MutantStack &m)
{
    if (this == &m)
        return (*this);
    std::stack<T>::operator=(m);
    return (*this);
};

template <typename T>
MutantStack::MutantStack(const MutantStack& m) : std::stack<T>(m){};

iterator begin() { return (std::stack<T>::c.begin()); }

        /**
         * @brief Get a const iterator on the ground of the
         * "std::stack".
         * 
         * @return the iterator.
         */
        const_iterator begin() const { return (std::stack<T>::c.begin()); }
        
        /**
         * @brief Get an iterator on the top of the "std::stack".
         * 
         * @return the iterator.
         */
        iterator end() { return (std::stack<T>::c.end()); }

        /**
         * @brief Get a cnst iterator on the top of the "std::stack".
         * 
         * @return the iterator.
         */
        const_iterator end() const { return (std::stack<T>::c.end()); }

                /**
         * @brief Get an iterator on the ground of the
         * "std::stack".
         * 
         * @return the iterator.
         */
        reverse_iterator rbegin() { return (std::stack<T>::c.rbegin()); }

        /**
         * @brief Get a const reverse_iterator on the ground of the
         * "std::stack".
         * 
         * @return the reverse_iterator.
         */
        const_reverse_iterator rbegin() const { return (std::stack<T>::c.rbegin()); }
        
        /**
         * @brief Get an reverse_iterator on the top of the "std::stack".
         * 
         * @return the reverse_iterator.
         */
        reverse_iterator rend() { return (std::stack<T>::c.rend()); }

        /**
         * @brief Get a cnst reverse_iterator on the top of the "std::stack".
         * 
         * @return the reverse_iterator.
         */
        const_reverse_iterator rend() const { return (std::stack<T>::c.rend()); } 