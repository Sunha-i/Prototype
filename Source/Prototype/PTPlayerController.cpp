// Fill out your copyright notice in the Description page of Project Settings.


#include "PTPlayerController.h"

void APTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void APTPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(Prototype, Warning, TEXT("%s"), *FString(__FUNCTION__));
}

void APTPlayerController::OnPossess(APawn* aPawn)
{
	UE_LOG(Prototype, Warning, TEXT("%s"), *FString(__FUNCTION__));
	Super::OnPossess(aPawn);
}
