#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StealthGame/ProceduralSpace.h"
#include "StealthGame/TileActor.h" // Include the header for ATileActor
#include "ProceduralSpaceManager.generated.h"

UCLASS()
class MENTORAMACPP5_API AProceduralSpaceManager : public AActor
{
	GENERATED_BODY()
    
public:    
	AProceduralSpaceManager();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RoomGeneration")
	TSubclassOf<AProceduralSpace> RoomClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RoomGeneration")
	TSubclassOf<ATileActor> WallActorClass; // Changed to ATileActor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RoomGeneration")
	TSubclassOf<ATileActor> EntranceActorClass; // Changed to ATileActor

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RoomGeneration")
	TSubclassOf<ATileActor> ExitActorClass; // Changed to ATileActor

	UFUNCTION(CallInEditor, Category="RoomGeneration")
	void EraseLastRoom();

	void SortRowsAndColumns();
	
	UFUNCTION(CallInEditor, Category="RoomGeneration")
	void GenerateNextRoom();

	int TotalRoomsCreatedCounter = 0;
	
	int32 NewRoomRows = 5;
	int32 NewRoomColumns = 5;

	float CalculateNewRoomRotation(float previousConnector, float newConnector);

	void AlignPassagesLocation(AProceduralSpace* PreviousRoom, AProceduralSpace* LastRoom);
	FRotator AlignPassagesRotation(AProceduralSpace* PreviousRoom, AProceduralSpace* LastRoom);
	
	UFUNCTION(CallInEditor, Category="RoomGeneration")
	void ClearRooms();

	UFUNCTION(CallInEditor, Category="RoomGeneration")
	void ProceedToNextRoom();

private:
	TArray<AProceduralSpace*> CreatedRooms; // Keep track of created rooms
	void AlignNewRoomWithPrevious();
	FTimerHandle TimerHandle;
};