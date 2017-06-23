#include "C1Way.h"

Cir8::C1Way::C1Way(string name):CComp(name)
{
}

Cir8::C1Way::C1Way():CComp()
{
}

void Cir8::C1Way::Connect(IComp * Comp, string Contact)
{
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

void Cir8::C1Way::DisconnectWith(IComp * Comp, string Contact)
{
	auto C = Contacts[Contact];
	if (C) {
		Contacts.erase(Contact);
		C->DisconnectWith(Comp, Contact);
	}
}


void Cir8::C1Way::OnVibrate(IComp * Comp, string Contact, void* Val)
{
	if (Contact == "IN"&& Contacts["IN"] == Comp) {
		auto C = Contacts["OUT"];
		if (C)
			C->OnVibrate(this, "OUT", Val);
	}
}
