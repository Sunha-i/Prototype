// Copyright Epic Games, Inc. All Rights Reserved.


#include "PTGameMode.h"
#include "PTCharacter.h"
#include "PTPlayerController.h"

APTGameMode::APTGameMode()
{
	DefaultPawnClass = APTCharacter::StaticClass();
	PlayerControllerClass = APTPlayerController::StaticClass();
}

void APTGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("PostLogin End"));
}
