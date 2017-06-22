#pragma once
#include "IComp.h"
namespace Cir8 {
	class CComp :public IComp {
	private:
		static int Count;
	public:
		CComp() :CComp("Name" + (++Count)) {
		}
		CComp(string name) {
			Name = name;
		}
	};

	int CComp::Count = -1;
}