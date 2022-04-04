// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FillTheBlanksProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AFillTheBlanksProjectile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
		class UTextRenderComponent* textRenderBlock;

	UFUNCTION()
		void Initialise();
	UFUNCTION()
		void SetTextRenderBlocks(FText displayText);
	UFUNCTION()
		FString GetBlankTextString();
	UFUNCTION()
		void ResetTransform();
	UFUNCTION()
		bool GetIsFilled() { return isFilled; }
	UFUNCTION()
		void SetIsFilled(bool value) { isFilled = value; }

	UPROPERTY(BlueprintReadOnly)
		bool isFilled;

	UTextRenderComponent* GetTextRenderBlock() { return ((textRenderBlock != nullptr) ? textRenderBlock : nullptr); }

private :
	UPROPERTY()
		FTransform originalTransform;
};

