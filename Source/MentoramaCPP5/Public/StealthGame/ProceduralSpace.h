#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StealthGame/TileActor.h"
#include "ProceduralSpace.generated.h"

UCLASS()
class MENTORAMACPP5_API AProceduralSpace : public AActor
{
    GENERATED_BODY()

public:
    AProceduralSpace();

protected:
    virtual void BeginPlay() override;
    void Destroyed();

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
    int32 Rows;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
    int32 Columns;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
    float TileSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
    TSubclassOf<ATileActor> TileActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
    TSubclassOf<ATileActor> WallActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
    TSubclassOf<ATileActor> EntranceActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
    TSubclassOf<ATileActor> ExitActorClass;

    UPROPERTY(BlueprintReadOnly, Category = "Grid Settings")
    ATileActor* SpawnedEntranceActor;

    UPROPERTY(BlueprintReadOnly, Category = "Grid Settings")
    ATileActor* SpawnedExitActor;    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
    float ExitEntranceDistancePercentage = 35.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Settings")
    float GroundTileHeight = 25.1f;

    UFUNCTION(BlueprintCallable, Category = "Grid Settings")
    void GenerateGrid(int32 RowsNewValue, int32 ColumnsNewValue);

    UFUNCTION(CallInEditor, Category = "Grid Settings")
    void TestGrid();

    UFUNCTION(CallInEditor,  Category = "Grid Settings")
    void ClearGrid();

    TArray<TPair<FVector, FVector>> CollectEdgeLocationPairs();
    bool FindValidEntranceExitPairs(const TArray<TPair<FVector, FVector>>& EdgeLocationPairs, TPair<FVector, FVector>& EntrancePair, TPair<FVector, FVector>& ExitPair);
    FVector CalculateGridCenter() const;
    FLinearColor DetermineTileColor(const FVector& Location) const;

    //inline void HandleEntranceActivated() { OnEntranceActivated.Broadcast(); };     //Not used anymore but I wanted to learn the inline method  

    UPROPERTY(BlueprintReadWrite, Category="Spawning")
    TMap<TSubclassOf<ATileActor>, float> SpawnMap;

    void SpawnActorsBasedOnMap();
    FVector GetRandomGroundTile();
    FVector GetRandomLocationInRoom();
    bool IsLocationValid(const FVector& Location);

    void SaveGroundTileLocations();

    TArray<FVector> GroundTileLocations;
    

private:
    void SpawnTiles(const FVector& GridCenter, const TPair<FVector, FVector>& EntrancePair, const TPair<FVector, FVector>& ExitPair);
    bool IsEdgeTile(int32 Row, int32 Column) const;
    bool IsCornerTile(int32 Row, int32 Column) const;
    bool HandleEntranceExitTiles(const FVector& Location, const TPair<FVector, FVector>& EntrancePair, const TPair<FVector, FVector>& ExitPair, const FVector& GridCenter, FActorSpawnParameters& SpawnParams);
    FRotator CalculateFacingRotation(const FVector& Location) const;
    FVector CalculateTileMidpoint(const TPair<FVector, FVector>& TilePair) const;

    ATileActor* SpawnActor(TSubclassOf<ATileActor> ActorClass, const FVector& Location, const FRotator& Rotation, FActorSpawnParameters& SpawnParams, int32 Index);
    ATileActor* SpawnActor(TSubclassOf<ATileActor> ActorClass, const FVector& Location, const FRotator& Rotation, FActorSpawnParameters& SpawnParams);



};

    