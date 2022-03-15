// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTNDomain.h"
#include "HTNNetwork.generated.h"

class UBlackboardData;
class UBlackboardComponent;

UCLASS(NotBlueprintable)
class HTNPLUGIN_API UHTNNetwork : public UObject
{
	GENERATED_BODY()

public:

	UHTNNetwork();


	UPROPERTY()
	UBlackboardData* WorldStateAsset;

	UPROPERTY()
	TArray<FName> IgnoredWorldStateValues;

	UPROPERTY()
	int32 MaxPlanCycles;

	virtual bool BuildNetwork(class USHTNComponent* HTNComponent);

protected:

	UFUNCTION()
	virtual bool SetDefaultWorldState(class AAIController* AIOwner, class APawn* Pawn, UBlackboardComponent* WorldState);

	UFUNCTION()
	virtual bool BuildHTNDomain(FSHTNDomain& Domain);

};
