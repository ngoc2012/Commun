#include "MutantStack.hpp"

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack &m)
{
    if (this != &m) {
        std::stack<T>::operator=(m);
    }
    return (*this);
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack& m) : std::stack<T>(m){}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() { return (this->begin()); }

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const { return (this->begin()); }

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() { return (this->end()); }

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const { return (this->end()); }

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin() { return (this->rbegin()); }

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rbegin() const { return (this->rbegin()); }

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend() { return (this->rend()); }

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rend() const { return (this->rend()); } 

template <typename T>
void MutantStack<T>::push(const T &value) {
    this->c.push_back(value);
}

template <typename T>
T& MutantStack<T>::top() {
    return this->top();
}

template <typename T>
const T& MutantStack<T>::top() const {
    return this->top();
}

template <typename T>
void MutantStack<T>::pop() {
    this->pop();
}

template <typename T>
size_t MutantStack<T>::size() const {
    return this->size();
}

template <typename T>
std::ostream& operator<<( std::ostream& out, const MutantStack<T>& a )
{
	if (!a.size())
	{
		out << "[]";
		return (out);
	}
	out << "[";
	for (typename MutantStack<T>::iterator i = a.begin();i != a.end(); a++)
	{
		if (a + 1 != a.end())
			out << *a << ", ";
		else
			out << a[a.size() - 1] << "]";
	}
		
	
	return (out);
}
