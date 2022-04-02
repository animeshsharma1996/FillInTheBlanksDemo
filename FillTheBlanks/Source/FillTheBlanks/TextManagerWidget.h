// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
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
	UFUNCTION(BlueprintCallable)
		void SpawnTextBoxes(int textBoxesIndex, FString blankWordRef);
	UFUNCTION(BlueprintCallable)
		void SetTextBoxPositions(TArray<UArrowComponent*> arrowPositions);
	UFUNCTION()
		void PublicTick(float DeltaTime);

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* paragraphTextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DemoData")
		int32 numOfBlanks;
	UPROPERTY(EditDefaultsOnly, Category = "DemoData")
		TSubclassOf<class AFillTheBlanksProjectile> projectileClass;

private :
	UPROPERTY()
		TArray<FString> paragraphTextArray;
	UPROPERTY()
		TArray<FString> blanksTextArray;
	UPROPERTY()
		TArray<int32> blanksIndexArray;
	UPROPERTY()
		TArray<FTransform> textBoxesTransforms;
	UPROPERTY()
		UWorld* world;
};
