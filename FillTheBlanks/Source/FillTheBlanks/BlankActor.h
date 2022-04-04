// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "BlankActor.generated.h"

UCLASS()
class FILLTHEBLANKS_API ABlankActor : public AActor
{
	GENERATED_BODY()
	
public:	
	virtual void BeginPlay();

	UFUNCTION()
		void Initialise(int32 blankIndex, FString blankString);
	UFUNCTION()
		FString GetBlankWordString() { return blankWordString; }
	UFUNCTION(BlueprintCallable)
		int32 GetBlankIndex() { return blankWordIndex; }
	UFUNCTION(BlueprintCallable)
		void TriggerHighlight();
	UFUNCTION(BlueprintCallable)
		void ResetMaterial();
	UFUNCTION(BlueprintCallable)
		void SetCurrentBlank(bool value);
	UFUNCTION(BlueprintCallable)
		bool GetCurrentBlank() { return isCurrentBlank; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		UMaterial* highlightedMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
		UMaterial* defaultMaterial;

protected:
	UPROPERTY()
		int32 blankWordIndex;
	UPROPERTY()
		FString blankWordString;
	UPROPERTY()
		TArray<UStaticMeshComponent*> staticMeshes;
	UPROPERTY()
		bool isHighlighted;
	UPROPERTY()
		bool isCurrentBlank;
	UPROPERTY()
		class UArrowComponent* ownArrow;
};
