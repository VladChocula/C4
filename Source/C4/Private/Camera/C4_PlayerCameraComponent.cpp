// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/C4_PlayerCameraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UC4_PlayerCameraComponent::UC4_PlayerCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
}


// Called when the game starts
void UC4_PlayerCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UC4_PlayerCameraComponent::PlayScoringFeedback()
{
	// TODO: Implement scoring feedback...
}

void UC4_PlayerCameraComponent::SetAttachments()
{
	SpringArm->SetupAttachment(this);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

