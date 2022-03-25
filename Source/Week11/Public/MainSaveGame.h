// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MainSaveGame.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerStats {
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "SavingData")
	FVector PlayerLocation;
	UPROPERTY(VisibleAnywhere, Category = "SavingData")
	FRotator PlayerRotation;

	// add health, ammo  and other variables you want to save and load in your game

};


UCLASS()
class WEEK11_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
		UMainSaveGame();
		UPROPERTY(EditAnywhere, Category="SavingData")
		FString PlayerName;
		UPROPERTY(EditAnywhere, Category = "SavingData")
		int32 PlayerIndex;
		FPlayerStats PlayerStat;

};
