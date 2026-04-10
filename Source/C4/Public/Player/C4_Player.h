// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C4_Player.generated.h"

class UC4_PlayerCameraComponent;
class AC4_GridBase;

UENUM(BlueprintType)
enum class EC4PlayPieceState : uint8
{
	Ready, 
	OnCooldown,
	Dropping,
	Dropped
};

USTRUCT(BlueprintType)
struct FPlayPiece
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	EC4PlayPieceState PieceState = EC4PlayPieceState::Ready;

	UPROPERTY(BlueprintReadOnly)
	float CooldownTimeRemainig = 0.f;

	FTimerHandle CooldownTimerHandle;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayPieceCooldownTimerTick, FPlayPiece&, PlayPiece);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPlayPieceStateChange, FPlayPiece&, PlayPiece, EC4PlayPieceState, OldState, EC4PlayPieceState, NewState);

UCLASS()
class C4_API AC4_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC4_Player();

	//Getter/Setter for PlayerID
	void SetPlayerID(int32 NewPlayerID) { PlayerID = NewPlayerID; }
	int32 GetPlayerID() const { return PlayerID;}

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SelectColumn(int32 Column);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Player")
	int32 PlayPieceMaxCount = 3;

	UPROPERTY(BlueprintReadOnly, Category="Player")
	TArray<FPlayPiece> PlayPieces;

	UPROPERTY(BlueprintAssignable, Category="Player")
	FOnPlayPieceCooldownTimerTick OnPlayPieceCooldownTimerTick;

	UPROPERTY(BlueprintAssignable, Category="Player")
	FOnPlayPieceStateChange OnPlayPieceStateChange;

	UFUNCTION()
	void OnPieceCooldownTimerTick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UC4_PlayerCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, Category="Grid")
	AC4_GridBase* Grid;

	void TransitionPieceState(FPlayPiece* PlayPiece, EC4PlayPieceState NewState);

private:

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"), Category="Player")
	int32 PlayerID = 0;

	FTimerHandle CooldownTimerHandle;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"), Category="Player")
	float CooldownTime = 6.f;

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess="true"), Category = "Player")
	float CooldownTimeInterval = .45f;
};
