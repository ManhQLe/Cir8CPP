#include "Cir8.h"
namespace Cir8 {
	static CConduit* Link(IComp* A, string ContactA, string ContactB, IComp* B) {
		auto Con = new CConduit();
		Con->Connect(A, ContactA);
		Con->Connect(B, ContactB);
		return Con;
	}

	static CConduit* MultiLink(int Count, ...) {
		va_list args;
		va_start(args, Count);
		CConduit *Con = new CConduit();
		for (auto i = 0; i < Count; i += 2) {
			Con->Connect(va_arg(args, IComp*), va_arg(args, string));
		}
		return Con;
	}

	static CConduit* MultiLink(void *A) {
		unsigned int *X = (unsigned int *)A;
		CConduit *Con = new CConduit();
		do
		{
			Con->Connect((IComp *)X, *(string *)X);
			X += 2;
		} while (true);

	}

	static CConduit* Wire(string N) {
		return new CConduit(N);
	}

}