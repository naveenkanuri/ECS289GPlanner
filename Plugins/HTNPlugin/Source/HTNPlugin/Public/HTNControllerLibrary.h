// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HTNDomain.h"
#include "HTNControllerLibrary.generated.h"


UCLASS()
class HTNPLUGIN_API USHTNControllerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SHTN")
	static bool RunHTNPlanner(class AAIController* AIController,  TSubclassOf<class USHTNNetwork_BlueprintBase> HTNNetwork);

protected:

	static bool SetupSHTNComponent(class USHTNComponent* SHTNComp, class USHTNNetwork_BlueprintBase* HTNNetwork);

	static USHTNComponent* GetSHTNComponent(AActor* Actor);

};
