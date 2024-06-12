// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaverseBaseBoat.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "MetaversePlayerBoat.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class METAVERSERECRUITMENT_API AMetaversePlayerBoat : public AMetaverseBaseBoat
{
	GENERATED_BODY()
public:
	AMetaversePlayerBoat();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AccelerateAction;
	
	void Accelerate(const FInputActionValue& Value);
	void Steer(const FInputActionValue& Value);
	void BrakeReverse(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;


public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
