// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C4_GameModeBase.generated.h"

class AC4_player;
class AC4_GridBase;

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

UENUM(BlueprintType)
enum class EC4PlayerCountConfig : uint8
{
	OneVOne,
	TwoVTwo,
	FourPFFA,
	OnevOnevOnevOne,
	Solo
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

	UFUNCTION(BlueprintCallable)
	EC4GameState GetCurrentGameState() const { return CurrentGameState; }

	UFUNCTION(BlueprintCallable)
	void SetPlayerCountConfig(EC4PlayerCountConfig NewPlayerCountConfig) { PlayerCountConfig = NewPlayerCountConfig; }

	UFUNCTION(BlueprintCallable)
	EC4PlayerCountConfig GetPlayerCountConfig() const { return PlayerCountConfig; }

	UFUNCTION(BlueprintCallable, Category = "Score Logic")
	void UpdatePlayerScore(AC4_Player* ScoringPlayer, float ScoreValue);
	
	FPlayerData* GetPlayerFromPlayers();

	FPlayerData* GetHighestPlayerScoreFromPlayers();

	UPROPERTY(BlueprintAssignable)
	FOnGameStateLeave OnGameStateLeave;

	UPROPERTY(BlueprintAssignable)
	FOnGameStateStart OnGameStateStart;

	UPROPERTY(BlueprintReadOnly, Category="Grid")
	AC4_GridBase* Grid;

protected:

	UFUNCTION(BlueprintCallable, Category="Game Mode")
	virtual void TransitionGameState(EC4GameState NewState);

	UFUNCTION(BlueprintCallable, Category="Game Mode")
	void PlayerSetup(APlayerController* NewPlayerController);

	virtual void PostLogin(APlayerController* NewPlayerController) override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	TArray<FPlayerData> Players;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category = "Game Mode")
	TSubclassOf<AC4_Player> PlayerClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category = "Game Mode")
	EC4GameState CurrentGameState = EC4GameState::PreGame;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Game Mode")
	EC4PlayerCountConfig PlayerCountConfig = EC4PlayerCountConfig::OneVOne;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Spawn Parameters")
	FVector PlayerSpawnLocation = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Spawn Parameters")
	FRotator PlayerSpawnRotation = FRotator::ZeroRotator;
};
