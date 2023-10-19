// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadJsonArraySubsystem.h"
#include "JsonObjectConverter.h"

bool UReadJsonArraySubsystem::ReadJsonArray()
{
	FString JsonString = "";	
	Array.Empty();
	FString JsonFilePath = FPaths::ProjectContentDir() + "/Jsons/JsonArray.json";
	FFileHelper::LoadFileToString(JsonString,*JsonFilePath);
	/*FString JsonTestFilePath = FPaths::ProjectContentDir() + "/Test/JsonArray.json";
	FFileHelper::SaveStringToFile(JsonString,*JsonTestFilePath);*/
	const TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(JsonString);
	TSharedPtr<FJsonValue> JsonValue;	
	if (FJsonSerializer::Deserialize(Reader, JsonValue) && JsonValue.IsValid())
	{
		const TSharedPtr<FJsonObject>* JsonObject;
		if (JsonValue->TryGetObject(JsonObject))
		{
			TArray<TSharedPtr<FJsonValue>> ArraysArray = JsonObject->Get()->GetArrayField("Array");
			for (const auto& ArrayValue : ArraysArray)
			{
				TArray<TSharedPtr<FJsonValue>>* SecondArraysArray;
				if(ArrayValue->TryGetArray(SecondArraysArray))
				{
					FArray JsonArray;
					for(auto& Element : *SecondArraysArray)
					{
						int32 number = 0;
						if(Element->TryGetNumber(number))
							JsonArray.Array.Add(number);
					}
					Array.Add(JsonArray);
				}				
			}
			return true;
		}
	}
	return false;
}

bool UReadJsonArraySubsystem::GetResult(int32 i, int32 j, int32& Result) const
{
	if(Array.Num() >= i && Array.Num() != 0)
	{
		if(Array[i-1].Array.Num() >= j && Array.Num() != 0)
		{
			Result = Array[i-1].Array[j-1];
			return true;
		}
	}
	
	return false;
}
