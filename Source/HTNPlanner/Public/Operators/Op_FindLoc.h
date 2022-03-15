// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HTNPlanner/HTNPlanner.h"
// #include "HTNOperator.h"
#include "HTNOperator_BlueprintBase.h"
#include "Op_FindLoc.generated.h"

class AAIC_GruxTest;
/**
 * 
 */
UCLASS()
class HTNPLANNER_API UOp_FindLoc : public USHTNOperator_BlueprintBase
{
	GENERATED_BODY()
	
public:

	
	virtual bool CheckConditions_Implementation(USHTNBlackboardGetWrapper* WorldState, const uint8 OperatorParam, const bool bIsPlanning) override;
	
	virtual void ReceiveInitializeAction_Implementation(AAIController* OwnerController, const uint8 OperatorParam) override;
	
	virtual void ReceiveExecuteAction_Implementation(AAIController* OwnerController, const uint8 OperatorParam,
		const float DeltaTime) override;
	
	virtual void ApplyEffects_Implementation(UBlackboardComponent* WorldState, const uint8 OperatorParam,
		const bool IsPlanning) override;

	

private:
	UPROPERTY()
	AAIC_GruxTest* AIController;

	FVector FoundLocation;
};
