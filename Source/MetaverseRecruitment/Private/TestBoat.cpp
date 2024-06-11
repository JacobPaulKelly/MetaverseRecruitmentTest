// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBoat.h"

ATestBoat::ATestBoat()
{

}

void ATestBoat::SetController(AController* Temp)
{
	controller = Temp;
}

// Called when the game starts or when spawned
void ATestBoat::BeginPlay()
{
	Super::BeginPlay();

	SetController(Cast<AController>(AiCon));
}

// Called every frame
void ATestBoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}