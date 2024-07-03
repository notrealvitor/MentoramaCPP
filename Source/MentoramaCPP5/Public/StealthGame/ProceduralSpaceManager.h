#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StealthGame/ProceduralSpace.h"
#include "NavMesh/NavMeshBoundsVolume.h"
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

	UPROPERTY(BlueprintReadOnly, Category="RoomGeneration" )
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RoomGeneration")
	TMap<TSubclassOf<ATileActor>, float> SpawnMap;

	AProceduralSpace* StorePreviousRoom;


public:
	// Function to adjust the NavMesh volume's location and size
	UFUNCTION(BlueprintCallable, Category = "RoomGeneration")
	void AdjustNavMeshVolume(const FVector& NewLocation, const FVector& NewExtent);
	void GetActorMidpointAndSize(AActor* Actor, FVector& OutMidpoint, FVector& OutSize) const;
	

protected:
	// Reference to the NavMeshBoundsVolume set in the Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoomGeneration")
	ANavMeshBoundsVolume* NavMeshVolume;
	

private:
	TArray<AProceduralSpace*> CreatedRooms; // Keep track of created rooms
	void AlignNewRoomWithPrevious();
	FTimerHandle TimerHandle;
};