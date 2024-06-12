// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaverseAIBoat.h"

#include "AISpline.h"
#include "Components/SplineComponent.h"

AMetaverseAIBoat::AMetaverseAIBoat()
{
	PrimaryActorTick.bCanEverTick = true;

	Timer = 0;
}

void AMetaverseAIBoat::BeginPlay()
{
	Super::BeginPlay();

	if (ChosenAISpline)
	{
		Path = ChosenAISpline->GetComponentByClass<USplineComponent>();

		SplineTarget = Path->GetSplineLength();

		//Timer = 1/SplineTarget;

		return;
	}
	
	 GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "No spline found");
}

void AMetaverseAIBoat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ChosenAISpline)
	{
		
		Timer += DeltaTime*LoopTimeLength;

		if (Timer >= SplineTarget)
		{
			Timer =0;
		}


		//BoatMeshComponent->SetWorldLocation(Path->GetLocationAtDistanceAlongSpline(Timer,ESplineCoordinateSpace::World));
		//BoatMeshComponent->SetWorldRotation(Path->GetRotationAtDistanceAlongSpline(Timer,ESplineCoordinateSpace::Local));

		//FVector direction = BoatMeshComponent->GetComponentVelocity();
		
		FVector TempVector = Path->GetLocationAtDistanceAlongSpline(Timer,ESplineCoordinateSpace::World);
		// temporary F Rotator to make life easy when adding 90 degrees to due to orientation of boat mesh.
		FRotator TempRotator = Path->GetRotationAtDistanceAlongSpline(Timer,ESplineCoordinateSpace::World);
		
		BoatMeshComponent->SetRelativeLocation(TempVector);
		BoatMeshComponent->SetWorldRotation(FRotator(TempRotator.Pitch, TempRotator.Yaw+90, TempRotator.Roll));
		//BoatMeshComponent->SetWorldRotation(TempRot);
	}
}

// UE_LOG(LogTemp, Warning, TEXT(""));
// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "spline found");