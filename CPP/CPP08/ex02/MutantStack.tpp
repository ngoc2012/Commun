#include "MutantStack.hpp"

template <typename T>
MutantStack& MutantStack::operator=(const MutantStack &m):std::stack<T>::operator=(m) {}

template <typename T>
MutantStack::MutantStack(const MutantStack& m) : std::stack<T>(m){}

iterator begin() { return (std::stack<T>::c.begin()); }
const_iterator begin() const { return (std::stack<T>::c.begin()); }
iterator end() { return (std::stack<T>::c.end()); }
const_iterator end() const { return (std::stack<T>::c.end()); }
reverse_iterator rbegin() { return (std::stack<T>::c.rbegin()); }
const_reverse_iterator rbegin() const { return (std::stack<T>::c.rbegin()); }
reverse_iterator rend() { return (std::stack<T>::c.rend()); }
const_reverse_iterator rend() const { return (std::stack<T>::c.rend()); } 

template <typename T>
std::ostream& operator<<( std::ostream& out, const MutantStack<T>& a )
{
	if (!a.size())
	{
		out << "[]";
		return (out);
	}
	out << "[";
	for (size_t i = 0;i < a.size() - 1;i++)
		out << a[i] << ", ";
	out << a[a.size() - 1] << "]";
	return (out);
}