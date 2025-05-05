// Copyright Epic Games, Inc. All Rights Reserved.


#include "PTGameMode.h"
#include "PTCharacter.h"
#include "PTPlayerController.h"
#include "PTGameState.h"
#include "Prototype.h"

APTGameMode::APTGameMode()
{
	DefaultPawnClass = APTCharacter::StaticClass();
	PlayerControllerClass = APTPlayerController::StaticClass();
	GameStateClass = APTGameState::StaticClass();
}

void APTGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	PTLOG(Warning, TEXT("%s"), TEXT("Begin"));
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	PTLOG(Warning, TEXT("%s"), TEXT("End"));
}

APlayerController* APTGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	PTLOG(Warning, TEXT("%s"), TEXT("Begin"));
	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	PTLOG(Warning, TEXT("%s"), TEXT("End"));

	return NewPlayerController;
}

void APTGameMode::PostLogin(APlayerController* NewPlayer)
{
	PTLOG(Warning, TEXT("%s"), TEXT("Begin"));
	Super::PostLogin(NewPlayer);
	PTLOG(Warning, TEXT("%s"), TEXT("End"));
}

void APTGameMode::StartPlay()
{
	PTLOG(Warning, TEXT("%s"), TEXT("Begin"));
	Super::StartPlay();
	PTLOG(Warning, TEXT("%s"), TEXT("End"));
}
