
#include "HTNOperator.h"

bool UHTNOperator::CheckConditions(UHTNBlackboard* WorldState, const uint8 OperatorParam, const bool bIsPlanning)
{
	return true;
}

float UHTNOperator::GetScore(UHTNBlackboard* WorldState, const uint8 OperatorParam)
{
	return 0.f;
}

void UHTNOperator::ReceiveInitializeAction(AAIController* OwnerController, const uint8 OperatorParam)
{
	UE_LOG(HTNPlugin, Warning, TEXT("Calling Base Receive Initialize Action for %s"), *this->GetName());
}

void UHTNOperator::ReceiveExecuteAction(AAIController* OwnerController, const uint8 OperatorParam,
	const float DeltaTime)
{
	UE_LOG(HTNPlugin, Warning, TEXT("Calling Base Receive Execute Action for %s"), *this->GetName());
}

void UHTNOperator::ReceiveAbort(AAIController* OwnerController, const uint8 OperatorParam)
{
	Result = EHTNOperatorResult::Aborted;
}

UHTNOperator::UHTNOperator()
{
	bActivated = false;
}

void UHTNOperator::Init(UWorld* InWorld, FName& ElementCDOName)
{
	SetWorld(InWorld);
	CDOName = ElementCDOName;
	SetProtectedWorldState = NewObject<UHTNBlackboard>(this, TEXT("SetProtectedWorldState"));
}

UWorld* UHTNOperator::GetWorld() const
{
	return UObject::GetWorld();
}

void UHTNOperator::ApplyEffects(UBlackboardComponent* WorldState, const uint8 OperatorParam, const bool IsPlanning)
{
	UE_LOG(HTNPlugin, Warning, TEXT("Calling Base Apply Effects for %s"), *this->GetName());
}
