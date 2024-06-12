// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaverseBaseBoat.h"
#include "MetaverseAIBoat.generated.h"

class AAISpline;
class USplineComponent;
/**
 * 
 */
UCLASS()
class METAVERSERECRUITMENT_API AMetaverseAIBoat : public AMetaverseBaseBoat
{
	GENERATED_BODY()
public:
	AMetaverseAIBoat();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AAISpline* ChosenAISpline;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0))
	float LoopTimeLength;
	
	float SplineTarget;

	float Timer;

	UPROPERTY()
	USplineComponent* Path;
};
