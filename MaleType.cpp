#define FKG_FORCED_USAGE 1
#include <sphelper.h>
#undef FKG_FORCED_USAGE
#include "MaleType.h"
void MaleType::SpeakPhrase(wstring Phrase)
{
	checkstatus();
	Access_Holder = BotVoice->Speak(Phrase.c_str(), SPF_ASYNC, NULL);
}
void MaleType::SetVoiceCharacter()
{
	if (SUCCEEDED(Access_Holder))
	{
		Access_Holder = SpEnumTokens(L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Speech_OneCore\\Voices", NULL, NULL, &EnumToken);
	}
	if (SUCCEEDED(Access_Holder))
	{
		Access_Holder = EnumToken->Item(1, &VoiceToken);
	}
	if (SUCCEEDED(Access_Holder))
	{
		Access_Holder = BotVoice->SetVoice(VoiceToken);
		Access_Holder = BotVoice->SetRate(0);
	}
}