// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordsList.h"
#include "Math/UnrealMathUtility.h"
#include <set>

/*
    TEXT(x) macros is defined in Platform.h

    adds L == w_char OR u == char16_t
    this is platform depended
*/

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame();   
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();    

    if (bGameFinished)
    {
        if (Input.ToLower().Equals("y")) 
        {
            InitGame();
        }
        else
        {
            EndGame();
        }
    }
    else
    {
        ProcessGuess(Input);
    }    
}

void UBullCowCartridge::InitGame()
{
    int32 RandomIndex = FMath::RandRange(0, HiddenWords.Num() - 1);
    HiddenWord = HiddenWords[RandomIndex];
    HiddenWordLength = HiddenWord.Len();
    Lives = 3;
    bGameFinished = false;

    PrintLine(TEXT("The hidden word is %s."), *HiddenWord);
    PrintLine(TEXT("Welcome to the BullCowGame!"));
    PrintLine(TEXT("Guess the %i letter word!\nYou have %i lives."), HiddenWordLength, Lives);
    PrintLine(TEXT("Enter your guess:"));    
}

void UBullCowCartridge::EndGame()
{
    bGameFinished = true;
    PrintLine(TEXT("Enter Y to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Input)
{
    if (HiddenWord.Equals((Input.ToLower())))
    {
        PrintLine(TEXT("You win!"));
        EndGame();
    }
    else
    {
        CheckGuessFormat(Input);
        if (--Lives <= 0)
        {
            PrintLine(TEXT("You lose!"));
            EndGame();
        }
        else
        {
            auto BullCows = GetBullCows(Input);
            PrintLine(TEXT("You have %i  bulls and %i Cows."), BullCows.first, BullCows.second);
            PrintLine(TEXT("Guess again, you have %i  lives left!"), Lives);
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Input) const
{
    std::set<TCHAR> UniqueSymbols(Input.begin(), Input.end());
    return Input.Len() == UniqueSymbols.size();
}

void UBullCowCartridge::CheckGuessFormat(const FString& Input) const
{
    if (HiddenWordLength != Input.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long!"), HiddenWordLength);
    }
    else if (!IsIsogram(Input))
    {
        PrintLine(TEXT("Hidden word is an isogram!"));
    }
}

std::pair<int32, int32> UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    int32 BullCount{ 0 };
    int32 CowCount{ 0 };

    for (int32 GuessIndes = 0; GuessIndes < Guess.Len(); ++GuessIndes)
    {
        if (Guess[GuessIndes] == HiddenWord[GuessIndes])
        {
            ++BullCount;
            continue;
        }

        for (int32 HiddenIndex = 1; HiddenIndex < HiddenWord.Len(); ++HiddenIndex)
        {
            if (Guess[GuessIndes] == HiddenWord[HiddenIndex])
            {
                ++CowCount;
                break;
            }
        }
    }

    return std::make_pair(BullCount, CowCount);
}