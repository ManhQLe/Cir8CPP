#pragma once
#include <map>
#include "CComp.h"

namespace Cir8 {
	class CPort :public CComp {	
	public:
		map<string, IComp*> Contacts;
		map<string, void *> Values;
		CPort() {
		}

		void* Get(const string Contact) {
			return Values[Contact];
		}

		void Set(const string Contact, void *Val) {
			auto C = Contacts[Contact];
			if (C) C->OnVibrate(this, Contact, Val);
		}

		void Connect(IComp *Comp, string Contact) {
		}

		void DisconnectWith(IComp *Comp, string Contact) {
		}

		void OnVibrate(IComp *Comp, string Contact, void *Val) {
			if (Contacts[Contact] == Comp) {
				Values[Contact] = Val;
			}
		}

		~CPort() {
		}
	};
}