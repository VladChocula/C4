// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C4_GridLogicBase.generated.h"

class AC4_Player;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerScored, AC4_Player*, ScoringPlayer, float, ScoreValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C4_API UC4_GridLogicBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC4_GridLogicBase();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerScored OnPlayerScored;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	TArray<int32> Grid;
	
	int32 GetIndex(int32 Row, int32 Col) const;

	bool CheckWin(int32 Row, int32 Col, int32 PlayerID);
};
