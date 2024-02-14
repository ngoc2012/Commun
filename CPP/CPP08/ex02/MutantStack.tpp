#include "MutantStack.hpp"

MutantStack& MutantStack::operator=(const MutantStack &m)
{
    if (this == &m)
        return (*this);
    std::stack<T>::operator=(m);
    return (*this);
};