// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpline.h"
#include "Components/SplineComponent.h"

// Sets default values
AAISpline::AAISpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	AISpline = CreateDefaultSubobject<USplineComponent>(TEXT("AI Spline Path"));
	AISpline->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AAISpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAISpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

