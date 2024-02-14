template <typename T>
easyfind<T>::easyfind()
{
	_a = new T();
	_size = 0;
}

template <typename T>
easyfind<T>::easyfind(size_t n)
{
	_a = new T[n];
	_size = n;
	for (size_t i = 0; i < n; i++ )
		_a[i] = 0;
}

template <typename T>
easyfind<T>::easyfind(const easyfind& src)
{
	*this = src;
}

template <typename T>
easyfind<T>&	easyfind<T>::operator=( easyfind const & src )
{
	for (size_t i = 0; i < src.size(); i++ )
		_a[i] = src[i];
	return (*this);
}

template <typename T>
easyfind<T>::~easyfind() { delete [] _a; }

template <typename T>
T& easyfind<T>::operator[](size_t i) const
{
	if (i >= _size)
		throw IndexError();
	return _a[i];
}

template <typename T>
size_t	easyfind<T>::size() const { return (_size);}

template <typename T>
std::ostream& operator<<( std::ostream& out, const easyfind<T>& a )
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
