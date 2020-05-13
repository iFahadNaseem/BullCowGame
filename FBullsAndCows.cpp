#pragma once

#include "FBullsAndCows.h"
#include <map>

//=============================================== Make Friendly Syntax According To UnrealEngineC++ Standards =========================================================//

#define TMap std::map
using int32 = int;

//==================================================== All Methods/functionalities Implemented In BCGame ==============================================================//


// Default Constructor
FBullCowGame::FBullCowGame() { Reset(); }

// Get The Current Guessing Try
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

// Get The Actual Length Of The HiddenIsogram
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

// Check If Game Is Won
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

// Get The Maximum Tries For The Player 
int32 FBullCowGame::GetMaxTries() const 
{
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,6}, {5,10}, {6,115} ,{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

// Reset The Game
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plane"; // This Must Be An Isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// Validte Player's Guess According To The Terms/Conditions
EGuess_Status FBullCowGame::IsGuessValid(FString Guess) const
{
	//Check If The Word Is Not Isogram ,then:
	if (!IsIsogram(Guess))
	{
		return	EGuess_Status::Not_Isogram;
	}
	//Check If There's Any Lowercase Used ,then:
	else if (!IsLowerCase(Guess))
	{
		return EGuess_Status::Not_LowerCase;
	}
	//Check If There Are Any Word Length Errors ,then: 
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuess_Status::Wrong_Length;
	}
	//If Everythings Fine, No Errors Found, then: 
	else
	{
		return EGuess_Status::OK;
	}
}

// Recieves A Validated Guess ,Increment Turn/try , And Return Counts.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//Increment CurrentTurn.
	MyCurrentTry++;

	//Setup Or Declare A Return Varibale.
	FBullCowCount BullCowCount;

	//Consider / Assume Same Lenght As Guess
	int32 WordLength = MyHiddenWord.length();
	
	//Loop Through All Letters In The HiddenWord
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {	
		
		//Compare Letters Against Guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			
			//Check If They Match :
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {

				//Increment Bulls, If They Are In The Same Place.
				if (MHWChar == GChar) { 
					BullCowCount.Bulls++; 
				}
				//Else Are On A Different Spot ,Then Increment Cows.
				else {
					BullCowCount.Cows++; 
				}
			}
		}

	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

// Check If The Player's Guess Is An Isogram i.e No Repaeted Letters 
bool FBullCowGame::IsIsogram(FString Word) const
{
	//Consider 0 and 1 Letters Words also as isograms
	if (Word.length() <= 1) {return true;}

	TMap <char, bool> LetterSeen; //setup our map
	for (auto Letter : Word) //Loop through all the letters of the word  (including numeric(0 to 9) / characters (#,$,% etc)
	//[Auto] used above!, will detect and declare the letter type int,char 
	{
		Letter = tolower(Letter); //handle mixed case words
		//Check if the letter is in the map 
		if (LetterSeen[Letter]) { 
			//if the letter is in the map
			return false;} //we do'nt have the isogram i.e false
		else //otherwise
		{
			LetterSeen[Letter] = true;
		} //add the letter to the map as seen i.e true 		
	}
	return true;//for example in cases where 0/1 is entered
}

// Check The Player's Guess For Uppercase Letters 
bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}




//========================================================================== The-End ==================================================================================//