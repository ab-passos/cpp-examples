#ifndef TYLELIST_HPP
#define TYLELIST_HPP

class NullType {};

template <class T, class U>
struct TypeList
{
	typedef T Head;
	typedef U Tail;
};

//Calculates length of a TypeList
template <class TList> struct Length;

template <>
struct Length<NullType>
{
	enum {value = 0};
};

template <class T, class U>
struct Length< TypeList<T, U> >
{
    enum {value = 1 + Length<U>::value};
};


// Type at a certain position
template <class TList, unsigned int index> struct TypeAt;

template <class Head, class Tail>
struct TypeAt<TypeList<Head, Tail>, 0>
{
	typedef Head Result;
};

template <class Head, class Tail, unsigned int i>
struct TypeAt<TypeList<Head, Tail>, i>
{
	typedef typename TypeAt<Tail, i-1>::Result Result;
};

//Index of a certain element in the list
template <class TList, class Elem> struct IndexOf;

template <class T>
struct IndexOf<NullType, T>
{
	enum {value = -1};
};

template <class Head, class Tail>
struct IndexOf<TypeList<Head, Tail>, Head>
{
	enum {value = 0};
};

template <class Head, class Tail, class T>
struct IndexOf<TypeList<Head, Tail>, T>
{
public:
enum { value = IndexOf<Tail, T>::value == -1 ? -1 : 1 + IndexOf<Tail, T>::value };
};

//Append
template <class TList, class T> struct Append;
template <>
struct Append<NullType, NullType>
{
	typedef NullType Result;
};

template <class T>
struct Append<NullType, T>
{
	typedef TypeList<T, NullType> Result;
};

template <class Head, class Tail>
struct Append<NullType, TypeList<Head, Tail> >
{
	typedef TypeList<Head, Tail> Result;
};

template <class Head, class Tail, class T>
struct Append<TypeList<Head, Tail>, T >
{
	typedef TypeList<Head,
			typename Append<Tail, T>::Result>
				Result;
};

//Erase
template <class TList, class T> struct Erase;
template <class T>
struct Erase<NullType, T>
{
	typedef NullType Result;
};


template <class T, class Tail>
struct Erase<TypeList<T, Tail>, T>
{
	typedef Tail Result;
};

template <class Head, class Tail, class T>
struct Erase<TypeList<Head, Tail>, T>
{
	typedef TypeList<Head,
			typename Erase<Tail, T>::Result > Result;
};

//Replace
template <class TList, class E, class U> struct Replace;

template <class E, class U>
struct Replace<NullType, E, U>
{
	typedef NullType Result;
};

template <class H, class Tail, class U>
struct Replace<TypeList<H, Tail>, H, U>
{
	typedef TypeList<U, Tail> Result;
};

template <class Head, class Tail, class E, class U>
struct Replace<TypeList<Head, Tail>, E, U>
{
	typedef TypeList<Head,
			typename Replace<Tail, E, U>::Result> Result;
};

#endif
