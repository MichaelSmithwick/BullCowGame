#pragma once

#include <string>

// to make UnReal friendly
using FString = std::string;
using int32 = int;

// must be an isogram
//const FString HIDDEN_WORD = "planet";
const FString HIDDEN_WORD = "pan";

// all values initialized to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus // 'class enum' C++ 11 -- Keeps enumerations out of global scope permitting 'Ok' to be used in other enums
{
	Invalid,
	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Multiple_Words
};

class FBullCowGame
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	bool bMyGameIsWon;
	int32 MyCurrentTry;
	FString MyHiddenWord;
};
