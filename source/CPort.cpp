#include "CPort.h"

Cir8::CPort::CPort()
{
}

template <typename T>
T Cir8::CPort::Get(const string Contact) {
	return *(T*)Values[Contact];
}

void Cir8::CPort::Set(const string Contact, void * Val) {
	auto C = Contacts[Contact];
	if (C) C->OnVibrate(this, Contact, Val);
}

void Cir8::CPort::Connect(IComp * Comp, string Contact) {
}

void Cir8::CPort::DisconnectWith(IComp * Comp, string Contact) {
}

void Cir8::CPort::OnVibrate(IComp * Comp, string Contact, void*  Val) {
	if (Contacts[Contact] == Comp) {
		Values[Contact] = Val;
	}
}