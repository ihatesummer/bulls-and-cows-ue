// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if(bGameOver){
        ClearScreen();
        SetupGame();
    }
    else{
        ProcessTheGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame(){
    HiddenWord = TEXT("spring");
    Attempts = 5;
    bGameOver = false;
    PrintLine(FString::Printf(TEXT("Give me the %i-long isogram password."), HiddenWord.Len()));
    PrintLine(TEXT("5 tries. If you fail, these bulls and cows will murder you."));
}

void UBullCowCartridge::EndGame(){
    bGameOver = true;
}

void UBullCowCartridge::ProcessTheGuess(const FString& Guess){

    if(Guess==HiddenWord){
        PrintLine(TEXT("ok bye."));
        EndGame();
        return;
        }
    else{
        --Attempts;

        if(Attempts<=0){
            PrintLine(TEXT("YOU DIED"));
            PrintLine(FString::Printf(TEXT("The password was %s."), *HiddenWord));
            EndGame();
        }
        else{
            if(!IsIsogram(Guess) || Guess.Len()!=HiddenWord.Len()){
                PrintLine(FString::Printf(TEXT("I said the password is %i-long isogram."), HiddenWord.Len()));
            }
            else{
                int32 Bulls, Cows;

                //Give number of bulls and cows
                //the corresponding number of bulls and cows turn into harmless creatures
            }
            PrintLine(FString::Printf(TEXT("You have %i attempt(s) remaining and nobody loves you."), Attempts));
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Guess) const{
    for(int32 i = 0; i<Guess.Len()-1; i++){
        for(int32 j = i+1; j<Guess.Len(); j++){
            if(Guess[i]==Guess[j]){
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const{
    BullCount = 0;
    CowCount = 0;

    for(int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++){
        if(Guess[GuessIndex]==HiddenWord[GuessIndex]){
            BullCount++;
            continue;
        }
        
        for (int32 HiddenIndex=0; HiddenIndex < HiddenWord.Len(); HiddenIndex++){
            if(Guess[GuessIndex]==HiddenWord[HiddenIndex]){
                CowCount++;
            }
        }
    }
}