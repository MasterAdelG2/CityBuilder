// Copyright Epic Games, Inc. All Rights Reserved.

#include "LimbicTestGameMode.h"
#include "LimbicTestPlayerController.h"

ALimbicTestGameMode::ALimbicTestGameMode()
{
	// no pawn by default
	DefaultPawnClass = nullptr;
	// use our own player controller class
	PlayerControllerClass = ALimbicTestPlayerController::StaticClass();
}
