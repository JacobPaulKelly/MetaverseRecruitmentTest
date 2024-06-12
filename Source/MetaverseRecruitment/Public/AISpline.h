// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AISpline.generated.h"

class USplineComponent;

UCLASS()
class METAVERSERECRUITMENT_API AAISpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* AISpline;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
