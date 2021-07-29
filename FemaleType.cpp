#include "FemaleType.h"
void FemaleType::SpeakPhrase(wstring Phrase)
{
	checkstatus();
	Access_Holder = BotVoice->Speak((L"<voice required='Gender = Female;'>" + Phrase).c_str(), SPF_ASYNC, NULL);
}
void FemaleType::SetVoiceCharacter()
{
}
