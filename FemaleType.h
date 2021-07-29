#pragma once
#include "BasicVoice.h"
class FemaleType : public BasicVoice
{
public:
	void SpeakPhrase(wstring Phrase);
	void SetVoiceCharacter();
};
