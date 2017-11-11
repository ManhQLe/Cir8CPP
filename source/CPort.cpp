#include "CPort.h"

Cir8::CPort::CPort()
{
}

void* Cir8::CPort::Get(const string Contact) {
	return Values[Contact];
}

void Cir8::CPort::Set(const string Contact, void * Val) {
	auto C = Contacts[Contact];
	if (C) { 		
		C->OnVibrate(Host, Contact, Val);
	}	
}

void Cir8::CPort::Connect(IComp * Comp, string Contact) {
}

void Cir8::CPort::DisconnectWith(IComp * Comp, string Contact) {
}

void Cir8::CPort::OnVibrate(IComp * Comp, string Contact, void* Val) {
	if (Contacts[Contact] == Comp) {
		Values[Contact] = Val;
	}
}

Cir8::CPort::~CPort()
{
	auto S = Values.begin();
	auto E = Values.end();
	while (S != E) {
		delete S->second;
		S++;
	}
	auto S1 = Contacts.begin();
	auto E1 = Contacts.end();
	while (S1 != E1) {
		delete S1->second;
		S1++;
	}
}
