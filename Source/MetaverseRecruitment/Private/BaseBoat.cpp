// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBoat.h"

// Sets default values
ABaseBoat::ABaseBoat()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = 0;
	Position = { 0, 0, 0 };
	Velocity = { 0, 0, 0 };
	Acceleration = {0, 0, 0 };
	MaxForce = 0;
	MaxSpeed = 0;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BoatMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Boat Mesh"));
	BoatMeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ABaseBoat::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseBoat::SetController(AController* Temp)
{
}

// Called every frame
void ABaseBoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

