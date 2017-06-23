#include "CComp.h"
int Cir8::CComp::Count = -1;

Cir8::CComp::CComp():CComp("Name" + std::to_string(++CComp::Count)) {
}

Cir8::CComp::CComp(string name)
{
	Name = name;
}