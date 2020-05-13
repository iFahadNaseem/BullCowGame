/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullsAndCow class in header file.
*/
#pragma once
//================================================================ Libraries / Header Files ===========================================================================//

#include<iostream>
#include<string>
#include "FBullsAndCows.h"

//============================================================ Subtitue string & int Into Unreal Syntax ===============================================================//

using FText = std::string;
using int32 = int;

//================================================================== Function Prototypes ==============================================================================//

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


//================================================= Global Declaration Of BCGame Functionalities | Instantiating  BCGame ================================================//
FBullCowGame BCGame;

//========================================================= Enrty Point Of The Game Or Application =====================================================================//
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0; //Exit Point Of Game Or Application.
}

//===================================== Following ,Listed Bellow, Are The Decalred Functions With Their Respective Code Of Lines=======================================//

// Print An Introduction For Player
void PrintIntro()
{
	// The legendary Introduction Of The Game Duhh..
	// The constexpr is function which sets the lenght of any type of variable ,here we use it in our introducion.
	
	std::cout << " _____________________________________________________________________________ \n";
	std::cout << "|                Welcome to Bulls and Cows, a fun word game                   | \n";
	std::cout << "|-----------------------------------------------------------------------------| \n";
	std::cout << "|-----------------------------------------------------------------------------| \n";
	std::cout << "|      ,           ,                             ,     ,                      | \n" ;
	std::cout << "|     /             \\                       ___('-&&&-')___                   | \n";
	std::cout << "|    ((__-^^-,-^^-__))                      '.__./     \\__.'                  | \n";
	std::cout << "|     `-_---' `---_-'                         .-'  6  6 \\                     | \n";
	std::cout << "|      <__|o` 'o|__>                                     |                    | \n";
	std::cout << "|         \\  `  /      BULL                       \\ _   _|     COW            | \n";
	std::cout << "|          ): :(                              |    (0_._0)                    | \n";
	std::cout << "|          :o_o:                               |  / '---'                     | \n";
	std::cout << "|          ' - '                                                              | \n";
	std::cout << "|_____________________________________________________________________________|\n";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// Plays Single Game To Completion
void PlayGame()
{
	// Firstly Reset The Game To Default Values
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//  Loop For Asking The Guesses WHILE: 
	// Game Is NOT Won And There Are Still Some Tries Remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		
			FText Guess = GetValidGuess();

			//Submit A Valid Guess To The Game And Receive BullsCowsCount.
			FBullCowCount BullsCowsCount = BCGame.SubmitValidGuess(Guess);

			//Print Number of Bulls and Cows.
			std::cout << "Bulls = " << BullsCowsCount.Bulls;
			std::cout << ". Cows = " << BullsCowsCount.Cows << "\n\n";
	}
	// Game Summary.
	PrintGameSummary();
	return;
}

// Loop Continually Untill The User Gives A Valid Guess.
FText GetValidGuess() 
{
	FText Guess = "";
	EGuess_Status Status = EGuess_Status::Invalid_status;
	// Now we will get the iput from the player or just say it like itwould be the guess by the player :d
	// Here we use getline () intead of cin so that we can also enter a line of words with spaces like "Donkey Kong".
	do
	{
		//Get Guess From Player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "[ Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << "]  Enter Your Guess :";
		std::getline(std::cin, Guess);

		//Check Guess Status And Response To The Feedback
		Status = BCGame.IsGuessValid(Guess);
		switch (Status)
		{
		case EGuess_Status::Wrong_Length:
			std::cout << "Please Enter A " << BCGame.GetHiddenWordLength() << " Letter Word !\n\n";
		break;
		
		case EGuess_Status::Not_Isogram:
			std::cout << "Do You Think You Can Fool Me? Do Not Repeat Same Letters More Than Once !\n\n";
		break;
		
		case EGuess_Status::Not_LowerCase:
			std::cout << "Sorry But You Have To Use Lowercase-Letters !\n\n";
		break;
		
		default:
			// Assume The Guess Is Valid / Guess Status Ok
		break;
		} 
	} while (Status != EGuess_Status::OK); //Keep Looping Until There Are No Errors
	return Guess;	  
}

// Collect Feedback Response At The End 
bool AskToPlayAgain()
{
	std::cout << "Do You Want To Play Again With The Same Hidden Word? (y/n)\t";
	FText Response = "";
	std::getline(std::cin, Response);
	return  (Response[0] == 'Y') || (Response[0] == 'y');
}

// Print Game Summary After Game Completion
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Winner Winner - Chicken Dinner !\n";
	}
	else
	{
		std::cout << "Better Luck Next Time Chicken !!\n";
	}
}
//========================================================================== The-End ==================================================================================//