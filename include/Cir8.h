#pragma once
#include "CBundle.h"
#include <cstdarg>
#define CGET_PORT_VAL(CPack_ptr,Name,Type) *(Type *)CPack_ptr->Ports.Get(Name)
#define CSEND_TO_PORT(CPack_ptr,Name,Type,Val) CPack_ptr->Ports.Set(Name,Val)
namespace Cir8 {

	CConduit* Link(IComp* A, string ContactA, string ContactB, IComp* B);

	CConduit* MultiLink(int Count, ...);

	CConduit* MultiLink(void *A);

	CConduit* Wire(string N);

}