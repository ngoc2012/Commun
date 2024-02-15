#include "MutantStack.hpp"

template<typename T, class Container = std::deque<T> > 
MutantStack<T>::MutantStack( const MutantStack<T>& rhs ) { *this = rhs; }

template<typename T, class Container = std::deque<T> > 
MutantStack<T>&    MutantStack<T>::operator=( const MutantStack<T>& rhs ) {
    std::stack< T, Container >::operator=( rhs );
    return *this;
}

template<typename T, class Container = std::deque<T> > 
typename MutantStack<T>::iterator    MutantStack<T>::begin() { return this->c.begin(); }

template<typename T, class Container = std::deque<T> > 
typename MutantStack<T>::iterator    MutantStack<T>::end() { return this->c.end(); }
