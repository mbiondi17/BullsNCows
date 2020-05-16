// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <iostream>
#include <string>
#include <fstream>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Bull 'n' Cows!"));
    ShowInstructions();
    PrintLine(TEXT("Guess 'Introduction' to show this message.\n"));
    
    SetupGame();

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    if(Input.Compare("Introduction", ESearchCase::IgnoreCase) == 0) {
        ShowInstructions();
    }
    else {
        //increment guess number if valid guess (decide if we should penalize for invalid guesses))
        ++GuessesMade;
        if(Input.Compare(HiddenWord, ESearchCase::IgnoreCase) == 0) {
            PrintLine(TEXT("You guessed correctly! Yay!"));
        }
        else {
            //TODO: Parse Bulls & Cows & Inform
            //TODO: Check Length & Inform
            //TODO: Check Heterogram and inform
            //TODO: Check if all guesses expended & lose if so
            //TODO: else prompt for next guess.

            if(Input.Len() != HiddenWord.Len()) {
                PrintLine(TEXT("The guess was %i letters long, but \nthe hidden word is %i letters long."), Input.Len(), HiddenWord.Len());
            }

            PrintLine(TEXT("You Lose, and suck balls and vagene."));
        }
    }

    //TODO: if the game has been completed, prompt to play again.

}

void UBullCowCartridge::SetupGame() {
    MaxGuesses = 5;
    GuessesMade = 0;
    //Stretch-TODO: Get difficulty from user input
    //Stretch-TODO: Set word from appropriate difficulty list.
    //TODO: Set this from list
    HiddenWord = TEXT("Geisha");
    PrintLine(TEXT("You have %i attempts."), MaxGuesses);
    PrintLine(TEXT("The Heterogram is %i letters"), HiddenWord.Len());
    PrintLine(TEXT("Press enter to submit your guess.")); 
}

void UBullCowCartridge::ShowInstructions() {
    PrintLine(TEXT("Guess the Heterogram! Each guess will"));
    PrintLine(TEXT("reveal correct letters in the correct spot"));
    PrintLine(TEXT("('bulls') and correct letters in the wrong"));
    PrintLine(TEXT("spot ('cows')."));
}