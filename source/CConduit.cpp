#include "CConduit.h"

Cir8::CConduit::CConduit(string name) :CComp(name) {}

Cir8::CConduit::CConduit() : CComp() {}

void Cir8::CConduit::Connect(IComp * Comp, string Contact) {
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

void Cir8::CConduit::DisconnectWith(IComp * Comp, string Contact) {
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

void Cir8::CConduit::OnVibrate(IComp * Comp, string Contact, void* Val) {
	auto S = Contacts.begin();
	auto E = Contacts.end();
	for (; S != E; S++) {
		if (S->first != Contact && S->second != Comp) {
			if (ParallelTrx) {
				thread t(Vibrate, this, S->first, S->second, Val);
				t.detach();
			}
			else
				Vibrate(this, S->first, S->second, Val);
		}
	}
}

void Cir8::CConduit::Signal(void* Val) {
	this->OnVibrate(NULL, "", Val);
}

void Cir8::CConduit::Vibrate(IComp * From, string Contact, IComp * Comp, void* Val) {
	cout <<hex << "Conduit vibrate to comp: [" << Comp
		<< "] at port: [" << Contact << "] - Val Address: [" << Val << "]" << endl;

	Comp->OnVibrate(From, Contact, Val);
}