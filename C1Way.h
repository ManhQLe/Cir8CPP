#pragma once
#include "CComp.h"
namespace Cir8 {
	class C1Way : public CComp {
	private:
		map<string, IComp*> Contacts;
	public:
		C1Way(string name) :CComp(name) {
		}

		C1Way() :CComp{
		}

		virtual void Connect(IComp * Comp, string Contact) {			
			if (Contact != "IN" && Contact != "OUT") {
				cerr << "CONNECTION ERROR: C1Way, Name:" << this->Name << ") only has 2 contacts: IN and OUT";
			}
			IComp *C = Contacts[Contact];
			if (C) {
				if (C != Comp)
					C->Connect(Comp, Contact);
			}
			else
			{
				Contacts[Contact] = Comp;
			}
		}

		virtual void DisconnectWith(IComp * Comp, string Contact) {
			auto C = Contacts[Contact];
			if (C) {
				Contacts.erase(Contact);
				C->DisconnectWith(Comp, Contact);
			}
		}
		virtual void OnVibrate(IComp * Comp, string Contact, void * Val) {	
			if (Contact == "IN"&& Contacts["IN"] == Comp) {
				auto C = Contacts["OUT"];
				if (C)
					C->OnVibrate(this, "OUT", Val);
			}
		}
	};
}
