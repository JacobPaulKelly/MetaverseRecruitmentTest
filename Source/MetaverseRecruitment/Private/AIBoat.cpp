// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBoat.h"

AAIBoat::AAIBoat()
{

}

void AAIBoat::SetController(AController* Temp)
{
	controller = Temp;
}

// Called when the game starts or when spawned
void AAIBoat::BeginPlay()
{
	Super::BeginPlay();

	SetController(Cast<AController>(AiCon));
}

// Called every frame
void AAIBoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}