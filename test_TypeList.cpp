#include <gtest/gtest.h>
#include <typeinfo>
#include "Typelist.hpp"

TEST(TypeList, Size_1){

	typedef TypeList<int, NullType> List;
	ASSERT_EQ(Length<List>::value, 1);
}

TEST(TypeList, Size_2){

	typedef TypeList<int, TypeList<int,NullType> > List;
	ASSERT_EQ(Length<List>::value, 2);
}

TEST(TypeList, Size_3){

	typedef TypeList<int,
		TypeList<int,
			TypeList<double, NullType> > > List;
	ASSERT_EQ(Length<List>::value, 3);
}

TEST(TypeList, TypeAt_0){
	typedef TypeList<int, TypeList<double,NullType> > List;

	ASSERT_EQ(typeid(TypeAt<List, 0>::Result), typeid(int));
}

TEST(TypeList, TypeAt_1){
	typedef TypeList<int, TypeList<double,NullType> > List;

	ASSERT_EQ(typeid(TypeAt<List, 1>::Result), typeid(double));
}

TEST(TypeList, IndexOf_int){

	typedef TypeList<int,
			TypeList<double, NullType> > List;

	int val = IndexOf<List, int>::value;
	ASSERT_EQ(val, 0);
}

TEST(TypeList, IndexOf_double){

	typedef TypeList<int,
			TypeList<double, NullType> > List;

	int val = IndexOf<List, double>::value;
	ASSERT_EQ(val, 1);
}

TEST(TypeList, IndexOf_void){

	typedef TypeList<int,
			TypeList<double, NullType> > List;

	int val = IndexOf<List, void>::value;
	ASSERT_EQ(val, -1);
}

TEST(TypeList, NullType)
{
	ASSERT_EQ(typeid(Append<NullType, NullType>::Result), typeid(NullType));
}

TEST(TypeList, Append_NullType)
{
	typedef TypeList<int, NullType> List;

	ASSERT_EQ(typeid(Append<List, NullType>::Result), typeid(List));
}

TEST(TypeList, Append_Double)
{
	typedef TypeList<int, NullType> List;
	typedef TypeList<int, TypeList<double, NullType> > ResultList;

	ASSERT_EQ(typeid(Append<List, double>::Result), typeid(ResultList));
}

TEST(TypeList, Append_Int)
{
	typedef TypeList<int, NullType> List;
	typedef TypeList<int, TypeList<int, NullType> > ResultList;

	ASSERT_EQ(typeid(Append<List, int>::Result), typeid(ResultList));
}

TEST(TypeList, Erase_NullType)
{
	ASSERT_EQ(typeid(Erase<NullType, NullType>::Result), typeid(NullType));
}

TEST(TypeList, Erase_OneElement)
{
	typedef TypeList<int, NullType> List;
	ASSERT_EQ(typeid(Erase<List, int>::Result), typeid(NullType));
}

TEST(TypeList, Erase_OneElementOfListWithTwo)
{
	typedef TypeList<int, TypeList<double, NullType> > List;
	typedef TypeList<int, NullType > ResultList;

	ASSERT_EQ(typeid(Erase<List, double>::Result), typeid(ResultList));
}

TEST(TypeList, Replace_NullType)
{
	ASSERT_EQ(typeid(Replace<NullType, NullType, NullType>::Result), typeid(NullType));
}

TEST(TypeList, Replace_NullType_ForInt_Returns_int)
{
	ASSERT_EQ(typeid(Replace<NullType, NullType, int>::Result), typeid(NullType));
}

TEST(TypeList, Replace_double_for_int)
{
	typedef TypeList<int, TypeList<double, NullType> > List;

	typedef TypeList<int, TypeList<int, NullType> > ResultList;


	ASSERT_EQ(typeid(Replace<List, double, int>::Result), typeid(ResultList));
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
