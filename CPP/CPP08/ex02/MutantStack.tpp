#include "MutantStack.hpp"

template<typename T, class Container> 
MutantStack<T, Container>::MutantStack( const MutantStack<T, Container>& rhs ) { *this = rhs; }

template<typename T, class Container> 
MutantStack<T, Container>&    MutantStack<T, Container>::operator=( const MutantStack<T, Container>& rhs ) {
    std::stack< T, Container >::operator=( rhs );
    return *this;
}

template<typename T, class Container> 
typename MutantStack<T, Container>::iterator    MutantStack<T, Container>::begin() { return this->c.begin(); }

template<typename T, class Container> 
typename MutantStack<T, Container>::iterator    MutantStack<T, Container>::end() { return this->c.end(); }
