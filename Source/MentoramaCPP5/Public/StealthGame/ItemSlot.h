// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemAbility.h"
#include "ItemSlot.generated.h"

UENUM(BlueprintType)
enum EItemType
{
	Weapon,
	Throwable,
	Consumable,
	Equipment
};

USTRUCT(BlueprintType)
struct FItemCollisionType
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName SocketAttached = "hand_rSocket";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector LocationOffset = FVector(-45.0f,0.0f,0.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector CollisionExtent = FVector(40.0f,8.0f,8.0f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName CollisionPreset = "MeleeBox";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName AddTag = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool DebugCollision = false;
};

UCLASS()
class MENTORAMACPP5_API UItemSlot : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FText Description; // good to know what it does

	//slate modules needs to be enabled in the build.cs
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FSlateBrush Icon; //I think using Texture2D* is a bit simpler but I want to try this

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UStaticMesh* Mesh;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int Weight; //the played has a max wight to limit its inventory

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int BaseAttribute; //this could be used for attack damage, defense, amount to heal, etc

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TEnumAsByte<EItemType> E_ItemType;  //with the item type we can organize better the inventory and standardize its effects

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UItemAbility> ItemPrimaryAbility;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UItemAbility> ItemSecondaryAbility;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int InteractionTraceRange = 200;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FItemCollisionType> ItemCollisions;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Cooldown = 0;
	
};
