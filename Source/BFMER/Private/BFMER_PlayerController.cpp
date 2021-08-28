// Fill out your copyright notice in the Description page of Project Settings.

#include "BFMER_PlayerController.h"

#include "Containers/Array.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h" 

#include "Unit.h"
#include "Hero.h"


void ABFMER_PlayerController::ClearSelection() 
{
    m_SelectedUnits.clear();

    m_SelectedHero.clear();
    m_SelectedNonHero.clear();
}


void ABFMER_PlayerController::SelectHero() 
{
    TArray<AActor *> found_actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHero::StaticClass(), found_actors);

    for (auto *actor : found_actors)
    {
        auto *found_hero = reinterpret_cast<AHero *>(actor);
        if (found_hero) 
            AddToSelection(static_cast<AUnit *>(found_hero));
    }
}


void ABFMER_PlayerController::AddToSelection(AUnit *unit)
{
    if (std::find(m_SelectedUnits.begin(), m_SelectedUnits.end(), unit) != m_SelectedUnits.end())
        return;

    auto *selected_hero = dynamic_cast<AHero *>(unit);
    
    if (selected_hero) 
    {
        m_SelectedHero.push_back(selected_hero);
    }
    else 
    {
        m_SelectedNonHero.push_back(unit);
    }

    m_SelectedUnits.push_back(unit);
}


void ABFMER_PlayerController::SelectSame()
{

}


void ABFMER_PlayerController::SelectAll()
{
    TArray<AActor *> found_actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), found_actors);

    for (auto *actor : found_actors)
    {
        auto *found_unit = reinterpret_cast<AUnit *>(actor);
        if (found_unit) 
        {
            AddToSelection(found_unit);
        }
    }
}


void ABFMER_PlayerController::LogSelected() const
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Selected units :"));

    for (auto const *selected_unit : m_SelectedUnits) 
    {
        auto const *selected_actor = static_cast<AActor const*>(selected_unit);
        auto const actor_name = selected_actor->GetName();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, actor_name);
    }
}