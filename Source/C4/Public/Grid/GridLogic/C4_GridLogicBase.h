// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C4_GridLogicBase.generated.h"

class AC4_Player;

UENUM(BlueprintType)
enum class EC4BoardState : uint8
{
	Inactive,
	Active,
	Shifting,
	Paused
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerScored, AC4_Player*, ScoringPlayer, float, ScoreValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBoardStateChanged, EC4BoardState, PreviousState, EC4BoardState, NewState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C4_API UC4_GridLogicBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC4_GridLogicBase();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerScored OnPlayerScored;

	UPROPERTY(BlueprintAssignable)
	FOnBoardStateChanged OnBoardStateChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 NumRows = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid")
	int32 NumColumns = 7;

	UFUNCTION(BlueprintCallable)
	int32 DropPiece(int32 Column, int32 PlayerID, AC4_Player* ScoringPlayer);

	UFUNCTION(BlueprintCallable)
	bool IsColumnFull(int32 Column) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TransitionBoardState(EC4BoardState NewState);

private:

	TArray<int32> Grid;
	
	int32 GetIndex(int32 Row, int32 Col) const;

	bool CheckWin(int32 Row, int32 Col, int32 PlayerID);

	UPROPERTY(BLueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Grid")
	EC4BoardState BoardState = EC4BoardState::Inactive;

	// Sequence scanning
	TArray<TArray<int32>> FindAllSequences(int32 PlayerID);
	int32 ScoreSequence(const TArray<int32>& SequenceIndices);

	// Chain resolution
	void RemoveSequences(const TArray<TArray<int32>>& AllSequences);
	void ShiftPiecesDown();
};
