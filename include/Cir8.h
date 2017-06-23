#pragma once
#include "CBundle.h"
#include <cstdarg>
#define PORTVAL(CPack_ptr,Name,Type) *(Type *)CPack_ptr->Ports.Get(Name)
namespace Cir8 {
	
	static CConduit* Link(IComp* A, string ContactA, string ContactB, IComp* B);

	static CConduit* MultiLink(int Count, ...);

	static CConduit* MultiLink(void *A);

	static CConduit* Wire(string N);

}