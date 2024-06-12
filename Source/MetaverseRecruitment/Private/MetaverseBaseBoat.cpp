// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaverseBaseBoat.h"

// Constructor to sets default values for this actor's properties.
AMetaverseBaseBoat::AMetaverseBaseBoat()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
void AMetaverseBaseBoat::BeginPlay()
{
	Super::BeginPlay();

	Root->SetWorldLocation(FVector(Root->GetComponentLocation().X,Root->GetComponentLocation().Y, 100));
}

// Called every frame
void AMetaverseBaseBoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BoatMeshComponent->GetComponentLocation().Z < 0)
	{
		BoatMeshComponent->AddForce(FVector(0,0,185000000000)*GetWorld()->DeltaTimeSeconds);
	}
}

// Called to bind functionality to input
void AMetaverseBaseBoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

