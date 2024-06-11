// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaverseBoatGameMode.h"

#include "CustomPlayerController.h"
#include "MetaversePlayerBoat.h"
#include "MetaverBoatGameState.h"
#include "MetaverseBoatGameHUD.h"


// Constructor to sets default values for this actor's properties.
AMetaverseBoatGameMode::AMetaverseBoatGameMode():AGameMode()
{
	//setting all custom modes for game start.
	PlayerControllerClass = ACustomPlayerController::StaticClass();
	DefaultPawnClass = AMetaversePlayerBoat::StaticClass();
	GameStateClass = AMetaverBoatGameState::StaticClass();
	HUDClass = AMetaverseBoatGameHUD::StaticClass();
	ReplaySpectatorPlayerControllerClass = ACustomPlayerController::StaticClass();
	SpectatorClass = nullptr;
}
