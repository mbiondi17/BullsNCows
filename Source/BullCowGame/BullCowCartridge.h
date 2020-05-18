// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void ProcessGuess(const FString& Guess);
	bool IsHeterogram(const FString& Guess) const;
	FBullCowCount ReportBullsAndCows(const FString& Guess) const;
	void SetupGame();
	FString GetHiddenWord(const int32& minLen,const int32& maxLen) const;
	void ShowInstructions() const;
	void EndGame(const bool& Victory);

	
	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 HiddenWordLen;
	int32 MaxGuesses;
	int32 GuessesMade;
	bool bGameFinished;	
};
