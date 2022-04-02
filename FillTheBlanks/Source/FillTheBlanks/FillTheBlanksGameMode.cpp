// Copyright Epic Games, Inc. All Rights Reserved.

#include "FillTheBlanksGameMode.h"
#include "FillTheBlanksHUD.h"
#include "FillTheBlanksCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFillTheBlanksGameMode::AFillTheBlanksGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/FirstPerson/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFillTheBlanksHUD::StaticClass();
}
