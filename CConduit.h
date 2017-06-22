#pragma once
#include "CComp.h"
namespace Cir8 {	
	class CConduit :CComp {
	private:		
		map<string, IComp*> Contacts;
	public:
		CConduit(string name) :CComp(name) {}

		CConduit():CComp() {
		}
		
		bool ParallelTrx = true;
		virtual void Connect(IComp * Comp, string Contact) {			
			auto S = Contacts.begin();
			auto E = Contacts.end();
			bool NotFound = true;
			for (; S != E; S++) {
				if (S->first == Contact && S->second == Comp) {
					NotFound = false;
					break;
				}
			}
			if (NotFound)
				Contacts[Contact] = Comp;			

		}
		virtual void DisconnectWith(IComp * Comp, string Contact) {
			auto S = Contacts.begin();
			auto E = Contacts.end();
			bool Found = false;
			for (; S != E; S++) {
				if (S->first == Contact && S->second == Comp) {
					Found = true;
					break;
				}
			}
			if (Found)
				Contacts.erase(Contact);
		}

		virtual void OnVibrate(IComp * Comp, string Contact, void * Val) {
			auto S = Contacts.begin();
			auto E = Contacts.end();			
			for (; S != E; S++) {
				if (S->first != Contact && S->second != Comp) {				
					if (ParallelTrx) {
						thread t(Vibrate, this, Contact, Comp, Val);
						t.detach();
					}
					else
						Vibrate(this, S->first, S->second, Val);
				}
			}			
		}

		void Signal(void *Val) {
			this->OnVibrate(NULL, "", Val);
		}

		static void Vibrate(IComp *From, string Contact, IComp* Comp, void *Val) {
			Comp->OnVibrate(From, Contact, Val);
		}
		
	};
}