// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridLogic/C4_GridLogicBase.h"

// Sets default values for this component's properties
UC4_GridLogicBase::UC4_GridLogicBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UC4_GridLogicBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC4_GridLogicBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

