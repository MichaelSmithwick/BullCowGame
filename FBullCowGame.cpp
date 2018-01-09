#include <map>
#include "FBullCowGame.h"

// to make UnReal friendly
// we don't use 'using' semantics because map is mapped with different types
#define TMap std::map

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bMyGameIsWon = false;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

// The maximum number of trys given to the player is decided by the length of the hidden word
int32 FBullCowGame::GetMaxTries() const
{
	// maximum tries follows this formula 3n+1 where n is the length of the word
	TMap<int32, int32> WordLengthToMaxTries{ {1,4},{2,7},{3,10},{4,13},{5,16},{6,19},{7,22} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() < 2)
	{
		return true;
	}

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter])
		{
			return false; // the letter has already been seen
		}
		else
		{
			LetterSeen[Letter]=true; // letter not seen, set to true
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() < 1)
	{
		return true; // no characters to check, must be true
	}

	for (auto Letter : Word)
	{
		if (!isalpha(Letter))
		{
			return false; // fail if not an alphabet character
		}
		if (!islower(Letter))
		{
			return false; // fail when Letter is uppercase
		}
	}

	return true; // all alphabet characters and all lowercase
}

bool FBullCowGame::IsGameWon() const
{
	return bMyGameIsWon; // true if won, false otherwise
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess is not an isogram return error
	{
		return EGuessStatus::Not_Isogram;
	}
	else if(!IsLowercase(Guess)) // if guess is not lowercase return error
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is mismatched return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (false) // if multiple words input return error
	{
		return EGuessStatus::Multiple_Words;
	}
	else // otherwise return ok ???
	{
		return EGuessStatus::Ok;
	}
}

// received a VALID guess, increments turn, and returns Bull/Cow count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++; // increment turn number
	FBullCowCount BullCowCount; // create return variable
	
	// SizeHiddenWord should be same as SizeGuessWord
	// because only valid Guesses should be passed to this function.
	int32 SizeHiddenWord = MyHiddenWord.length();
	int32 SizeGuessWord = Guess.length();

	for (int32 i = 0; i < SizeHiddenWord; i++) // loop through all letters in the guess
	{
		for (int32 j = 0; j < SizeGuessWord; j++)
		{
			
			if (Guess[j] == MyHiddenWord[i]) // compare letters against the hidden word
			{
				if (j == i) // and if they match
				{
					BullCowCount.Bulls++; // increment Bull if characters are in same location
				}
				else
				{
					BullCowCount.Cows++; // or increment Cow if they are not in same location
				}
				break;  // no need to check more, this is an isogram, the character should match only one time
			}
		}
		
	}

	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bMyGameIsWon = true; // all characters match and are in matching positions
	}
	else
	{
		bMyGameIsWon = false;
	}

	return BullCowCount; // the count of Bulls and Cows found
}
