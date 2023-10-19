// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ReadJsonArraySubsystem.generated.h"

USTRUCT(BlueprintType)
struct FArray
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> Array;
};
UCLASS()
class READJSONARRAY_API UReadJsonArraySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, meta =(ExpandBoolAsExecs = "ReturnValue"))
	bool ReadJsonArray();

	UFUNCTION(BlueprintCallable)
	bool GetResult(int32 i, int32 j, int32& Result) const;
private:
	TArray<FArray> Array;
};
