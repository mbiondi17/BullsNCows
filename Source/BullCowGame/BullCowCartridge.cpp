// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "EasyHeterograms.h"
#include "MediumHeterograms.h"
#include "HardHeterograms.h"
#include "RidiculousHeterograms.h"
#include <iostream>
#include <string>
#include <fstream>
#include <locale>

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

    //TODO: I don't like this being on hitting enter; move it out.
    if(bGameFinished) {
        SetupGame();
        return;
    }
    
    if(Input.Compare("Introduction", ESearchCase::IgnoreCase) == 0) {
        ShowInstructions();
    }
    else {
        ProcessGuess(Input);
    }
}


#pragma region Helper Functions

void UBullCowCartridge::SetupGame() {
    GuessesMade = 0;
    bGameFinished = false;
    //Stretch-TODO: Get difficulty from user input
    //Stretch-TODO: Set word from appropriate difficulty list.
    //TODO: Set this from list

    int32 HiddenWordIndex = rand() % EasyHeterograms.Num(); 
    HiddenWord = EasyHeterograms[HiddenWordIndex];
    HiddenWordLen = HiddenWord.Len();
    MaxGuesses = HiddenWordLen;
    PrintLine(TEXT("You have %i attempts."), MaxGuesses);
    PrintLine(TEXT("The Heterogram is %i letters"), HiddenWordLen);
    PrintLine(TEXT("Press enter to submit your guess.")); 

}

void UBullCowCartridge::ShowInstructions() const {
    PrintLine(TEXT("Guess the Heterogram! Each guess will"));
    PrintLine(TEXT("reveal correct letters in the correct spot"));
    PrintLine(TEXT("('bulls') and correct letters in the wrong"));
    PrintLine(TEXT("spot ('cows')."));
}

void UBullCowCartridge::ProcessGuess(FString Guess) {
    if(Guess.IsEmpty()) {
        PrintLine(TEXT("You didn't type a guess. Try again."));
        return;
    }
    if(Guess.Len() != HiddenWordLen) {
        PrintLine(TEXT("The guess was %i letters long, but the \nhidden word is %i letters long. Try Again."), Guess.Len(), HiddenWordLen);
        return;
    }
    else if(!IsHeterogram(Guess)) {
        PrintLine(TEXT("Your word was not a heterogram; \nit contained 2 or more of the same letter."));
        return;
    }

    ++GuessesMade;
    if(Guess.Compare(HiddenWord, ESearchCase::IgnoreCase) == 0) {
        EndGame(true);
    }
    else {
        if(GuessesMade >= MaxGuesses) {
            EndGame(false);
        }
        else {
            PrintLine(TEXT("Incorrect! You have %i guesses remaining."), MaxGuesses-GuessesMade);
            ReportBullsAndCows(Guess);
        }
    }
}

bool UBullCowCartridge::IsHeterogram(const FString& guess) const {
    TMap<char, int32> LetterMap;
    for(int i = 0; i < guess.Len(); i++) {
        int32* charEntry = LetterMap.Find(guess[i]);
        if(charEntry == nullptr) {
            LetterMap.Add(guess[i], 1);
        }
        else return false;
    }
    return true;
    
}

void UBullCowCartridge::ReportBullsAndCows(const FString& guess) const {
    int32 bulls = 0;
    int32 cows = 0;
    
    TMap<char, int32> GuessMap;
    for(int i = 0; i < guess.Len(); i++) {
        char lowercase = std::tolower(guess[i], std::locale()); //need to ignore case in guess
        int32* charEntry = GuessMap.Find(lowercase);
        if(charEntry == nullptr) {
            GuessMap.Add(lowercase, i);
        }
    }

    for(int i = 0; i < HiddenWordLen; i++) { 
        char lowercase = std::tolower(HiddenWord[i], std::locale());
        if(GuessMap.Find(lowercase) != nullptr) {
            if(*GuessMap.Find(lowercase) == i) {
                bulls++;
            }
            else {
                cows++;
            }
        }
    }

    PrintLine(TEXT("Your Guess contained %i bulls and %i cows"), bulls, cows);
}

void UBullCowCartridge::EndGame(bool Victory) {
    bGameFinished = true;
    if(Victory) {
        PrintLine(TEXT("Congratulations, You win!"));
    }
    else
    {
        PrintLine(TEXT("Oh no! You've exhausted all your guesses!"));
        PrintLine(TEXT("The hidden word was %s. \nBetter luck next time."), *HiddenWord);
    }
    
    PrintLine(TEXT("Press Enter to play again."));
}

#pragma endregion
