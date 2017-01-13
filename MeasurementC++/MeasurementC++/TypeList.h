/**
* @file		TypeList.h
* @brief	タイプリストを提供
* @author	S.OIKAWA
* @date		2016.09.07
*/
#pragma once

//-----------------------------------------------------------
// include
//-----------------------------------------------------------
#include"NullType.h"

//-----------------------------------------------------------
// define
//-----------------------------------------------------------
namespace Utility
{
	//-----------------------------------------------------------
	// TypeList
	//-----------------------------------------------------------
	template <typename T, typename U>
	struct TypeList
	{
		using Head = T;
		using Tail = U;
	};

	template<
		typename T1>
		using TypeList1 =
		Utility::TypeList<
		T1,	Utility::NullType>;

	template<
		typename T1,
		typename T2>
		using TypeList2 =
		Utility::TypeList<T1, TypeList1<T2>>;

	template<
		typename T1,
		typename T2,
		typename T3>
		using TypeList3 =
		Utility::TypeList<T1, TypeList2<T2,T3>>;

	template<
		typename T1,
		typename T2,
		typename T3,
		typename T4>
		using TypeList4 =
		Utility::TypeList<T1, TypeList3<T2,T3,T4>>;

	template<
		typename T1,
		typename T2,
		typename T3,
		typename T4,
		typename T5>
		using TypeList5 =
		Utility::TypeList<T1, TypeList4<T2,T3,T4,T5>>;

	template<
		typename T1,
		typename T2,
		typename T3,
		typename T4,
		typename T5,
		typename T6>
		using TypeList6 =
		Utility::TypeList<T1, TypeList5<T2, T3, T4, T5,T6>>;

	template<
		typename T1,
		typename T2,
		typename T3,
		typename T4,
		typename T5,
		typename T6,
		typename T7>
		using TypeList7 =
		Utility::TypeList<T1, TypeList6<T2, T3, T4, T5, T6,T7>>;

	template<
		typename T1,
		typename T2,
		typename T3,
		typename T4,
		typename T5,
		typename T6,
		typename T7,
		typename T8>
		using TypeList8 =
		Utility::TypeList<T1, TypeList7<T2, T3, T4, T5, T6, T7,T8>>;

	template<
		typename T1,
		typename T2,
		typename T3,
		typename T4,
		typename T5,
		typename T6,
		typename T7,
		typename T8,
		typename T9>
		using TypeList9 =
		Utility::TypeList<T1, TypeList8<T2, T3, T4, T5, T6, T7, T8,T9>>;

	template<
		typename T1,
		typename T2,
		typename T3,
		typename T4,
		typename T5,
		typename T6,
		typename T7,
		typename T8,
		typename T9,
		typename T10>
		using TypeList10 =
		Utility::TypeList<T1, TypeList9<T2, T3, T4, T5, T6, T7, T8, T9, T10>>;

#define ___TYPE_LIST1(t1)\
	Utility::TypeList<t1,Utility::NullType>
#define ___TYPE_LIST2(t1,t2)\
	Utility::TypeList<t1,___TYPE_LIST1(t2)>
#define ___TYPE_LIST3(t1,t2,t3)\
	Utility::TypeList<t1,___TYPE_LIST2(t2,t3)>
#define ___TYPE_LIST4(t1,t2,t3,t4)\
	Utility::TypeList<t1,___TYPE_LIST3(t2,t3,t4)>
#define ___TYPE_LIST5(t1,t2,t3,t4,t5)\
	Utility::TypeList<t1,___TYPE_LIST4(t2,t3,t4,t5)>
#define ___TYPE_LIST6(t1,t2,t3,t4,t5,t6)\
	TypeList<t1,___TYPE_LIST5(t2,t3,t4,t5,t6)>
#define ___TYPE_LIST7(t1,t2,t3,t4,t5,t6,t7)\
	Utility::TypeList<t1,___TYPE_LIST6(t2,t3,t4,t5,t6,t7)>
#define ___TYPE_LIST8(t1,t2,t3,t4,t5,t6,t7,t8)\
	Utility::TypeList<t1,___TYPE_LIST7(t2,t3,t4,t5,t6,t7,t8)>
#define ___TYPE_LIST9(t1,t2,t3,t4,t5,t6,t7,t8,t9)\
	Utility::TypeList<t1,___TYPE_LIST8(t2,t3,t4,t5,t6,t7,t8,t9)>
#define ___TYPE_LIST10(t1,t2,t3,t4,t5,t6,t7,t8,t9,t10)\
	Utility::TypeList<t1,___TYPE_LIST9(t2,t3,t4,t5,t6,t7,t8,t9,t10)>


	//-----------------------------------------------------------
	// Length
	//-----------------------------------------------------------
	template <class TList> struct Length;

	template<>
	struct Length<NullType>
	{
		enum : int { value = 0 };
	};

	template<class T, class U>
	struct Length<TypeList<T, U>>
	{
		enum : int
		{
			value = 1 + Length<U>::value
		};
	};
}
//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------