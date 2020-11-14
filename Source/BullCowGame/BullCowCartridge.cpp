// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordsList.h"
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
    HiddenWord = TEXT("car");
    HiddenWordLength = HiddenWord.Len();
    Lives = 3;
    bGameFinished = false;

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
            PrintLine(TEXT("You have %i  lives left, try again!"), Lives);
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