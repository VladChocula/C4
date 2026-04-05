// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gamemodes/C4_GameModeBase.h"
#include "C4_TimerGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerTick, float, TimeRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerExpired);

/**
 * 
 */
UCLASS()
class C4_API AC4_TimerGameMode : public AC4_GameModeBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable, Category="Timer")
	FOnTimerTick OnTimerTick;

	UPROPERTY(BlueprintAssignable, Category="Timer")
	FOnTimerExpired OnTimerExpired;
	
protected:
	
	virtual void BeginPlay() override;

	virtual void TransitionGameState(EC4GameState NewState) override;


private:

	FTimerHandle CountdownTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"), Category="Timer")
	float TimeRemaining = 120.f;

	UFUNCTION()
	void OnCountdownTick();
	
};
