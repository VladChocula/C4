// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C4_GridBase.generated.h"

class UC4_GridLogicBase;

UCLASS()
class C4_API AC4_GridBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC4_GridBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Grid")
	UC4_GridLogicBase* GridLogic;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
