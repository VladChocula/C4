// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "C4_PlayerCameraComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C4_API UC4_PlayerCameraComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC4_PlayerCameraComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* Camera;

	UFUNCTION(BlueprintCallable, Category="Camera")
	void PlayScoringFeedback();

	UFUNCTION(BlueprintCallable, Category="Camera")
	void SetAttachments();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
