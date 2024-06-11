// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBoat.h"
#include "CustomAIController.h"
#include "AIBoat.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSERECRUITMENT_API AAIBoat : public ABaseBoat
{
	GENERATED_BODY()

public:
	AAIBoat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetController(AController* Temp) override;
	ACustomAIController* AiCon;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
