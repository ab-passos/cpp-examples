#include <iostream>
#include <memory>
#include "Typelist.hpp"

class EmptyType
{};

#define TYPELIST_1(T1) TypeList<T1, NullType>
#define TYPELIST_2(T1, T2) TypeList<T1,TypeList<T2, NullType> >
#define TYPELIST_3(T1, T2, T3) TypeList<T1,TypeList<T2, TypeList<T3, NullType> > >

namespace functor
{
template<typename R>
struct FunctorBase
{
	typedef R ResultType;
	typedef EmptyType Param1;
private:
};
}

template <typename R, class TList>
class FunctorImpl;

template <typename R>
class FunctorImpl<R, NullType > : public functor::FunctorBase<R>
{
public:
	typedef R ResultType;

	virtual ~FunctorImpl(){}
	virtual R operator()() = 0;
};

template <typename R, typename P1>
class FunctorImpl<R, TYPELIST_1(P1) > : public functor::FunctorBase<R>
{
public:
	typedef R ResultType;
	typedef P1 Param1;

	virtual ~FunctorImpl(){}
	virtual R operator()(P1) = 0;

};

template < class ParentFunctor, typename Fun>
class FunctionHandler : public ParentFunctor::Impl
{
private:
	typedef typename ParentFunctor::Impl Base;
	Fun fun;
public:
	typedef typename Base::ResultType ResultType;
	typedef typename Base::Param1 Param1;

	FunctionHandler(const Fun& fun) :
		fun(fun)
	{}

	virtual ~FunctionHandler()
	{}

	ResultType operator()()
	{
		return fun();
	}

	ResultType operator()(Param1 p1)
	{
		return fun(p1);
	}

};

template <typename R, class TList = NullType>
class Functor
{
public:
	typedef TList ParamList;
	typedef R ResultType;
	typedef FunctorImpl<R, TList> Impl;
	typedef typename Impl::Param1 Param1;

	Functor() :
		impl(0)
	{}

	//Function / Handling functor type templated constructor
	template<class Fun>
	Functor(const Fun& fun) :
	impl(new FunctionHandler<Functor, Fun>(fun))
	{}

	//apply functions
	R operator()()
	{
		return (*impl)();
	}

	R operator()(Param1 p1)
	{
		return (*impl)(p1);
	}
private:
	std::auto_ptr<Impl> impl;

};

class TestFunctor
{
public:
	int operator()()
	{
		std::cout << "zero param functor" << std::endl;
		return 1;
	}
};

int main()
{
	TestFunctor f;
	Functor<int, NullType> command(f);
	int res = command();
}
