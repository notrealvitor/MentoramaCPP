#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArkanoidTP/Brick.h"
#include "BrickManager.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllBricksDestroyed);

UCLASS()
class MENTORAMACPP5_API ABrickManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ABrickManager();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABrick> BrickClass;


	UFUNCTION(BlueprintCallable)
	void SpawnBricks(int NumRows, int NumColumns, int BrickHealth);					//int Amount, int Difficulty, bool Randomize

	UPROPERTY(EditAnywhere)
	int DefaultNumRows = 10;
	UPROPERTY(EditAnywhere)
	int DefaultNumColumns = 2;

	UPROPERTY(BlueprintReadWrite)
	FVector StartSpawnPosition = GetActorLocation();

	UPROPERTY(EditAnywhere)
	FVector OffsetBetweenBricks;
	
	UPROPERTY(BlueprintAssignable)
	FOnAllBricksDestroyed OnAllBricksDestroyed;
		
	FTimerHandle DelayTimerHandle;
	
	FVector GetPositionFor(int y, int z);

	UFUNCTION()
	void HandleBrickDestroyed(ABrick* DestroyedBrick);

	void ApplyScore(ABrick* DestroyedBrick);

	UPROPERTY(BlueprintReadWrite)
	TArray<ABrick*> Bricks;

	FVector BrickExtend;
	
};
