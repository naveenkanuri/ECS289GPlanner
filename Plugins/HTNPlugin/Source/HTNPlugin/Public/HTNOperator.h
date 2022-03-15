// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTNDomain.h"
#include "Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "HTNOperator.generated.h"


class AAIController;

UENUM()
enum class EHTNOperatorResult : uint8
{
	InProgress,
	Success,
	Failed,
	Aborted
};

UCLASS(NotBlueprintable)
class HTNPLUGIN_API UHTNBlackboard : public UObject
{

	GENERATED_BODY()

public:

	UHTNBlackboard() :
		Blackboard(nullptr)
	{}

	UFUNCTION()
		UObject* GetValueAsObject(const FName KeyName) const
	{
		return Blackboard->GetValueAsObject(KeyName);
	}

	UFUNCTION()
		UClass* GetValueAsClass(const FName KeyName) const
	{
		return Blackboard->GetValueAsClass(KeyName);
	}

	UFUNCTION()
		uint8 GetValueAsEnum(const FName KeyName) const
	{
		return Blackboard->GetValueAsEnum(KeyName);
	}

	UFUNCTION()
		int32 GetValueAsInt(const FName KeyName) const
	{
		return Blackboard->GetValueAsInt(KeyName);
	}

	UFUNCTION()
		float GetValueAsFloat(const FName KeyName) const
	{
		return Blackboard->GetValueAsFloat(KeyName);
	}

	UFUNCTION()
		bool GetValueAsBool(const FName KeyName) const
	{
		return Blackboard->GetValueAsBool(KeyName);
	}

	UFUNCTION()
		FString GetValueAsString(const FName KeyName) const
	{
		return Blackboard->GetValueAsString(KeyName);
	}

	UFUNCTION()
		FName GetValueAsName(const FName KeyName) const
	{
		return Blackboard->GetValueAsName(KeyName);
	}

	UFUNCTION()
		FVector GetValueAsVector(const FName KeyName) const
	{
		return Blackboard->GetValueAsVector(KeyName);
	}

	UFUNCTION()
		FRotator GetValueAsRotator(const FName KeyName) const
	{
		return Blackboard->GetValueAsRotator(KeyName);
	}

	UFUNCTION()
		bool GetLocationFromEntry(const FName KeyName, FVector& ResultLocation) const
	{
		return Blackboard->GetLocationFromEntry(KeyName, ResultLocation);
	}

protected:
	
	friend class UHTNOperator;

	UPROPERTY()
	UBlackboardComponent* Blackboard;

};


UCLASS()
class HTNPLUGIN_API UHTNOperator : public UObject
{
	GENERATED_BODY()
	
protected:

	bool bActivated;
	EHTNOperatorResult Result;

	UFUNCTION()
		virtual bool CheckConditions(UHTNBlackboard* WorldState, const uint8 OperatorParam, const bool bIsPlanning);

	UFUNCTION()
		virtual float GetScore(UHTNBlackboard* WorldState, const uint8 OperatorParam);

	UFUNCTION()
		virtual void ReceiveInitializeAction(AAIController* OwnerController, const uint8 OperatorParam);

	UFUNCTION()
		virtual void ReceiveExecuteAction(AAIController* OwnerController, const uint8 OperatorParam, const float DeltaTime);

	UFUNCTION()
		virtual void ReceiveAbort(AAIController* OwnerController, const uint8 OperatorParam);

	UFUNCTION()
		virtual void FinishExecute(bool bSuccess) { Result = bSuccess ? EHTNOperatorResult::Success : EHTNOperatorResult::Failed; }

	UFUNCTION()
		virtual void FinishAbort() { Result = EHTNOperatorResult::Aborted; }

	UPROPERTY()
	UWorld* World;

	UPROPERTY()
	UHTNBlackboard* SetProtectedWorldState;

public:

	UHTNOperator();

	void Init(UWorld* InWorld, FName& ElementCDOName);

	void SetWorld(UWorld* InWorld) { World = InWorld; }

	virtual UWorld* GetWorld() const override;

	 float GetScores(UBlackboardComponent* Blackboard, const uint8 OperatorParam)
	{
		SetProtectedWorldState->Blackboard = Blackboard;
		return GetScore(SetProtectedWorldState, OperatorParam);
	}

	bool CheckCondition(UBlackboardComponent* Blackboard, const uint8 OperatorParam, const bool bIsPlanning = false)
	{
		SetProtectedWorldState->Blackboard = Blackboard;
		return CheckConditions(SetProtectedWorldState, OperatorParam, bIsPlanning);
	}

	UFUNCTION()
	virtual void ApplyEffects(UBlackboardComponent* WorldState, const uint8 OperatorParam, const bool IsPlanning);

	void Initialize(AAIController* OwnerController, const uint8 OperatorParam)
	{
		bActivated = true;
		Result = EHTNOperatorResult::InProgress;
		ReceiveInitializeAction(OwnerController, OperatorParam);
	}

	void Execute(AAIController* OwnerController, const uint8 OperatorParam, const float DeltaTime)
	{
		Result = EHTNOperatorResult::InProgress;
		ReceiveExecuteAction(OwnerController, OperatorParam, DeltaTime);
	}

	void Abort(AAIController* OwnerController, const uint8 OperatorParam)
	{
		Terminate();
		ReceiveAbort(OwnerController, OperatorParam);
	}

	void Terminate() { bActivated = false; }
	EHTNOperatorResult GetResult() const { return Result; }
	bool IsActivated() const { return bActivated; }

	FName CDOName;
};
