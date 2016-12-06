/**
* @file		Constant.h
* @brief	定数を定義する
* @author	S.OIKAWA
* @date		2016.11.28
*/
#pragma once

#pragma region include
//-----------------------------------------------------------
// include
//-----------------------------------------------------------
#include<Windows.h>
#include<tchar.h>
#include<stdlib.h>
#pragma endregion

#pragma region define
//-----------------------------------------------------------
// define
//-----------------------------------------------------------

#pragma endregion
class Constant final
{
public:
#pragma region value
	//-----------------------------------------------------------
	// val
	//-----------------------------------------------------------

			/// <summary>
			/// クラス・プロセス名
			/// </summary>
	static const TCHAR ClassName[];

	/// <summary>
	/// プロシージャプロパティ
	/// </summary>
	static const TCHAR ClientProc[];

#pragma endregion
};

//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------