// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C4_GameModeBase.generated.h"


UENUM(BlueprintType)
enum class EC4GameState : uint8
{
	PreGame,
	PlayerReady,
	GameStartCountdown,
	GameStart,
	ActiveGame,
	GameEnd,
	SessionCleanup,
	PostGame
};

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	int32 PlayerScore = 0;
	AActor* PlayerObj = nullptr;
};
/**
 * 
 */
UCLASS()
class C4_API AC4_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPlayerToPlayers(APawn* newPlayer);
	
	UFUNCTION(BlueprintCallable)
	GetPlayerFromPlayers();
	GetHighestPlayerScoreFromPlayers();
protected:

private:
	TArray<FPlayerData> Players;
	
};
