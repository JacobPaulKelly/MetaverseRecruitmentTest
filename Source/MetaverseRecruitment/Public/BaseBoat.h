// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "BaseBoat.generated.h"



UCLASS()
class METAVERSERECRUITMENT_API ABaseBoat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBoat();

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

	AController* controller;

	virtual void SetController(AController* Temp);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
