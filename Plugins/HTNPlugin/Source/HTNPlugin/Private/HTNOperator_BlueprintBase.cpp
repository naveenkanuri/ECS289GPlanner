// Fill out your copyright notice in the Description page of Project Settings.


#include "HTNOperator_BlueprintBase.h"

void USHTNOperator_BlueprintBase::ReceiveInitializeAction_Implementation(AAIController* OwnerController,
	const uint8 OperatorParam)
{
	UE_LOG(HTNPlugin, Warning, TEXT("Base Implementation called in USHTNOperator_BlueprintBase::ReceiveInitializeAction(). Please check"));
}

void USHTNOperator_BlueprintBase::ReceiveExecuteAction_Implementation(AAIController* OwnerController,
	const uint8 OperatorParam, const float DeltaTime)
{
	UE_LOG(HTNPlugin, Warning, TEXT("Base Implementation called in USHTNOperator_BlueprintBase::ReceiveExecuteAction(). Please check"));
}

USHTNOperator_BlueprintBase::USHTNOperator_BlueprintBase()
{
	bActivated = false;
}

void USHTNOperator_BlueprintBase::Init(UWorld * InWorld, FName & ElementCDOName)
{
	SetWorld(InWorld);
	CDOName = ElementCDOName;
	SetProtectedWorldState = NewObject<USHTNBlackboardGetWrapper>(this, TEXT("SetProtectedWorldState"));
}

void USHTNOperator_BlueprintBase::ReceiveAbort_Implementation(AAIController* OwnerController, const uint8 OperatorParam)
{
	Result = ESHTNOperatorResult::Aborted;
}

UWorld * USHTNOperator_BlueprintBase::GetWorld() const
{
	return World;
}

void USHTNOperator_BlueprintBase::ApplyEffects_Implementation(UBlackboardComponent* WorldState,
	const uint8 OperatorParam, const bool IsPlanning)
{
	UE_LOG(HTNPlugin, Warning, TEXT("Base Implementation called in USHTNOperator_BlueprintBase::ApplyEffects(). Please check"));
}

bool USHTNOperator_BlueprintBase::CheckConditions_Implementation(USHTNBlackboardGetWrapper * WorldState, const uint8 OperatorParam, const bool bIsPlanning)
{
	return true;
}

float USHTNOperator_BlueprintBase::GetScore_Implementation(USHTNBlackboardGetWrapper* WorldState, const uint8 OperatorParam)
{
	// If not implemented assume score is 0
	return 0.f;
}