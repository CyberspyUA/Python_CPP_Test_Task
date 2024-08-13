// Copyright Epic Games, Inc. All Rights Reserved.

#include "CppDeveloperTestTaskGameMode.h"
#include "CppDeveloperTestTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACppDeveloperTestTaskGameMode::ACppDeveloperTestTaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
