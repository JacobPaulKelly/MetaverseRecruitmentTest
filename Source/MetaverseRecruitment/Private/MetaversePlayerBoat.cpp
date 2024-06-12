// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "MetaversePlayerBoat.h"

#include "CustomPlayerController.h"

AMetaversePlayerBoat::AMetaversePlayerBoat()
{
    
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Springarm"));
    SpringArmComponent->SetupAttachment(Root);
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    AutoPossessPlayer = EAutoReceiveInput::Player0;
}


// Called when the game starts or when spawned
void AMetaversePlayerBoat::BeginPlay()
{
    Super::BeginPlay();
    
    //Add Input Mapping Context
    if (APlayerController* PlayerController = Cast<ACustomPlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(MappingContext, 0);
        }
    }
    
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(MappingContext, 0);
        }
    }
}

void AMetaversePlayerBoat::Accelerate(const FInputActionValue& Value)
{
	const bool CurrentValue = Value.Get<bool>();

    Root->SetWorldLocation(FVector(0,0,0));


    if (CurrentValue)
    {
        UE_LOG(LogTemp, Warning, TEXT("Accelerating"));
    }
}

void AMetaversePlayerBoat::Steer(const FInputActionValue& Value)
{
    
    UE_LOG(LogTemp, Warning, TEXT("Steering %f"),Value.GetMagnitude());
}

void AMetaversePlayerBoat::BrakeReverse(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Brake"));
}

void AMetaversePlayerBoat::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add yaw and pitch input to controller
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(-LookAxisVector.Y);
    }

    //SpringArmComponent->GetRelativeRotation().Pitch+
}

// Called every frame
void AMetaversePlayerBoat::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

// Called to bind functionality to input
void AMetaversePlayerBoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Triggered, this, &AMetaversePlayerBoat::Accelerate);
        EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Triggered, this, &AMetaversePlayerBoat::Steer);
        EnhancedInputComponent->BindAction(BrakeReverseAction, ETriggerEvent::Triggered, this, &AMetaversePlayerBoat::BrakeReverse);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMetaversePlayerBoat::Look);
    }
}