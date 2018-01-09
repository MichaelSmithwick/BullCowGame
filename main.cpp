/*
 * This is the console executable that makes use of the BullCow class
 * This acts as the view in a MVC pattern and is responsible for all
 * user interaction. For game logic see the FBullCowGame class
 */

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make UnReal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
void PrintStatus(const EGuessStatus & Status);
void PrintGuess(const FText& Guess,const FBullCowCount& BullCowCount);
bool AskToPlayAgain();

FBullCowGame BCGame;

// application entry point
int main()
{
	do
	{
		BCGame.Reset();
		PrintIntro();
		PlayGame();
	}
	while(AskToPlayAgain());
	return 0;
}

// display the game introduction
void PrintIntro()
{
	std::cout << "\n\n";
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n" << std::endl;
	std::cout << "          }   {       ___           " << std::endl;
	std::cout << "          (o o)      (o o)          " << std::endl;
	std::cout << "   /-------\\ /        \\ /-------\\   " << std::endl;
	std::cout << "  / | BULL |O          O| COW  | \\  " << std::endl;
	std::cout << " *  |-,--- |            |------|  * " << std::endl;
	std::cout << "    ^      ^            ^      ^    " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n" << std::endl;
}

// Player gets a number of guesses at the correct word
void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();

	// loop while game is not won and there are still guesses available
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount=BCGame.SubmitValidGuess(Guess);
		PrintGuess(Guess,BullCowCount);
	}

	PrintGameSummary(); // prints win/loss message to user
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You Won, congratulations!\n" << std::endl;
	}
	else
	{
		std::cout << "Good try, better luck next time.\n" << std::endl;
	}
}

// loop continues until valid guess entered
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";

	do
	{
		// get player input.
		std::cout << "My Current Try: " << BCGame.GetCurrentTry();
		std::cout << " of " << BCGame.GetMaxTries() << std::endl;
		std::cout << "Enter your guess : ";
		Guess = "";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess); // is player input valid?
		PrintStatus(Status); // print an error message if it is not.
	} while (Status != EGuessStatus::Ok); // if player input is not valid try again.

	return Guess;
}

// status returned by CheckGuessValidity() function
void PrintStatus(const EGuessStatus& Status)
{
	switch (Status)
	{
	case EGuessStatus::Wrong_Length:
		std::cout << "Word must be " << BCGame.GetHiddenWordLength() << " characters." << std::endl;
		break;
	case EGuessStatus::Not_Isogram:
		std::cout << "Word must be an Isogram (all letters in the word must be unique)." << std::endl;
		break;
	case EGuessStatus::Not_Lowercase:
		std::cout << "Use only lower case characters in your word." << std::endl;
		break;
	case EGuessStatus::Multiple_Words:
		std::cout << "One word per try." << std::endl;
		break;
	case EGuessStatus::Ok:
		break;
	default:
		std::cout << "Unknown error occurred." << std::endl;
		break;
	}

	if (Status != EGuessStatus::Ok)
	{
		std::cout << "Please try again.\n" << std::endl; // give some encouragement...
	}
	else
	{
		std::cout << std::endl;
	}
}

// display the players guess and the number of bulls and cows from the guess
// @param Guess - input string with players guess
// @param BullCowCount - a FBullCowStruct containing the count of Bulls and Cows for the players Guess
// @returns void
void PrintGuess(const FText& Guess,const FBullCowCount& BullCowCount)
{
	std::cout << "Your guess was " << Guess <<std::endl;
	std::cout << "Bulls : " << BullCowCount.Bulls;
	std::cout << " Cows : " << BullCowCount.Cows;
	std::cout << "\n" << std::endl;
}

// does player want to play another game?
// returns true if player wants to play again, false otherwise
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}
	
