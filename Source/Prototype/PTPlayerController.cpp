// Fill out your copyright notice in the Description page of Project Settings.


#include "PTPlayerController.h"
#include "Prototype.h"

void APTPlayerController::BeginPlay()
{
	PTLOG(Warning, TEXT("%s"), TEXT("Begin"));
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	PTLOG(Warning, TEXT("%s"), TEXT("Begin"));
}

void APTPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PTLOG_S(Log);
}

void APTPlayerController::OnPossess(APawn* aPawn)
{
	PTLOG_S(Log);
	Super::OnPossess(aPawn);
}
