#include "MutantStack.hpp"

template <typename T>
MutantStack& MutantStack::operator=(const MutantStack &m):std::stack<T>::operator=(m) {}

template <typename T>
MutantStack::MutantStack(const MutantStack& m) : std::stack<T>(m){}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() { return (std::stack<T>::c.begin()); }

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const { return (std::stack<T>::c.begin()); }

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() { return (std::stack<T>::c.end()); }

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const { return (std::stack<T>::c.end()); }

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rbegin() { return (std::stack<T>::c.rbegin()); }

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rbegin() const { return (std::stack<T>::c.rbegin()); }

template <typename T>
typename MutantStack<T>::reverse_iterator MutantStack<T>::rend() { return (std::stack<T>::c.rend()); }

template <typename T>
typename MutantStack<T>::const_reverse_iterator MutantStack<T>::rend() const { return (std::stack<T>::c.rend()); } 

template <typename T>
std::ostream& operator<<( std::ostream& out, const MutantStack<T>& a )
{
	if (!a.size())
	{
		out << "[]";
		return (out);
	}
	out << "[";
	for (MutantStack<T>::iterator i = a.begin();i != a.end(); a++)
	{
		if (a + 1 != a.end())
			out << *a << ", ";
		else
			out << a[a.size() - 1] << "]";
	}
		
	
	return (out);
}
