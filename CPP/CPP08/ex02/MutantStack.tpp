#include "MutantStack.hpp"

template<typename T, class Container = std::deque<T> > 
MutantStack( const MutantStack& rhs ) { *this = rhs; }

    MutantStack&    operator=( const MutantStack& rhs ) {
        std::stack< T, Container >::operator=( rhs );
        return *this;
    }

    typedef typename Container::iterator    iterator;

    iterator    begin() { return this->c.begin(); }
    iterator    end() { return this->c.end(); }
};
