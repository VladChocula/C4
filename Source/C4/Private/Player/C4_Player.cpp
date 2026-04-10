// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C4_Player.h"
#include "Camera/C4_PlayerCameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Grid/C4_GridBase.h"
#include "Grid/GridLogic/C4_GridLogicBase.h"

// Sets default values
AC4_Player::AC4_Player()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UC4_PlayerCameraComponent>(TEXT("PlayerCameraComp"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetAttachments();

}

// Called when the game starts or when spawned
void AC4_Player::BeginPlay()
{
	Super::BeginPlay();

	Grid = Cast<AC4_GridBase>(UGameplayStatics::GetActorOfClass(GetWorld(), AC4_GridBase::StaticClass()));
	PlayPieces.Init(FPlayPiece(), PlayPieceMaxCount);
}

// Called to bind functionality to input
void AC4_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC4_Player::TransitionPieceState(FPlayPiece* PlayPiece, EC4PlayPieceState NewState)
{
	EC4PlayPieceState OldState = PlayPiece->PieceState;
	PlayPiece->PieceState = NewState;
	OnPlayPieceStateChange.Broadcast(*PlayPiece, OldState, PlayPiece->PieceState);

	if (NewState == EC4PlayPieceState::OnCooldown)
	{
		GetWorldTimerManager().SetTimer(
			CooldownTimerHandle, 
			this,
			&AC4_Player::OnPieceCooldownTimerTick, 
			CooldownTimeInterval,
			true);
	}
}

void AC4_Player::SelectColumn(int32 Column)
{
	// If neither the Grid Pointer has not been set in BP, or the GridLogic of the Grid set, return
	if (!Grid || !Grid->GridLogic) return;

	if (Grid->GridLogic->DropPiece(Column, PlayerID, this) > 0)
	{
		// TODO - take the next piece ready to go on cooldown, start its timer,
		// , set its state to OnCooldown.

	}
}

void AC4_Player::OnPieceCooldownTimerTick()
{

}
