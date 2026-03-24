// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C4.h"
#include "C4_Grid.generated.h"

UCLASS()
class C4_API AC4_Grid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC4_Grid();

	static const int32 ROWS = BASE_GM_ROW_MAX;
	static const int32 COLS = BASE_GM_COL_MAX;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<int32> Grid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int32 GetINdex(int32 Row, int32 Col) const;

};
