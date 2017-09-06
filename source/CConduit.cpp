#include "CConduit.h"

Cir8::CConduit::CConduit(string name) :CComp(name) {}

Cir8::CConduit::CConduit() : CComp() {}

void Cir8::CConduit::Connect(IComp * Comp, string Contact) {
	auto S = Contacts.begin();
	auto E = Contacts.end();
	
	auto X = find_if(S, E, [&](pair<string,IComp*> pair) {
		return pair.first == Contact && pair.second == Comp;
	});
			
	if (X == E) //NOT FOUND
	{		
		Contacts.push_back(make_pair(Contact, Comp));
		if (Comp)Comp->Connect(this, Contact);
	}

}

void Cir8::CConduit::DisconnectWith(IComp * Comp, string Contact) {
	auto S = Contacts.begin();
	auto E = Contacts.end();
	auto X = find_if(S, E, [&](pair<string, IComp*> pair) {
		return pair.first == Contact && pair.second == Comp;
	});
	
	if (X != E)
		Contacts.remove(*X);
}

void Cir8::CConduit::OnVibrate(IComp * Comp, string Contact, void* Val) {
	auto S = Contacts.begin();
	auto E = Contacts.end();
	while (S != E) {
		if (S->first == Contact && S->second == Comp) {
			//Do nothing to prevent bouncing;
		}
		else {
			if (ParallelTrx) {
				thread t(Vibrate, this, S->first, S->second, Val);
				t.detach();
			}
			else
				Vibrate(this, S->first, S->second, Val);
		}
		S++;
	}
}

void Cir8::CConduit::Signal(void* Val) {
	this->OnVibrate(NULL, "", Val);
}

void Cir8::CConduit::Vibrate(IComp * From, string Contact, IComp * Comp, void* Val) {
	//cout <<hex << "Conduit vibrate to comp: [" << Comp
	//	<< "] at port: [" << Contact << "] - Val Address: [" << Val << "]" << endl;

	Comp->OnVibrate(From, Contact, Val);
}