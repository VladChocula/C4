// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/Timer/C4_TimerGameMode.h"

void AC4_TimerGameMode::BeginPlay()
{
	Super::BeginPlay();
	TransitionGameState(EC4GameState::PreGame);
}

void AC4_TimerGameMode::TransitionGameState(EC4GameState NewState)
{
	Super::TransitionGameState(NewState);

	if (NewState == EC4GameState::ActiveGame)
	{
		GetWorldTimerManager().SetTimer(
			CountdownTimerHandle,
			this,
			&AC4_TimerGameMode::OnCountdownTick,
			1.0f,    // Interval
			true	// Looping
		);
	}

	else if (NewState == EC4GameState::GameEnd)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	}
}

void AC4_TimerGameMode::OnCountdownTick()
{
	TimeRemaining -= 1.0f;
	OnTimerTick.Broadcast(TimeRemaining);

	if (TimeRemaining <= 0.f)
	{
		TransitionGameState(EC4GameState::GameEnd);
	}
}
