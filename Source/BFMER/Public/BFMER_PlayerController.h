// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BFMER_PlayerController.generated.h"


class AUnit;
class AHero;

/**
 * 
 */
UCLASS(Blueprintable)
class BFMER_API ABFMER_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Unit Selection")
	void ClearSelection();

	UFUNCTION(BlueprintCallable, Category="Unit Selection")
	void SelectHero();

	UFUNCTION(BlueprintCallable, Category="Unit Selection")
	bool AddToSelection(AUnit *unit);

	UFUNCTION(BlueprintCallable, Category="Unit Selection")
	void SelectSame();

	UFUNCTION(BlueprintCallable, Category="Unit Selection")
	void SelectAll();

	UFUNCTION(BlueprintCallable, Category="Unit Selection")
	void LogSelected() const;

protected:
	
private:
	std::vector<AUnit *> m_SelectedUnits;
	std::vector<AHero *> m_SelectedHero;
	std::vector<AUnit *> m_SelectedNonHero;

	
};
