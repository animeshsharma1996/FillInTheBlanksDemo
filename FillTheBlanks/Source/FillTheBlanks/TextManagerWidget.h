// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextManagerWidget.generated.h"

/**
 * 
 */
UCLASS()
class FILLTHEBLANKS_API UTextManagerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	UFUNCTION()
		void Initialise();
	UFUNCTION()
		void PublicTick(float DeltaTime);

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* paragraphTextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DemoData")
		int32 numOfBlanks;

};
