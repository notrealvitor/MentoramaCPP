// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Save_PlayerStatistics.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MentoramaHelpers.generated.h"

/**
 * 
 */
UCLASS()
class MENTORAMACPP5_API UMentoramaHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static int MySum(int a, int b, int c);

	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static int SumAll(TArray<int> Values);

	UFUNCTION(BlueprintPure, Category = "Helpers")
	static int GetBestScore(TArray<int> Scores);

	UFUNCTION(BlueprintPure, Category = "Helpers")
	static int Factorial(int Number);

	UFUNCTION(BlueprintPure, Category = "Helpers")
	static int FirstDivisibleNumber(int Number, bool NoPairs = false);

	UFUNCTION(BlueprintPure, Category = "Helpers")
	static int ListPrimeNumbers(int Number);

	UFUNCTION(BlueprintPure, Category = "Helpers")
	static bool IsNumberPrime(int Number);

	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static void PrintStringArray(TArray<FString> Value)
	{
		for (int i = 0; i < Value.Num(); i++)
		{
			UE_LOG(LogTemp, Display, TEXT("%s"), *Value[i]);
		}
	}

	UFUNCTION(BlueprintPure, Category = "Helpers")
	static bool IsPallindrome(FString Palavra);  //M6 Pallindromo sem TArray

	UFUNCTION(BlueprintPure, Category = "Helpers")
	static bool IsPallindromeFString(FString Palavra);  //M6 Pallindromo RETORNO


	UFUNCTION(BlueprintCallable, meta = (DisplayName = "WildcardArrayShuffleTest", CompactNodeTitle = "WildcardArrayShuffleTest", ArrayParm = "TargetArray", ArrayTypeDependentParams = "Item", BlueprintThreadSafe), Category = "Test")
	static void WildcardArrayShuffleTest(UPARAM(ref) TArray<int32>& TargetArray);


	UFUNCTION(BlueprintCallable, CustomThunk, meta = (DisplayName = "ShuffleTeste", CompactNodeTitle = "SHUFFLETESTE", ArrayParm = "TargetArray"), Category = "Helpers")
	static void ShuffleTeste(const TArray<int32>& TargetArray);								//Copiado do SHUFFLE da Engine para pesquisa

	static void GenericShuffleTeste(void* TargetArray, const FArrayProperty* ArrayProp);	//Copiado do SHUFFLE da Engine para pesquisa

	DECLARE_FUNCTION(execShuffleTeste)														//Copiado do SHUFFLE da Engine para pesquisa
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<FArrayProperty>(NULL);
		void* ArrayAddr = Stack.MostRecentPropertyAddress;
		FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericShuffleTeste(ArrayAddr, ArrayProperty);
		P_NATIVE_END;
	}


	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static void ShuffleStringArray(UPARAM(ref) TArray<FString>& TargetArray);	//M6 ShuffleString		

	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static void ShuffleSortStringArray(UPARAM(ref) TArray<FString>& TargetArray, bool SortFirst, FString ItemToInsert); //M6 InsertionSort

	UFUNCTION(BlueprintCallable, Category = "Helpers")
	static void InsertionSort(UPARAM(ref)TArray<int>& TargetArray);														//M6 InsertionSort RETORNO

	inline static bool ConstPredicate(const FString Name1, const FString Name2);
	
	UFUNCTION(BlueprintCallable, Category = "CustomSave")
	static void WriteUsernameToFile(FString Username);

	UFUNCTION(BlueprintPure, Category = "CustomSave")
	static FString ReadUsernameFromFile();
	
	static FString GetUsernameFileDataPath()
	{
		FString path = FPaths::GeneratedConfigDir() + FString("username.data"); //...saved/config/username.data
		return path;
	}

	UFUNCTION(BlueprintCallable, Category = "CustomSave")
	static void SavePlayerStatistics(int FailCount);

	UFUNCTION(BlueprintCallable, Category = "CustomSave")
	static int LoadPlayerStatistics();
	
};
