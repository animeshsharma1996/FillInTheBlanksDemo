// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Components/ArrowComponent.h"
#include "TextManagerWidget.h"
#include "TextManager.generated.h"

//Text Manager is the Actor class that exists in the level to act as a bridge between TextManagerWidget and the world level
//The blueprint extension is also used to spawn, display the 3D Text along with the Blank Actor
UCLASS()
class FILLTHEBLANKS_API ATextManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATextManager();

UFUNCTION(BlueprintCallable)
	void InitTextWidget();

UPROPERTY()
	class UWidgetComponent* textManagerWidgetComponent;
UPROPERTY()
	TArray<UArrowComponent*> arrowPositions;
UPROPERTY()
	class UTextManagerWidget* textManagerWidget;

protected:
	virtual void BeginPlay() override;


};
