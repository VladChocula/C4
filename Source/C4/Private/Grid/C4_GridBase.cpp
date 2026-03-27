// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/C4_GridBase.h"

// Sets default values
AC4_GridBase::AC4_GridBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GridLogic = CreateDefaultSubobject<UC4_GridLogicBase>(TEXT("GridLogic"));

}

// Called when the game starts or when spawned
void AC4_GridBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC4_GridBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

