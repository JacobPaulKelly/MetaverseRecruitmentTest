// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "MetaversePlayerBoat.h"

#include "CustomPlayerController.h"
//#include "Blueprint/UserWidget.h"

AMetaversePlayerBoat::AMetaversePlayerBoat()
{
    //creating camera and spring arm, any changes to these are to be done in blueprints.
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Springarm"));
    SpringArmComponent->SetupAttachment(Root);
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);

    AutoPossessPlayer = EAutoReceiveInput::Player0;

    AccelerationRate = 0;

    IsAdjustingAcceleration = false;
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
    IsAdjustingAcceleration = true;
    
    if (AccelerationRate < 0)
    {
        AccelerationRate = 0;
    }

    if (AccelerationRate > 1)
    {
        AccelerationRate = 1;
    }
    
    AccelerationRate += Value.GetMagnitude()*GetWorld()->DeltaTimeSeconds;
}

void AMetaversePlayerBoat::StoppedAccelerate(const FInputActionValue& Value)
{
    IsAdjustingAcceleration = false;
}

void AMetaversePlayerBoat::Steer(const FInputActionValue& Value)
{
    Root->SetRelativeRotation(FRotator(0, Root->GetRelativeRotation().Yaw + Value.GetMagnitude()*GetWorld()->DeltaTimeSeconds*CalculateSteeringStrength(), 0));
}

void AMetaversePlayerBoat::BrakeReverse(const FInputActionValue& Value)
{
    IsAdjustingAcceleration = true;
    
    if (AccelerationRate > 0)
    {
        AccelerationRate = 0;
    }

    if (AccelerationRate < -1)
    {
        AccelerationRate = -1;
    }

    //Getting input and then smoothing it with delta time.
    AccelerationRate -= Value.GetMagnitude()*GetWorld()->DeltaTimeSeconds;
}

void AMetaversePlayerBoat::StoppedBrakeReverse(const FInputActionValue& Value)
{
    IsAdjustingAcceleration = false;
}

float AMetaversePlayerBoat::CalculateSteeringStrength()
{
    //below causes turn speed to slow down as the boat gets faster and slower but keeps its standard during mid speeds
    if (AccelerationRate > 0.5)
    {
        return (1-(AccelerationRate/1.5))*100;
    }
    else if (AccelerationRate < 0.5 && AccelerationRate > -0.5)
    {
       return AccelerationRate*100;
    }
    
    return (-1-(AccelerationRate/1.5))*100;
}

void AMetaversePlayerBoat::Look(const FInputActionValue& Value)
{
    // input is directly from the mouse
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // add yaw and pitch input to controller for camera rotation
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(-LookAxisVector.Y);
    }
}

void AMetaversePlayerBoat::Pause(const FInputActionValue& Value)
{
    //Attempting to spawn Widgets in blueprints
    // WidgetInstance = CreateWidget(this, WidgetTemplate);
    //
    // WidgetInstance->AddToViewport();
    //CreateWidget(this,);

    UE_LOG(LogTemp, Warning, TEXT("Paused"));

    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Paused");
}

// Called every frame
void AMetaversePlayerBoat::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Stopping boat from going too fast
    if (BoatMeshComponent->GetComponentVelocity().Length()<20000 && IsAdjustingAcceleration)
    {
        BoatMeshComponent->AddForce(((Root->GetForwardVector()*100000000000)*GetWorld()->DeltaTimeSeconds)*AccelerationRate);
    }
    else
    {
        BoatMeshComponent->AddForce(-BoatMeshComponent->GetComponentVelocity().GetSafeNormal2D()*100000000000*GetWorld()->DeltaTimeSeconds);
    }

    //ensuring that all components are facing the correct way and in the right place
    SetActorLocation(BoatMeshComponent->GetComponentLocation());
    BoatMeshComponent->SetRelativeRotation(FRotator(0, Root->GetRelativeRotation().Yaw - 90, 0));

    // Reduces AccelerationRate only when acceleration is not being touched and is not 0
    if (AccelerationRate != 0 && !IsAdjustingAcceleration)
    {
        AccelerationRate -= AccelerationRate*(GetWorld()->DeltaTimeSeconds);
    }
}

// Called to bind functionality to input
void AMetaversePlayerBoat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Creating function binds from the enhanced input actions.
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Completed, this, &AMetaversePlayerBoat::StoppedAccelerate);
        EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Triggered, this, &AMetaversePlayerBoat::Accelerate);
        EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Triggered, this, &AMetaversePlayerBoat::Steer);
        EnhancedInputComponent->BindAction(BrakeReverseAction, ETriggerEvent::Completed, this, &AMetaversePlayerBoat::StoppedBrakeReverse);
        EnhancedInputComponent->BindAction(BrakeReverseAction, ETriggerEvent::Triggered, this, &AMetaversePlayerBoat::BrakeReverse);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMetaversePlayerBoat::Look);
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AMetaversePlayerBoat::Pause);
    }
}