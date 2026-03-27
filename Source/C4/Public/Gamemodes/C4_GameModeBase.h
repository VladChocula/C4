// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C4_GameModeBase.generated.h"

class AC4_player;

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameStateLeave, EC4GameState, LeavingGameState, EC4GameState, NextGameState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateStart, EC4GameState, EnteringGameState);

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	int32 PlayerScore = 0;
	class AC4_Player* PlayerObj = nullptr;
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
	void AddPlayerToPlayers(AC4_Player* newPlayer);
	
	FPlayerData* GetPlayerFromPlayers();

	FPlayerData* GetHighestPlayerScoreFromPlayers();

	UPROPERTY(BlueprintAssignable)
	FOnGameStateLeave OnGameStateLeave;

	UPROPERTY(BlueprintAssignable)
	FOnGameStateStart OnGameStateStart;

protected:

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TArray<FPlayerData> Players;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category = "Game Mode")
	TSubclassOf<AC4_Player> PlayerClass;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category = "Game Mode")
	float TimerTime = 120.f; //Defaulting to 2 mins.

	
};
