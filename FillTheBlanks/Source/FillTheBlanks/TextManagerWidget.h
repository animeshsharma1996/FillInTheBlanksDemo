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
	UFUNCTION(BlueprintCallable)
		void Initialise();
	UFUNCTION(BlueprintCallable)
		void GenerateBlanksInParagraph();
	UFUNCTION()
		void PublicTick(float DeltaTime);

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* paragraphTextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DemoData")
		int32 numOfBlanks;

private :
	UPROPERTY()
		TArray<FString> paragraphTextArray;
	UPROPERTY()
		TArray<FString> blanksTextArray;
	UPROPERTY()
		TArray<int32> blanksIndexArray;
};
