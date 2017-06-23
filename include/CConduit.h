#pragma once
#include "CComp.h"
namespace Cir8 {	
	class CConduit :public CComp {
	private:		
		map<string, IComp*> Contacts;
	public:
		CConduit(string name);

		CConduit();
		
		bool ParallelTrx = true;
		virtual void Connect(IComp * Comp, string Contact); 
		virtual void DisconnectWith(IComp * Comp, string Contact); 

		void OnVibrate(IComp * Comp, string Contact, void* Val);

		void Signal(void*Val);

		static void Vibrate(IComp *From, string Contact, IComp* Comp, void* Val);
	};
}