// Fill out your copyright notice in the Description page of Project Settings.


#include "MentoramaHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Containers/UnrealString.h"

int UMentoramaHelpers::MySum(int a, int b, int c)
{
	return a + b + c;
}

int UMentoramaHelpers::SumAll(TArray<int> Values)
{
	int result = 0;
	for (int i = 0; i < Values.Num(); i++)
	{
		result += Values[i];
	}
	return result;
}

int UMentoramaHelpers::GetBestScore(TArray<int> Scores)
{
	int MaxScore = INT_MIN;
	for (int i = 0; i < Scores.Num(); i++)
	{
		if (Scores[i] > MaxScore)
		{
			MaxScore = Scores[i];
		}
	}
	return MaxScore;
}

int UMentoramaHelpers::Factorial(int Number)
{
	int result = 1;
	while (Number > 1)
	{
		result *= Number;
		Number--;
	}
	return result;
}

int UMentoramaHelpers::FirstDivisibleNumber(int Number, bool NoPairs)
{
	int Result = 2;
	do
	{
		if (Result % 2 == 0 && NoPairs == true)
		{
			Result++;
			continue;
		}

		if (Number % Result == 0)
		{
			break;
		}
		Result++;
	} while (Result < Number);
	return Result;
}

bool UMentoramaHelpers::IsNumberPrime(int Number)
{
	for (int i = 2; i < Number; i++)
	{
		if (Number % i == 0)
		{
			//UE_LOG(LogTemp, Display, TEXT("%d DIVISIVEL"), i);
			return false;

		}
	}
	UE_LOG(LogTemp, Display, TEXT("PRIMO %d"), Number);
	return true;
}

int UMentoramaHelpers::ListPrimeNumbers(int Number)
{
	int Primes = 0;
	for (int i = 2; i < Number; i++)
	{
		if (IsNumberPrime(i))
		{
			Primes++;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("%d numeros primos foram encontrados"), Primes);
	return Primes;

}

bool UMentoramaHelpers::IsPallindrome(FString Palavra)            //M6 PALINDROMO #1
{
	UE_LOG(LogTemp, Display, TEXT("WordStart %s"), *Palavra);

	int Index = 0;
	TArray<TCHAR> Pallindrome = Palavra.GetCharArray();											// Convertendo FString para Array #1
	//UE_LOG(LogTemp, Display, TEXT("Length %d"), Pallindrome.Num());	
	for (TCHAR Letter : Pallindrome)															// Convertendo FString para Array #2
	{
		//UE_LOG(LogTemp, Display, TEXT("Start %c"), Pallindrome[Index]);						 // use %c to get the TCHAR or crash
		//UE_LOG(LogTemp, Display, TEXT("End %c"), Pallindrome[Pallindrome.Num() - Index -2]);
		if (Pallindrome[Index] == Pallindrome[Pallindrome.Num() - Index - 2])					//achei estranho aqui ter que colocar -2 ao inv�s de -1
		{
			if (Pallindrome.Num() - 2 % 2 == 0)													//se Palavra for par
			{
				if (Index == Pallindrome.Num() - Index - 2 || Pallindrome.Num()/2 == Pallindrome.Num() / 2 + 1) //N�O CONSEGUI RESOLVER, ACHEI MELHOR DEIXAR PRA L� E OLHAR A DICA
				{
					return true;
				}
			} 
			else if (Index == Pallindrome.Num() - Index - 2)									//se Palavra for �mpar
			{
				return true;
			}
			Index++;
		}
		else break;
	}
	return false;
}

bool UMentoramaHelpers::IsPallindromeFString(FString Palavra)								 //M6 Palindromo #2
{
	UE_LOG(LogTemp, Display, TEXT("Length / 2 %d"), Palavra.Len()/2);

	for (int i = 0; i < Palavra.Len()/2; i++)												//Acessa at� o �ltimo elemento de Palavra
	{
		if (Palavra[i] == Palavra[Palavra.Len() - i - 1])									//Compara o elemento com o seu equivalente inverso
		{
			i++;
		}
		else
		{
			return false;
			break;
		}
	}
	return true;
}




void UMentoramaHelpers::ShuffleTeste(const TArray<int32>& TargetArray)  //Copiado do SHUFFLE da Engine como pesquisa, este serve apenas como uma refer�ncia para buildar o GenericShuffleTeste
{
	check(0);
}

void UMentoramaHelpers::GenericShuffleTeste(void* TargetArray, const FArrayProperty* ArrayProp) //Copiado do SHUFFLE da Engine como pesquisa, este � o ShuffleTeste reescrito
{ 
	if (TargetArray)
	{
		FScriptArrayHelper ArrayHelper(ArrayProp, TargetArray);
		int32 LastIndex = ArrayHelper.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(0, LastIndex);
			if (i != Index)
			{
				ArrayHelper.SwapValues(i, Index);
			}
		}
	}
}



