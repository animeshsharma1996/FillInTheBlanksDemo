// Fill out your copyright notice in the Description page of Project Settings.


#include "TextManagerWidget.h"
#include "Engine/Engine.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"
#include "FillTheBlanksProjectile.h"

//Initialise the Text Manager Widget by getting the world object, setting the firstBlankActor and game over to false
//As soon as the class is initialised, it's followed by generating random blanks in the paragraph and storing their information
void UTextManagerWidget::Initialise()
{
	world = GetWorld();
	firstBlankActor = false;
	isGameOver = false;
	if (paragraphTextBlock != nullptr && world != nullptr)
	{
		GenerateBlanksInParagraph();
	}
}

//Generate the blanks in the paragraph according to the specified number of blanks and store their sorted information with the help of 
// Key (index) and value (word) map data structure
void UTextManagerWidget::GenerateBlanksInParagraph()
{
	if (!paragraphTextBlock->GetText().IsEmpty())
	{
		(paragraphTextBlock->GetText().ToString()).ParseIntoArray(paragraphTextArray, TEXT(" "), true);
	}

	int32 lenghtOfTextArray = paragraphTextArray.Num();

	TArray<FString> generatedTextArray;
	int textBoxesIndex = 0;

	//Untill the number of blanks word in the array is not equal to the specified number of blanks
	//add the blank word randomnly to an array only if the array doesn't contain it, then replace the word with blanks
	//This also makes sures the random words are not the same in terms of their index
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
				blankWordsKeyMap.Add(randomBlankNumber,blankWord);
				SpawnTextBox(textBoxesIndex, blankWord);
				paragraphTextArray[randomBlankNumber] = "_____";
				++textBoxesIndex;
			}
		}
	}

	//Generate the new string after generating dashes
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

	newGeneratedString = generatedString;

	paragraphTextBlock->SetText(FText::AsCultureInvariant(generatedString));

}

//Set the text block positons according to the arrow positions
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

//Spawn the Text Block Actors according to the set text block positions (set by the arrows)
void UTextManagerWidget::SpawnTextBox(int textBoxesIndex, FString blankWordRef)
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

//Function to spawn the blank actor at the positions in the world where the blanks are located
//Set the first blank actor on first call
//Add the blank word actors to the Map data structure, once all the actors are added queue them
void UTextManagerWidget::SpawnBlankActor(int blankWordIndex,FString blankWordRef, FVector spawnLocation)
{
	FVector tempLocation = FVector(0.0F, 0.0F, 0.0F);
	FRotator spawnRotation = FQuat::MakeFromEuler(FVector(90.0F, 0.0F, 90.0F)).Rotator();
	ABlankActor* blankActor = world->SpawnActor<ABlankActor>(blankActorClass, spawnLocation, spawnRotation);
	if (!firstBlankActor)
	{
		blankActor->SetCurrentBlank(true);
		firstBlankActor = true;
	}
	blankActor->Initialise(blankWordIndex, blankWordRef);
	blankActorsMap.Add(blankWordIndex, blankActor);

	if (blankActorsMap.Num() == numOfBlanks)
	{
		for (auto pair : blankActorsMap)
		{
			blankActorsQueue.Enqueue(pair.Value);
		}
	}

}

//Original function generating the required dashes according to the number of letters -> for easy play (not added in the current build)
FString UTextManagerWidget::GenerateRequiredDashes(int32 charactersNumbers)
{
	FString generatedString = "";
	for (int32 i = 0; i < charactersNumbers; ++i)
	{
		generatedString.Append("_");
	}
	return generatedString;
}

//Return the new generated string
FString UTextManagerWidget::GetGeneratedString()
{
	FString returnString = "";
	if (!newGeneratedString.IsEmpty())
	{
		returnString = newGeneratedString;
	}
	return returnString;
}

//Set the next blank actor or the objective according to the queue data structure 
//If the tail element or the last element is present make that the current objective or blank
//If not then the game is finished
void UTextManagerWidget::SetNextBlankActor()
{
	ABlankActor* blankActor;
	blankActorsQueue.Dequeue(blankActor);
	ABlankActor* nextBlankActor;
	if (blankActorsQueue.Peek(nextBlankActor))
	{
		nextBlankActor->SetCurrentBlank(true);
	}
	else
	{
		isGameOver = true;
	}
}