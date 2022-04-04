// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "BlankActor.h"
#include "TextManagerWidget.generated.h"

//Text Manager Widget class is responsible for handling the generation of the blank words through the paragraph text written the extended blueprint
//Text Manager Widget is manager by the Text Manager in the hierarchy 
//The class contains the information of the whole paragraph string, the blank words, their indexes and the logic to switch blanks when they have been 
//matches or filled -> Once all blanks have been filled trigger the Game Over boolean
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
		void SpawnTextBox(int textBoxesIndex, FString blankWordRef);
	UFUNCTION(BlueprintCallable)
		void SpawnBlankActor(int blankWordIndex, FString blankWordRef, FVector spawnLocation);
	UFUNCTION(BlueprintCallable)
		void SetTextBoxPositions(TArray<UArrowComponent*> arrowPositions);
	UFUNCTION(BlueprintCallable)
		FString GenerateRequiredDashes(int32 charactersNumbers);
	UFUNCTION(BlueprintCallable)
		FString GetGeneratedString();
	UFUNCTION(BlueprintCallable)
		void SetNextBlankActor();
	UFUNCTION(BlueprintCallable)
		bool GetIsGameOver() { return isGameOver; }

	UPROPERTY(BlueprintReadWrite)
		TMap<int32, ABlankActor*> blankActorsMap;
	UPROPERTY(BlueprintReadWrite)
		TMap<int32, FString> blankWordsKeyMap;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* paragraphTextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DemoData")
		int32 numOfBlanks;
	UPROPERTY(EditDefaultsOnly, Category = "DemoData")
		TSubclassOf<class AFillTheBlanksProjectile> projectileClass;	
	UPROPERTY(EditDefaultsOnly, Category = "DemoData")
		TSubclassOf<class ABlankActor> blankActorClass;

	TQueue<ABlankActor*> blankActorsQueue;

private :
	UPROPERTY()
		FString newGeneratedString;
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
	UPROPERTY()
		bool firstBlankActor;
	UPROPERTY()
		bool isGameOver;
};
