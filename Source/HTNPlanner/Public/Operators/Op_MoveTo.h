// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HTNPlanner/HTNPlanner.h"
// #include "HTNOperator.h"
#include "HTNOperator_BlueprintBase.h"
#include "Tasks/AITask_MoveTo.h"
#include "Op_MoveTo.generated.h"

/**
 * 
 */
UCLASS()
class HTNPLANNER_API UOp_MoveTo : public USHTNOperator_BlueprintBase
{
	GENERATED_BODY()

public:

	virtual void ReceiveExecuteAction_Implementation(AAIController* OwnerController, const uint8 OperatorParam,
	const float DeltaTime) override;

	virtual bool CheckConditions_Implementation(USHTNBlackboardGetWrapper* WorldState, const uint8 OperatorParam,
		const bool bIsPlanning) override;
	
	UFUNCTION()
	void MoveComplete(TEnumAsByte<EPathFollowingResult::Type> MoveResult, AAIController* AIController);

private:

	FMoveTaskCompletedSignature TaskSignature;
};
