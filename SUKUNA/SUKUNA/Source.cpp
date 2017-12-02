

#include"Allocator.h"
using namespace SUKUNA;

int main()
{
	Alloctor<Front, Back> alloctor(100, 500);
	auto pint = alloctor.Allocate<int>();

	auto ppp = pint.pMediator;
	*((int*)ppp->pMem) = 100;

	alloctor.SendToBack();
	auto ppp2 = pint.pMediator;

	auto sss = *((int*)ppp->pMem);

	alloctor.Deallocate(pint);

}