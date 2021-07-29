#define FKG_FORCED_USAGE 1
#include <sphelper.h>
#undef FKG_FORCED_USAGE
#include "BasicVoice.h"
class MaleType : public BasicVoice
{
private:
	CComPtr<ISpObjectToken> VoiceToken;
	CComPtr<IEnumSpObjectTokens> EnumToken;

public:
	void SpeakPhrase(wstring Phrase);
	void SetVoiceCharacter();
};
