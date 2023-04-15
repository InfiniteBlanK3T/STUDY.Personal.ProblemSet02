#include "CharacterFrequencyIterator.h"

void CharacterFrequencyIterator::mapIndices() noexcept
{
	for (size_t i = 0; i < 256; i++)
	{
		fMappedIndices[i] = static_cast<unsigned char>(i);
	}

	for (size_t i = 1; i < 256; i++)
	{
		unsigned char other = fMappedIndices[i];
		size_t j = i - 1;

		while (j < 256 && (*fCollection)[fMappedIndices[j]].frequency() < (*fCollection)[other].frequency())
		{
			fMappedIndices[j + 1] = fMappedIndices[j];

			if (j == 0) break;
			j--;

		}
		fMappedIndices[j + 1] = other;
	}
}


CharacterFrequencyIterator::CharacterFrequencyIterator(const CharacterCounter* aCollection) noexcept :
	fCollection(aCollection),
	fIndex(1)
{
	mapIndices();
}

const CharacterMap& CharacterFrequencyIterator::operator*() const noexcept
{
	return (*fCollection)[fMappedIndices[fIndex]];
}

CharacterFrequencyIterator& CharacterFrequencyIterator::operator++() noexcept
{
	fIndex++;
	return *this;
}

CharacterFrequencyIterator CharacterFrequencyIterator::operator++(int) noexcept
{
	CharacterFrequencyIterator old = *this;
	++(*this);
	return old;
}

bool CharacterFrequencyIterator::operator==(const CharacterFrequencyIterator& aOther) const noexcept
{
	return fCollection == aOther.fCollection && fIndex == aOther.fIndex;
}

bool CharacterFrequencyIterator::operator!=(const CharacterFrequencyIterator& aOther) const noexcept
{
	return !(*this == aOther);
}

CharacterFrequencyIterator CharacterFrequencyIterator::begin() const noexcept
{
	CharacterFrequencyIterator result(fCollection);
	return result;
}

CharacterFrequencyIterator CharacterFrequencyIterator::end() const noexcept
{
	CharacterFrequencyIterator result(fCollection);

	for (size_t i = 1; i < 256; i++) {
		if ((*fCollection)[fMappedIndices[i]].frequency() == 0) 
		{
			result.fIndex = i;
			return result;
		}
	}

	return result;
}
