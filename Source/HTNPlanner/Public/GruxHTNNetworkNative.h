// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HTNPlanner/HTNPlanner.h"
#include "HTNNetwork.h"
#include "HTNNetwork_BlueprintBase.h"
#include "GruxHTNNetworkNative.generated.h"

class UBlackBoardData;

/**
 * 
 */
UCLASS()
class HTNPLANNER_API UGruxHTNNetworkNative : public USHTNNetwork_BlueprintBase
{
	GENERATED_BODY()
	
public:

	UGruxHTNNetworkNative();
	

	UFUNCTION()
	virtual bool BuildHTNDomain_Implementation(FSHTNDomain& Domain) override;
	
	TMap<FName, FSHTNCompositeTask> CompositeTasks;
	TMap<FName, FSHTNPrimitiveTask> PrimitiveTasks;
};
