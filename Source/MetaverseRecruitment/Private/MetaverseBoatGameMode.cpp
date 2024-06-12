// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaverseBoatGameMode.h"
#include "CustomPlayerController.h"
#include "MetaversePlayerBoat.h"
#include "MetaverseBoatGameState.h"
#include "MetaverseBoatGameHUD.h"


// Constructor to sets default values for this actor's properties.
AMetaverseBoatGameMode::AMetaverseBoatGameMode():AGameMode()
{
	//setting all custom modes for game start.
	PlayerControllerClass = ACustomPlayerController::StaticClass();
	DefaultPawnClass = AMetaversePlayerBoat::StaticClass();
	GameStateClass = AMetaverseBoatGameState::StaticClass();
	HUDClass = AMetaverseBoatGameHUD::StaticClass();
	ReplaySpectatorPlayerControllerClass = ACustomPlayerController::StaticClass();
	SpectatorClass = nullptr;
}
