// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "MetaverseBaseBoat.generated.h"

UCLASS()
class METAVERSERECRUITMENT_API AMetaverseBaseBoat : public APawn
{
	GENERATED_BODY()

public:
	// Constructor to sets default values for this actor's properties.
	AMetaverseBaseBoat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 
	
	UPROPERTY(EditAnywhere, meta=(ClampMin = 0))
	float Mass;
	
	
	FVector Position;
	FVector Velocity;
	FVector Acceleration;
	float MaxForce;
	float MaxSpeed;

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BoatMeshComponent;

	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	UPROPERTY()
	UCameraComponent* CameraComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
