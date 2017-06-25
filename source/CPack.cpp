#include "CPack.h"

Cir8::CPack::CPack(string name) :CComp(name) {}

Cir8::CPack::CPack() : CComp() {}

void Cir8::CPack::SetStage(bool s) {
	Stage = s;
	Ports.Values.clear();
	ICount = 0;
}

void Cir8::CPack::Connect(IComp * Comp, string Contact) {
	auto &Contacts = Ports.Contacts;
	auto X = Contacts[Contact];
	if (X) { //FoundE		
		if (X != Comp) {
			X->Connect(Comp, Contact);
		}
	}
	else //Not found
	{		
		Contacts[Contact] = Comp;
		Comp->Connect(this, Contact);		
	}
}

void Cir8::CPack::DisconnectWith(IComp * Comp, string Contact) {
	auto &Contacts = Ports.Contacts;
	if (Contacts.find(Contact) != Contacts.end()) { //Found
		auto A = Contacts[Contact];
		Contacts.erase(Contact);
		A->DisconnectWith(Comp, Contact);
	}
}

void Cir8::CPack::OnVibrate(IComp * Comp, string Contact, void*Val) {
	auto &Contacts = Ports.Contacts;
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
			Ports.Values[Contact] = Val;
			if (!Data && ICount++ >= Ins.size() || ICount >= Ins.size()) {
				if (FX)FX(this);
			}
		}
	}
}