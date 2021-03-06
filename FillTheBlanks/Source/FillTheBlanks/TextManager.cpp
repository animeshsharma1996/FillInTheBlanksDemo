// Fill out your copyright notice in the Description page of Project Settings.


#include "TextManager.h"
#include "Engine/Engine.h"
#include "Components/TextBlock.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATextManager::ATextManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned -> Gets the TextManagerWidget component and the arrow positions where the text blocks should be spawned
void ATextManager::BeginPlay()
{
	Super::BeginPlay();

	textManagerWidgetComponent = FindComponentByClass<UWidgetComponent>();

	GetComponents(arrowPositions);
}

//Initialise the Text Manager Widget with this function
void ATextManager::InitTextWidget()
{
	if (textManagerWidgetComponent != nullptr)
	{
		textManagerWidget = Cast<UTextManagerWidget>(textManagerWidgetComponent->GetWidget());
		if (textManagerWidget != nullptr)
		{
			textManagerWidget->SetTextBoxPositions(arrowPositions);
			textManagerWidget->Initialise();
		}
	}
}

