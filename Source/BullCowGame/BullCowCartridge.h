// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void ProcessGuess(FString Guess);
	bool IsHeterogram(const FString& Guess);
	void SetupGame();
	void ShowInstructions();
	void EndGame(bool Victory);

	
	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 HiddenWordLen;
	int32 MaxGuesses;
	int32 GuessesMade;
	bool bGameFinished;

	
};
