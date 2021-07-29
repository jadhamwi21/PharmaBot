#define FKG_FORCED_USAGE 1
#include <sphelper.h>
#undef FKG_FORCED_USAGE
#include "BasicVoice.h"
#include "FemaleType.h"
#include "MaleType.h"
BasicVoice::BasicVoice()
{
	BotVoice = NULL;
	if (FAILED(::CoInitialize(NULL)))
	{
		auto Boolean = ::CoInitialize(NULL);
		if (FAILED(Boolean))
		{
			cout << "Failed Initializing COM" << endl;
			return;
		}
	}
	Access_Holder = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&BotVoice);
	if (SUCCEEDED(Access_Holder))
		cout << "Voice Object Successfully Created" << endl;
	else
		cout << "Failed !! " << endl;
	temp = new SPVOICESTATUS();
}
BasicVoice *BasicVoice::CreateGendre(string Gendre)
{
	if (Gendre == "Male")
	{
		BasicVoice *temp = new MaleType();
		temp->SetVoiceCharacter();
		return temp;
	}
	else
	{
		BasicVoice *temp = new FemaleType();
		temp->SetVoiceCharacter();
		return temp;
	}
}