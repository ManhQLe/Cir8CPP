#pragma once
#include "CComp.h"
#include "CPort.h"
#include <algorithm>
#include <mutex>
namespace Cir8 {
	typedef void CPackFx(CPack *);
	class CPack :CComp {	
	private:
		mutex locker;
	public:
		int ICount = 0;
		bool Stage = false;
		list<string> Ins;
		void *Props;
		CPort Ports;
		CPackFx FX;

		CPack(string name) :CComp(name) {}
		CPack() :CComp() {}

		void SetStage(bool s) {
			Stage = s;
			Ports.Values.clear();
			ICount = 0;
		}

		virtual void Connect(IComp * Comp, string Contact) {
			auto Contacts = Ports.Contacts;
			if (Contacts.find(Contact) != Contacts.end()) { //Found
				auto A = Contacts[Contact];
				if (A != Comp) {
					A->Connect(Comp, Contact);
				}
			}
			else //Not found
			{
				Contacts[Contact] = Comp;
				Comp->Connect(this, Contact);
			}
		}

		virtual void DisconnectWith(IComp * Comp, string Contact) {
			auto Contacts = Ports.Contacts;
			if (Contacts.find(Contact) != Contacts.end()) { //Found
				auto A = Contacts[Contact];
				Contacts.erase(Contact);
				A->DisconnectWith(Comp, Contact);				
			}
		}
		virtual void OnVibrate(IComp * Comp, string Contact, void * Val) {
			auto Contacts = Ports.Contacts;			
			auto End = Contacts.end();		
			auto c = find(Ins.begin(), Ins.end(), Contact);
			if (Ins.size() == 0) {
				FX(this);
				return;
			}
			if (c != Ins.end()) {//Found
				if (Stage) {
					locker.lock();
					auto Data = Ports.Values[Contact];
					Ports.Values[Contact] = Val;
					if (!Data &&ICount++ == Ins.size()) {
						if (FX)FX(this);
						Ports.Values.clear();
						ICount = 0;
					}
					locker.unlock();
				}
				else
				{
					auto Data = Ports.Values[Contact];
					if (!Data && ICount++ >= Ins.size() || ICount >= Ins.size()) {
						if (FX)FX(this);
					}
				}
			}
			
		}

		~CPack() {
		}
	};
}