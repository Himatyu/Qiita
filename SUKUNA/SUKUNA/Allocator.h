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
#include<memory>
#include<assert.h>
#include<utility>
#include<array>
#pragma endregion

#pragma region define
//-----------------------------------------------------------
// define
//-----------------------------------------------------------

#pragma endregion

namespace SUKUNA
{
	///実メモリポインタを持つ
	struct Mediator
	{
		Mediator* next = nullptr;
		Mediator* prev = nullptr;
		void*	pMem = nullptr;
		size_t size = 0;
		bool isFront = true;
	};

	///公開用のポインタ
	template<class T>
	class MemoryPointer
	{
		friend class Front;
		friend class Back;
	public:
		MemoryPointer(Mediator* _pMediator)
			: pMediator(_pMediator)
		{

		}
		~MemoryPointer() {}



		Mediator* pMediator;
	};

	///Mediator用のアロケータ
	template<class T>
	class FixedAllocator
	{
	public:
		class MemoryBlock
		{
		public:
			MemoryBlock* pNext = nullptr;
			T			Entity;

			void DisConnect()
			{
				pNext = nullptr;
			}
			void Connect(MemoryBlock* _listHead)
			{
				pNext = _listHead;
			}
		};


		FixedAllocator(size_t _blockCount)
		{
			pMemory = new MemoryBlock[_blockCount];
			pFreeHead = pMemory;

			for (int i = 0; i < _blockCount - 1; i++)
			{
				auto& block = pFreeHead[i];
				auto pNextBlock = pFreeHead + (i + 1);

				block.pNext = pNextBlock;
			}
		}

		~FixedAllocator()
		{
			delete pMemory;
		}

		MemoryBlock* Allocate()
		{
			assert(pFreeHead != nullptr);
			auto pUseBlock = pFreeHead;
			pFreeHead = pFreeHead->pNext;

			pUseBlock->DisConnect();
			return pUseBlock;
		}

		void Deallocate(MemoryBlock* _pBlock)
		{
			_pBlock->Entity.~T();
			_pBlock->Connect(pFreeHead);
		}

	private:
		MemoryBlock* pFreeHead;
		MemoryBlock* pMemory;
	};

	/// 仮領域を割り当てるだけのアロケータ
	/// 開放することない
	class TemporaryAlloctor
	{
	public:
		TemporaryAlloctor(size_t _size)
		{
			pMemoryHead = malloc(_size);
		}
		~TemporaryAlloctor()
		{
			free(pMemoryHead);
		}

		template<class T>
		T* Allocate()
		{
			auto size = sizeof(T);
			if (maxSize < offsetFromHead + size)
			{
				throw new std::bad_alloc;
			}

			auto pHead = (char*)pMemoryHead + offsetFromHead;
			auto result = new (pHead) T;
			offsetFromHead += size;
			return result;
		}

		//デストラクタを呼ばない
		void AllDeallocate()
		{
			offsetFromHead = 0;
		}

	private:

		void* pMemoryHead;
		size_t offsetFromHead = 0;
		size_t maxSize;
	};

	///一時的なメモリ確保を行う
	class Front
	{
		struct DataSet
		{
			Mediator* pMediatorHead;
			TemporaryAlloctor* pAlloctor;
		};

	public:
		Front(size_t _temporaryBufferSize) :
			data(
		{
		DataSet{nullptr,new TemporaryAlloctor(_temporaryBufferSize)},
		DataSet{ nullptr,new TemporaryAlloctor(_temporaryBufferSize) }
		})
		{
			pBuffer = &data[0].pMediatorHead;
		}
		~Front() {}

		template<class T>
		MemoryPointer<T> Allocate(Mediator* _pMediator)
		{
			auto& dataSet = GetDataInSide();
			auto pData = dataSet.pAlloctor->Allocate<T>();

			_pMediator->pMem = pData;
			_pMediator->isFront = true;
			_pMediator->size = sizeof(T);

			if (dataSet.pMediatorHead != nullptr)
			{
				_pMediator->next = dataSet.pMediatorHead;
				dataSet.pMediatorHead->prev = _pMediator;
			}
			dataSet.pMediatorHead = _pMediator;

			return MemoryPointer<T>({ _pMediator });
		}

		template<class T>
		void Deallocate(MemoryPointer<T>& _pointer)
		{
			auto pNext = _pointer.pMediator->next;
			auto pPrev = _pointer.pMediator->prev;

			if (pNext)
			{
				pNext->prev = pPrev;
			}

			if (pPrev)
			{
				pPrev->next = pNext;
			}

			auto pMem = static_cast<T*>(_pointer.pMediator->pMem);
			pMem->~T();
		}

		Mediator* GetMediators()
		{
			return *pBuffer;
		}

		void FlipBuffer()
		{
			auto useIndex = (*pBuffer == data[0].pMediatorHead) ? 1 : 0;
			pBuffer = &data[useIndex].pMediatorHead;

			auto resetIndex = static_cast<int>(~static_cast<bool>(useIndex));
			data[useIndex].pMediatorHead = nullptr;
		}

		bool IsFront()
		{
			return *pBuffer == data[0].pMediatorHead;
		}

		DataSet& GetDataInSide()
		{
			return data[IsFront() ? 0 : 1];
		}

	private:
		Mediator** pBuffer;

		std::array<DataSet, 2> data;
		bool isFront;
	};

	///時間のかかるメモリ確保を行い、メディエータのポインタを差し替える
	class Back
	{
	public:
		void ReAllocate(Mediator* _pMediator)
		{
			auto newMemory = malloc(_pMediator->size);//test
			std::memmove(newMemory, _pMediator->pMem, _pMediator->size);
			_pMediator->pMem = newMemory;
		}

		template<class T>
		void Deallocate(MemoryPointer<T>& _pointer)
		{
			auto pCasted = static_cast<T*>(_pointer.pMediator->pMem);
			pCasted->~T();

			std::free(pCasted);
		}
	};

	template<class Front, class Back>
	class Alloctor
	{
	public:
#pragma region  defaults
		//-----------------------------------------------------------
		// defaults
		//-----------------------------------------------------------
		Alloctor(size_t _mediatorCount, size_t _temporarySize) :
			mediatorAllocator(_mediatorCount),
			frontAllocator(_temporarySize)
		{

		}
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
		MemoryPointer<T> Allocate()
		{
			auto pMediator = mediatorAllocator.Allocate();
			return frontAllocator.Allocate<T>(&pMediator->Entity);
		}

		template<class T>
		void Deallocate(MemoryPointer<T> _pointer)
		{
			auto isFront = _pointer.pMediator->isFront;

			if (isFront)
			{
				frontAllocator.Deallocate(_pointer);
				return;
			}
			backAllocator.Deallocate(_pointer);
		}

		void SendToBack()
		{
			auto pMediatorsOnSide = frontAllocator.GetMediators();
			auto pIt = pMediatorsOnSide;

			while (pIt != nullptr)
			{
				backAllocator.ReAllocate(pIt);
				pIt = pIt->next;
			}

			frontAllocator.FlipBuffer();
		}

#pragma endregion

	private:
#pragma region value
		//-----------------------------------------------------------
		// val
		//-----------------------------------------------------------
		FixedAllocator<Mediator> mediatorAllocator;
		Front		frontAllocator;
		Back		backAllocator;
#pragma endregion
	};
}

//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------