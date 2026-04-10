// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/C4_GameModeBase.h"
#include "Player/C4_Player.h"
#include "Grid/C4_GridBase.h"
#include "Grid/GridLogic/C4_GridLogicBase.h"
#include "Kismet/GameplayStatics.h"

void AC4_GameModeBase::AddPlayerToPlayers(AC4_Player* newPlayer)
{
	if (!newPlayer) return;
	Players.Add(FPlayerData{ 0, newPlayer});
}

void AC4_GameModeBase::UpdatePlayerScore(AC4_Player* ScoringPlayer, float ScoreValue)
{
	for (auto& Player : Players)
	{
		if (Player.PlayerObj == ScoringPlayer)
		{
			Player.PlayerScore += (int32)ScoreValue;
		}
	}
}

FPlayerData* AC4_GameModeBase::GetPlayerFromPlayers()
{
	//TODO: Implement
	return nullptr;
}

FPlayerData* AC4_GameModeBase::GetHighestPlayerScoreFromPlayers()
{
	FPlayerData* HighestPlayer = nullptr;
	int32 HighestScore = 0;

	for (auto& Player : Players)
	{
		if (Player.PlayerScore > HighestScore)
		{
			HighestScore = Player.PlayerScore;
			HighestPlayer = &Player;
		}

		//TODO: Create logic to handle tie events
	}

	return HighestPlayer;
}

void AC4_GameModeBase::TransitionGameState(EC4GameState NewState)
{
	OnGameStateLeave.Broadcast(CurrentGameState, NewState);
	CurrentGameState = NewState;
	OnGameStateStart.Broadcast(CurrentGameState);
}

void AC4_GameModeBase::PlayerSetup(APlayerController* NewPlayerController)
{
	if (!NewPlayerController || !PlayerClass) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = NewPlayerController;

	AC4_Player* NewPlayer = GetWorld()->SpawnActor<AC4_Player>(
		PlayerClass,
		PlayerSpawnLocation,
		PlayerSpawnRotation,
		SpawnParams
	);

	if (NewPlayer)
	{
		NewPlayerController->Possess(NewPlayer);
		NewPlayer->SetPlayerID(Players.Num() + 1);
		AddPlayerToPlayers(NewPlayer);
	}
}

void AC4_GameModeBase::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);
	PlayerSetup(NewPlayerController);
}

void AC4_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Grid = Cast<AC4_GridBase>(UGameplayStatics::GetActorOfClass(GetWorld(), AC4_GridBase::StaticClass()));

	if (Grid && Grid->GridLogic)
	{
		Grid->GridLogic->OnPlayerScored.AddDynamic(this, &AC4_GameModeBase::UpdatePlayerScore);
	}
}