void UMentoramaHelpers::ShuffleStringArray(TArray<FString>& TargetArray)			//M6 ShuffleString
{
	int i = 0;
	for (FString Element : TargetArray)
	{
		int32 RandomIndex = FMath::RandRange(0, (TargetArray.Num() - 1));
		TargetArray.Swap(i, RandomIndex);
	}
}




void UMentoramaHelpers::WildcardArrayShuffleTest(TArray<int32>& TargetArray) //esse est� crashando quando roda
{
	int i = 0;
	int32 LastIndex = TargetArray.Num() - 1;

	for (i = 0; i <= TargetArray.Num(); i++)
	{
		int32 RandomIndex = FMath::RandRange(0, LastIndex);
		if (i != RandomIndex)
		{
			TargetArray.Swap(i, RandomIndex);
		}
	}
}


inline static bool ConstShuffleSortPredicate(const FString Name1, const FString Name2)
{
	return (Name1 > Name2);
}


void UMentoramaHelpers::ShuffleSortStringArray(UPARAM(ref)TArray<FString>& TargetArray, bool SortFirst, FString ItemToInsert)		//M6 InsertionSort #1
{
	if (SortFirst)
	{	
		TargetArray.Sort(ConstShuffleSortPredicate);													//Bool para colocar tudo em ordem antes, para testar
	}

	for (int i = TargetArray.Num() - 1; i >= 0; i--)
	{
		UE_LOG(LogTemp, Display, TEXT("Insert %d"), ItemToInsert.Compare(TargetArray[i]));
		//UE_LOG(LogTemp, Display, TEXT("InsertTest %d"), ItemToInsert.Compare(TargetArray[i +1]));
		
		if (ItemToInsert.Compare(TargetArray[i]) <= 0)
		{
			TargetArray.Insert(ItemToInsert, i + 1);
			//UE_LOG(LogTemp, Display, TEXT("Insert %d"), i + 1);
			break;
		}
		else
		{
			if (i == 0)																					 //Se chegou at� o ultimo index e n�o adicionou, ent�o deve adicionar
			{
				TargetArray.Insert(ItemToInsert, i);
			}
		}
		
	}
}

void UMentoramaHelpers::InsertionSort(UPARAM(ref)TArray<int>& TargetArray)											  //M6 InsertionSort #2 exemplo tirado a p�gina da Wiki
{
	//TargetArray.Swap(0, 1);

	for (int i = 1; i < TargetArray.Num(); i++)					//Verifica todos elementos de TargetArray
	{
		int Escolhido = TargetArray[i];							//Escolhe o elemento a ser verificado
		int j = i - 1;											//Seta j como o elemento posterior ao escolhido anteriormente

		while ((j >= 0) && (TargetArray[j] > Escolhido))		//Compara se o elemento posterior ao escolhido � maior que o escolhido, se for maior n�o executa 
		{
			TargetArray[j + 1] = TargetArray[j];	//Substituiu o elemento J do array pelo pr�ximo at� encontrar
			j--;												//Verifica o while novamente, o elemento posterior a J
		}

		TargetArray[j + 1] = Escolhido;							//Quando n�o houver mais elementos maiores substitui o Escolhido pelo comparado no while
	}

}
