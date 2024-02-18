#include <cstring> // memset

template <typename T>
Array<T>::Array()
{
	_a = new T();
	_size = 0;
}

template <typename T>
Array<T>::Array(size_t n)
{
	_a = new T[n];
	for (size_t i = 0; i < n; ++i) {
        _a[i] = T();
    }
	_size = n;
}

template <typename T>
Array<T>::Array(const Array& src)
{
	*this = src;
}

template <typename T>
Array<T>&	Array<T>::operator=( Array const & src )
{
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
