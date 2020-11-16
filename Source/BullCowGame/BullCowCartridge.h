// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <utility>
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
	void InitGame();
	std::pair<int32, int32> GetBullCows(const FString& Guess) const;

	// Your declarations go below!
	private:
		FString HiddenWord;
		int32 HiddenWordLength;
		int32 Lives;
		bool bGameFinished;

		void EndGame();
		void ProcessGuess(const FString& Input);
		bool IsIsogram(const FString& Input) const;
		void CheckGuessFormat(const FString& Input) const;
};
