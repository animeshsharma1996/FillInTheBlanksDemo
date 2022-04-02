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

// Called when the game starts or when spawned
void ATextManager::BeginPlay()
{
	Super::BeginPlay();

	textManagerWidgetComponent = FindComponentByClass<UWidgetComponent>();

	GetComponents(arrowPositions);

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

// Called every frame
void ATextManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (textManagerWidget != nullptr)
	{
		//textManagerWidget->PublicTick(DeltaTime);
	}
}

