// Fill out your copyright notice in the Description page of Project Settings.


#include "TextManagerWidget.h"
#include "Engine/Engine.h"
#include "Components/TextBlock.h"
#include "FillTheBlanksProjectile.h"

void UTextManagerWidget::Initialise()
{
	world = GetWorld();
	if (paragraphTextBlock != nullptr && world != nullptr)
	{
		GenerateBlanksInParagraph();
	}
}

void UTextManagerWidget::GenerateBlanksInParagraph()
{
	if (!paragraphTextBlock->GetText().IsEmpty())
	{
		(paragraphTextBlock->GetText().ToString()).ParseIntoArray(paragraphTextArray, TEXT(" "), true);
	}

	int32 lenghtOfTextArray = paragraphTextArray.Num();

	TArray<FString> generatedTextArray;
	int textBoxesIndex = 0;
	while (blanksIndexArray.Num() != numOfBlanks)
	{
		int32 randomBlankNumber = FMath::RandRange(0, lenghtOfTextArray);
		if (!blanksIndexArray.Contains(randomBlankNumber))
		{
			blanksIndexArray.Add(randomBlankNumber);
			if (randomBlankNumber < lenghtOfTextArray)
			{
				FString blankWord = paragraphTextArray[randomBlankNumber];
				blanksTextArray.Add(blankWord);
				SpawnTextBoxes(textBoxesIndex, blankWord);
				paragraphTextArray[randomBlankNumber] = "_____";
				++textBoxesIndex;
			}
		}
	}

	FString generatedString;
	for(int32 i = 0; i < lenghtOfTextArray; ++i)
	{
		generatedString.Append(paragraphTextArray[i]);
		
		if ((i + 1 < lenghtOfTextArray))
		{
			FString nextElem = paragraphTextArray[i + 1];
			bool punctuationCheck = (nextElem == "." || nextElem == "!" || nextElem == "?" || nextElem == ",");
			if (!punctuationCheck)
			{
				generatedString.Append(" ");
			}
		}
	}
	paragraphTextBlock->SetText(FText::AsCultureInvariant(generatedString));
}

void UTextManagerWidget::SpawnTextBoxes(int textBoxesIndex, FString blankWordRef)
{
	if (textBoxesTransforms.Num() != 0)
	{
		FVector spawnLocation = textBoxesTransforms[textBoxesIndex].GetLocation();
		FRotator spawnRotation = textBoxesTransforms[textBoxesIndex].GetRotation().Rotator();
		AFillTheBlanksProjectile* spawnActor = world->SpawnActor<AFillTheBlanksProjectile>(projectileClass, spawnLocation, spawnRotation);
		spawnActor->Initialise();
		spawnActor->SetTextRenderBlocks(FText::AsCultureInvariant(blankWordRef));
	}
}

void UTextManagerWidget::SetTextBoxPositions(TArray<UArrowComponent*> arrowPositions)
{
	if (arrowPositions.Num() != 0)
	{
		for (auto arrowPosition : arrowPositions)
		{
			textBoxesTransforms.Add(arrowPosition->GetComponentTransform());
		}
	}
}

void UTextManagerWidget::PublicTick(float DeltaTime)
{

}
