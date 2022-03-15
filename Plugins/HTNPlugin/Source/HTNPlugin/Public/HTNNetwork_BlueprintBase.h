// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTNDomain.h"
#include "HTNNetwork_BlueprintBase.generated.h"

class UBlackboardData;
class UBlackboardComponent;

UCLASS(Blueprintable)
class HTNPLUGIN_API USHTNNetwork_BlueprintBase : public UObject
{
	GENERATED_BODY()

public:

	USHTNNetwork_BlueprintBase();


	UPROPERTY(EditDefaultsOnly, Category = "SHTN")
	UBlackboardData* WorldStateAsset;

	UPROPERTY(EditDefaultsOnly, Category = "SHTN")
	TArray<FName> IgnoredWorldStateValues;

	UPROPERTY(EditDefaultsOnly, Category = "SHTN")
	int32 MaxPlanCycles;

	bool BuildNetwork(class USHTNComponent* HTNComponent);

protected:

	UFUNCTION(BlueprintNativeEvent)
	bool SetDefaultWorldState(class AAIController* AIOwner, class APawn* Pawn, UBlackboardComponent* WorldState);

	UFUNCTION(BlueprintNativeEvent)
	bool BuildHTNDomain(FSHTNDomain& Domain);

};
