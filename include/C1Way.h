#pragma once
#include "CComp.h"
namespace Cir8 {
	class C1Way : public CComp {
	private:
		map<string, IComp*> Contacts;
	public:
		C1Way(string name);
		C1Way();
		void Connect(IComp * Comp, string Contact);		
		void DisconnectWith(IComp * Comp, string Contact);


		void OnVibrate(IComp * Comp, string Contact, void* Val);
	};
}
