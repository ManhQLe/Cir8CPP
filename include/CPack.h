#pragma once
#include "CComp.h"
#include "CPort.h"
#include <algorithm>
#include <mutex>
namespace Cir8 {
	class CPack :public CComp {	
	private:
		mutex locker;
	public:
		typedef void(*CPackFx)(CPack *);
		unsigned int ICount = 0;
		bool Stage = false;
		vector<string> Ins;
		void *Props;
		CPort Ports;
		//void (*FX)(CPack *);
		CPackFx FX;

		CPack(string name);
		CPack();

		void SetStage(bool s);

		void Connect(IComp * Comp, string Contact);

		void DisconnectWith(IComp * Comp, string Contact);

		void OnVibrate(IComp * Comp, string Contact, void* Val); 

		~CPack();
	};		
}