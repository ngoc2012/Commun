template <typename T>
MutantStack<T>::MutantStack()
{
	_a = new T();
	_size = 0;
}

template <typename T>
MutantStack<T>::MutantStack(size_t n)
{
	_a = new T[n];
	_size = n;
	for (size_t i = 0; i < n; i++ )
		_a[i] = 0;
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack& src)
{
	*this = src;
}

template <typename T>
MutantStack<T>&	MutantStack<T>::operator=( MutantStack const & src )
{
	for (size_t i = 0; i < src.size(); i++ )
		_a[i] = src[i];
	return (*this);
}

template <typename T>
MutantStack<T>::~MutantStack() { delete [] _a; }

template <typename T>
T& MutantStack<T>::operator[](size_t i) const
{
	if (i >= _size)
		throw IndexError();
	return _a[i];
}

template <typename T>
size_t	MutantStack<T>::size() const { return (_size);}

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
