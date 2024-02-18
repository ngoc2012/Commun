#include <cstring> // memset

template <typename T>
Array<T>::Array()
{
	_a = 0;
	_size = 0;
}

template <typename T>
Array<T>::Array(int n)
{
	if (n <= 0)
	{
		_a = 0;
		_size = 0;
		throw std::invalid_argument("Invalid array size");
	}
	_a = new T[n];
	if (!_a)
	{
		_size = 0;
		throw std::bad_alloc();
	}
	for (int i = 0; i < n; ++i)
	{
		_a[i] = T();
	}
	_size = n;
}

template <typename T>
Array<T>::Array(const Array& src)
{
	_a = new T[src._size];
	if (!_a)
	{
		_size = 0;
		throw std::bad_alloc();
	}
	_size = src._size;
	*this = src;
}

template <typename T>
Array<T>&	Array<T>::operator=( Array const & src )
{
	if (_size != src._size)
		throw std::invalid_argument("Array not equals");
	for (size_t i = 0; i < src.size(); i++ )
		_a[i] = src[i];
	return (*this);
}

template <typename T>
Array<T>::~Array() { delete [] _a; }

template <typename T>
T& Array<T>::operator[](size_t i) const
{
	if (i >= _size)
		throw IndexError();
	return _a[i];
}

template <typename T>
size_t	Array<T>::size() const { return (_size);}

template <typename T>
std::ostream& operator<<( std::ostream& out, const Array<T>& a )
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
