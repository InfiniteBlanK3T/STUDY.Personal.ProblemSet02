#include "CharacterCounter.h"

CharacterCounter::CharacterCounter() noexcept
{
	fCharacterCounts[0];
	fTotalNumberOfCharacters = 0;
}

void CharacterCounter::count(unsigned char aCharacter) noexcept
{
	fCharacterCounts[aCharacter].setCharacter(aCharacter);
	fCharacterCounts[aCharacter].increment();
}

const CharacterMap& CharacterCounter::operator[](unsigned char aCharacter) const noexcept
{
	return fCharacterCounts[aCharacter];
}

