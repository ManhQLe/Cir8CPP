#pragma once
#include "IComp.h"
namespace Cir8 {
	class CComp :public IComp {
	private:
		static int Count;
	public:
		CComp();
		CComp(string name);
	};
}