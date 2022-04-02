// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlankActor.generated.h"

UCLASS()
class FILLTHEBLANKS_API ABlankActor : public AActor
{
	GENERATED_BODY()
	
public:	
	UFUNCTION()
		void Initialise(int32 blankIndex, FString blankString);
	UFUNCTION()
		FString GetBlankWordString() { return blankWordString; }
	UFUNCTION(BlueprintCallable)
		void TriggerHighlight();


protected:
	UPROPERTY()
		int32 blankWordIndex;
	UPROPERTY()
		FString blankWordString;
};
