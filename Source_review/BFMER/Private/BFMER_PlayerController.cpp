// Fill out your copyright notice in the Description page of Project Settings.

#include "BFMER_PlayerController.h"

#include "Containers/Array.h"
#include "Engine/AssetManager.h"
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


bool ABFMER_PlayerController::AddToSelection(AUnit *unit)
{
    if (std::find(m_SelectedUnits.begin(), m_SelectedUnits.end(), unit) != m_SelectedUnits.end())
        return false;

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
    
    return true;
}


void ABFMER_PlayerController::SelectSame()
{
    static const float offscreen_min_time = 0.2;

    std::vector<FPrimaryAssetId> selected_asset;

    for (auto const* selected_unit : m_SelectedNonHero) {
        auto const primary_asset = selected_unit->GetPrimaryAssetId();

        if (std::find(selected_asset.begin(), selected_asset.end(), primary_asset) == selected_asset.end())
        {
            selected_asset.push_back(primary_asset);
        }
    }

    TArray<AActor *> found_actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), found_actors);

    std::vector<AUnit *> offscreen_units;
    bool select_offscreen_units{true};
    for (auto *actor : found_actors) 
    {
        auto *found_unit = reinterpret_cast<AUnit *>(actor);
        if (found_unit)
        {
            bool unit_similar_to_selected = false;
            for (auto primary_asset_id : selected_asset)
            {
                if (found_unit->GetPrimaryAssetId() == primary_asset_id)
                {
                    unit_similar_to_selected = true;
                    break;
                }
            }

            if (unit_similar_to_selected)
            {
                if (found_unit->WasRecentlyRendered(offscreen_min_time))
                {
                    if (AddToSelection(found_unit))
                        select_offscreen_units = false;
                }
                else
                {
                    offscreen_units.push_back(found_unit);
                }
            }
        }
    }

    if (select_offscreen_units)
    {
        for (auto *unit : offscreen_units)
        {
            AddToSelection(unit);
        }
    }
}


void ABFMER_PlayerController::SelectAll()
{
    auto &asset_manager = UAssetManager::Get();
    TArray<AActor *> found_actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit::StaticClass(), found_actors);

    for (auto *actor : found_actors)
    {
        auto *found_unit = reinterpret_cast<AUnit *>(actor);
        if (found_unit) 
        {
            auto const asset_id = found_unit->GetPrimaryAssetId();
            if (asset_id.PrimaryAssetType != TEXT("NonMilitary"))
                AddToSelection(found_unit);
        }
    }
}


void ABFMER_PlayerController::LogSelected() const
{
    for (auto const *selected_unit : m_SelectedUnits) 
    {
        auto const *selected_actor = static_cast<AActor const*>(selected_unit);
        auto const actor_name = selected_actor->GetName();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, actor_name);
    }
    
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Selected units :"));
}