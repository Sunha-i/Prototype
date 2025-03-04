// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Prototype, Log, All);

#define PTLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define PTLOG_S(Verbosity) UE_LOG(Prototype, Verbosity, TEXT("%s"), *PTLOG_CALLINFO)
#define PTLOG(Verbosity, Format, ...) UE_LOG(Prototype, Verbosity, TEXT("%s %s"), *PTLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))