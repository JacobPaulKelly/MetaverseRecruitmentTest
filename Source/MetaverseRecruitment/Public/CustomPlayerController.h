// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class METAVERSERECRUITMENT_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Constructor to sets default values for this actor's properties.
	ACustomPlayerController();
};