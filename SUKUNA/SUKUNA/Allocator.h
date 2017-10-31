/**
* @file		Alloctor.h
* @brief
* @author
* @date
*/
#pragma once

#pragma region include
//-----------------------------------------------------------
// include
//-----------------------------------------------------------

#pragma endregion

#pragma region define
//-----------------------------------------------------------
// define
//-----------------------------------------------------------

#pragma endregion

namespace SUKUNA
{
	///���������|�C���^������
	struct Mediator
	{
		Mediator* next;
		void*	pMem;
	};

	///�ꎞ�I�ȃ������m�ۂ��s��
	class Front
	{
	public:
		Front()
		{
			pBuffer = &pFront;
		}
		~Front() {}

		template<class T>
		MemoryPointer<T> Allocate()
		{
			return MemoryPointer<T>();
		}

		template<class T>
		void Deallocate(MemoryPointer<T> _pointer)
		{

		}

		Mediator* GetMediators()
		{
			return *pBuffer;
		}
		void FlipBuffer()
		{
			pBuffer = (*pBuffer == pFront) ? &pBack : &pFront;
		}

	private:
		Mediator** pBuffer;
		Mediator* pFront;
		Mediator* pBack;

	};

	///���Ԃ̂����郁�����m�ۂ��s���A���f�B�G�[�^�̃|�C���^�������ւ���
	class IBack
	{
	public:
		IBack() {}
		~IBack() {}

		void ReAllocate(Mediator*) {}

		template<class T>
		void Deallocate(MemoryPointer<T>) {}
	private:

	};

	///���J�p�̃|�C���^
	template<class T>
	class MemoryPointer
	{
		friend class
	public:
		MemoryPointer() {}
		~MemoryPointer() {}

	private:

	};


	class Alloctor
	{
	public:
#pragma region  defaults
		//-----------------------------------------------------------
		// defaults
		//-----------------------------------------------------------
		Alloctor() = default;
		~Alloctor() = default;

		Alloctor(const Alloctor&) = default;
		Alloctor(Alloctor&&) = default;

		Alloctor& operator=(const Alloctor&) = default;
		Alloctor& operator=(Alloctor&&) = default;
#pragma endregion

#pragma region function
		//-----------------------------------------------------------
		// function
		//-----------------------------------------------------------

		template<class T>
		MemoryPointer<T> Allocate() {}

		template<class T>
		void Deallocate(MemoryPointer<T>) {}

		void PreparationForSend() {}

		void SendToBack() {}

		void AsyncPreparationForSend() {}

		void AsyncSendToBack() {}


#pragma endregion

#pragma region property
		//-----------------------------------------------------------
		// property
		//-----------------------------------------------------------

#pragma endregion

#pragma region value
	//-----------------------------------------------------------
	// val
	//-----------------------------------------------------------

#pragma endregion
	};
}

//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------