#pragma once
#include <map>
#include "CComp.h"

namespace Cir8 {
	class CPort :public CComp {	
		friend class CPack;
	private:
		map<string, IComp*> Contacts;

		map<string, void *> Values;
	public:
		
		CPort();
		template <typename T>
		T Get(const string Contact);

		void Set(const string Contact, void *Val);

		void Connect(IComp *Comp, string Contact);
		void DisconnectWith(IComp *Comp, string Contact);

		void OnVibrate(IComp *Comp, string Contact, void *Val);

	};
}