#pragma once
#include "stdafx.h"
using namespace std;
namespace Cir8 {
	class IComp {
	public:
		string Name;
		virtual void Connect(IComp *Comp, string Contact) = 0;
		virtual void DisconnectWith(IComp *Comp, string Contact) = 0;
		virtual void OnVibrate(IComp *Comp, string Contact, void* Val) = 0;
	};
}