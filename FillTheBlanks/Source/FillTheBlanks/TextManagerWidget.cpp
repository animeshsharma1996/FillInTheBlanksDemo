// Fill out your copyright notice in the Description page of Project Settings.


#include "TextManagerWidget.h"
#include "Engine/Engine.h"
#include "Components/TextBlock.h"

void UTextManagerWidget::Initialise()
{
	if (paragraphTextBlock != nullptr)
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

	while (blanksIndexArray.Num() != numOfBlanks)
	{
		int32 randomBlankNumber = FMath::RandRange(0, lenghtOfTextArray);
		if (!blanksIndexArray.Contains(randomBlankNumber))
		{
			blanksIndexArray.Add(randomBlankNumber);
		}
	}

	TArray<FString> generatedTextArray;
	for(auto blankPosition : blanksIndexArray)
	{
		if (blankPosition < lenghtOfTextArray)
		{
			blanksTextArray.Add(paragraphTextArray[blankPosition]);
			paragraphTextArray[blankPosition] = "_____";
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

void UTextManagerWidget::PublicTick(float DeltaTime)
{

}
