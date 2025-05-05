// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogPrototype, Log, All);

#define PTLOG_NETMODEINFO ((GetNetMode() == ENetMode::NM_Client) ? *FString::Printf(TEXT("CLIENT%d"), GPlayInEditorID) \
: ((GetNetMode() == ENetMode::NM_Standalone) ? TEXT("STANDALONE") : TEXT("SERVER")))

#define PTLOG_CALLFUNC ANSI_TO_TCHAR(__FUNCTION__)
#define PTLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define PTLOG_S(Verbosity) UE_LOG(LogPrototype, Verbosity, TEXT("%s"), *PTLOG_CALLINFO)
#define PTLOG(Verbosity, Format, ...) UE_LOG(LogPrototype, Verbosity, TEXT("[%s] %s %s"), PTLOG_NETMODEINFO, PTLOG_CALLFUNC, *FString::Printf(Format, ##__VA_ARGS__))