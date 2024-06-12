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

	//Control Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* MappingContext;

	//Control Inputs and function
	void Accelerate(const FInputActionValue& Value);
	void StoppedAccelerate(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* AccelerateAction;
	
	void Steer(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* SteerAction;
	
	void BrakeReverse(const FInputActionValue& Value);
	void StoppedBrakeReverse(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* BrakeReverseAction;
	
	void Look(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* LookAction;

	void Pause(const FInputActionValue& Value);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* PauseAction;
	
	float CalculateSteeringStrength();
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	// TSubclassOf<UUserWidget> WidgetTemplate;
	//
	// UPROPERTY()
	// UUserWidget* WidgetInstance;

private:
	float AccelerationRate;

	bool IsAdjustingAcceleration;

	bool IsReverseing;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
