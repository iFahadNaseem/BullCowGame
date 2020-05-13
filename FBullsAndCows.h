/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once
#include <string>

//=============================================== Assume Global Substitution Just for Unreal Syntax Standards =========================================================//
using FString = std::string;
using int32 = int;

//============================================================== All Values Initialsed To Zero ========================================================================//
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;	
};

enum class EGuess_Status
{
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase,
};

class FBullCowGame
{												
public:
	FBullCowGame();	// CONSTRUCTOR -User Defined.
								
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuess_Status IsGuessValid(FString) const; // TODO IN FUTURE UPDATES -Make A More Rich Return Value.
	
	void Reset();
	FBullCowCount SubmitValidGuess(FString) ; //This Provides A Method To Count Number Of BullsAndCows And Inceasing Try Numbers.
	
//Please Try To Ignore This And Focus On The Interface Above 
private:
	//See Constructor For Initialisation.
	int32 MyCurrentTry = 1;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString)const;
	bool IsLowerCase(FString)const;
	
};
//========================================================================= THE-END ===================================================================================//