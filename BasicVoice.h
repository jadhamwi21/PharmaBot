#pragma once
#define FKG_FORCED_USAGE 1
#include <sphelper.h>
#undef FKG_FORCED_USAGE
#include <iostream>
#include <sapi.h>
using namespace std;
class BasicVoice
{
protected:
	HRESULT Access_Holder;
	ISpVoice *BotVoice;
	SPVOICESTATUS *temp;

public:
	BasicVoice();
	virtual void SpeakPhrase(wstring Phrase) = 0;
	static BasicVoice *CreateGendre(string Gendre);
	void checkstatus()
	{
		Access_Holder = BotVoice->GetStatus(temp, NULL);
		if (temp->dwRunningState == SPRS_IS_SPEAKING)
		{
			BotVoice->Speak(nullptr, SPF_ASYNC | SPF_PURGEBEFORESPEAK, nullptr);
		}
	}
	virtual void SetVoiceCharacter() = 0;
};