#include "StealthGame/ProceduralSpace.h"
#include "StealthGame/TileActor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h" 
#include "GameFramework/Actor.h"

AProceduralSpace::AProceduralSpace()
{
    PrimaryActorTick.bCanEverTick = true;
    Rows = 15;
    Columns = 15;
    TileSize = 100.0f; // Assuming 1x1 meter tiles are scaled to 100 unreal units
}

void AProceduralSpace::BeginPlay()
{
    Super::BeginPlay();
}

void AProceduralSpace::Destroyed()
{
    Super::Destroyed();
    ClearGrid();
}

void AProceduralSpace::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProceduralSpace::ClearGrid()
{
    TArray<AActor*> AttachedActors;
    GetAttachedActors(AttachedActors);
    for (AActor* Actor : AttachedActors)
    {
        Actor->Destroy();
    }
}

void AProceduralSpace::GenerateGrid(int32 RowsNewValue, int32 ColumnsNewValue)
{
    ClearGrid();

    if (!TileActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("TileActorClass is not assigned."));
        return;
    }
    
    if (RowsNewValue != 0)      Rows = RowsNewValue;  //if value is zero, use the defaults
    if (ColumnsNewValue != 0)   Rows = ColumnsNewValue; 
    
    FVector GridCenter = CalculateGridCenter();
    TArray<TPair<FVector, FVector>> EdgeLocationPairs = CollectEdgeLocationPairs();
    TPair<FVector, FVector> EntrancePair;
    TPair<FVector, FVector> ExitPair;
    bool bValidPairsFound = FindValidEntranceExitPairs(EdgeLocationPairs, EntrancePair, ExitPair);

    if (bValidPairsFound)
    {
        SpawnTiles(GridCenter, EntrancePair, ExitPair);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Valid entrance and exit pairs not found."));
    }
}

void AProceduralSpace::TestGrid()
{
    GenerateGrid(0,0);
}

void AProceduralSpace::SpawnTiles(const FVector& GridCenter, const TPair<FVector, FVector>& EntrancePair, const TPair<FVector, FVector>& ExitPair)
{
    FVector ActorLocation = GetActorLocation();
    int32 Index = 1;
    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Column = 0; Column < Columns; ++Column)
        {
            FVector Location = ActorLocation + FVector(Row * TileSize, Column * TileSize, 0.0f);
            FRotator Rotation = FRotator::ZeroRotator;
            FActorSpawnParameters SpawnParams;

            if (IsEdgeTile(Row, Column))
            {
                if (HandleEntranceExitTiles(Location, EntrancePair, ExitPair, GridCenter, SpawnParams))
                {
                    continue;
                }
                else
                {
                    ATileActor* WallActor = SpawnActor(WallActorClass, Location, Rotation, SpawnParams, Index);
                    Index++;
                }
            }
            else
            {
                SpawnActor(TileActorClass, Location, Rotation, SpawnParams, Index);
                Index++;
            }
        }
    }   
}

ATileActor* AProceduralSpace::SpawnActor(TSubclassOf<ATileActor> ActorClass, const FVector& Location, const FRotator& Rotation, FActorSpawnParameters& SpawnParams, int32 Index)
{
    ATileActor* NewActor = GetWorld()->SpawnActor<ATileActor>(ActorClass, Location, Rotation, SpawnParams);
    if (NewActor)
    {
        NewActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        if (Index != -1)
        {
            NewActor->Index = Index;
        }

        FLinearColor Color = DetermineTileColor(Location);
        NewActor->SetTileColor(Color);
    }
    return NewActor;
}

ATileActor* AProceduralSpace::SpawnActor(TSubclassOf<ATileActor> ActorClass, const FVector& Location, const FRotator& Rotation, FActorSpawnParameters& SpawnParams)
{
    ATileActor* NewActor = GetWorld()->SpawnActor<ATileActor>(ActorClass, Location, Rotation, SpawnParams);
    if (NewActor)
    {
        NewActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

        FLinearColor Color = DetermineTileColor(Location);
        NewActor->SetTileColor(Color);
    }
    return NewActor;
}

TArray<TPair<FVector, FVector>> AProceduralSpace::CollectEdgeLocationPairs()
{
    TArray<TPair<FVector, FVector>> EdgeLocationPairs;

    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Column = 0; Column < Columns; ++Column)
        {
            if (IsCornerTile(Row, Column))
            {
                continue;
            }

            if (IsEdgeTile(Row, Column))
            {
                FVector Location1(Row * TileSize, Column * TileSize, 0.0f);
                if (Row == 0 && Column < Columns - 1)
                {
                    FVector Location2(Row * TileSize, (Column + 1) * TileSize, 0.0f);
                    if (Column + 1 < Columns - 1)
                        EdgeLocationPairs.Add(TPair<FVector, FVector>(Location1, Location2));
                }
                else if (Column == 0 && Row < Rows - 1)
                {
                    FVector Location2((Row + 1) * TileSize, Column * TileSize, 0.0f);
                    if (Row + 1 < Rows - 1)
                        EdgeLocationPairs.Add(TPair<FVector, FVector>(Location1, Location2));
                }
                else if (Row == Rows - 1 && Column < Columns - 1)
                {
                    FVector Location2(Row * TileSize, (Column + 1) * TileSize, 0.0f);
                    if (Column + 1 < Columns - 1)
                        EdgeLocationPairs.Add(TPair<FVector, FVector>(Location1, Location2));
                }
                else if (Column == Columns - 1 && Row < Rows - 1)
                {
                    FVector Location2((Row + 1) * TileSize, Column * TileSize, 0.0f);
                    if (Row + 1 < Rows - 1)
                        EdgeLocationPairs.Add(TPair<FVector, FVector>(Location1, Location2));
                }
            }
        }
    }
    return EdgeLocationPairs;
}

bool AProceduralSpace::FindValidEntranceExitPairs(const TArray<TPair<FVector, FVector>>& EdgeLocationPairs, TPair<FVector, FVector>& EntrancePair, TPair<FVector, FVector>& ExitPair)
{
    bool bValidPairFound = false;
    TArray<TPair<FVector, FVector>> EdgePairs = EdgeLocationPairs;

    float GridDiagonal = FVector::Dist(FVector(0, 0, 0), FVector(Rows * TileSize, Columns * TileSize, 0));
    float MinDistance = (ExitEntranceDistancePercentage / 100.0f) * GridDiagonal;

     while (!bValidPairFound && EdgePairs.Num() >= 2)
    {
        int32 EntranceIndex = FMath::RandRange(0, EdgePairs.Num() - 1);
        EntrancePair = EdgePairs[EntranceIndex];
        EdgePairs.RemoveAt(EntranceIndex);

        //UE_LOG(LogTemp, Warning, TEXT("Selected Entrance Pair: %s and %s"), *EntrancePair.Key.ToString(), *EntrancePair.Value.ToString());

        for (int32 i = 0; i < EdgePairs.Num(); ++i)
        {
            int32 ExitIndex = FMath::RandRange(0, EdgePairs.Num() - 1);
            ExitPair = EdgePairs[ExitIndex];

            float Distance = FVector::Dist((EntrancePair.Key + EntrancePair.Value) / 2.0f, (ExitPair.Key + ExitPair.Value) / 2.0f);
            if (Distance >= MinDistance)
            {
                bValidPairFound = true;
                //UE_LOG(LogTemp, Warning, TEXT("Selected Exit Pair: %s and %s with Distance: %f"), *ExitPair.Key.ToString(), *ExitPair.Value.ToString(), Distance);
                break;
            }
        }
    }
    return bValidPairFound;
}

bool AProceduralSpace::HandleEntranceExitTiles(const FVector& Location, const TPair<FVector, FVector>& EntrancePair, const TPair<FVector, FVector>& ExitPair, const FVector& GridCenter, FActorSpawnParameters& SpawnParams)
{
    FRotator FacingRotation = CalculateFacingRotation(Location);

    if ((Location.Equals(GetActorLocation() + EntrancePair.Key) || Location.Equals(GetActorLocation() + EntrancePair.Value)) && EntranceActorClass)
    {
        FVector Midpoint = CalculateTileMidpoint(EntrancePair);
        Midpoint += GetActorLocation();
        if (Location.Equals(GetActorLocation() + EntrancePair.Key))
        {
            SpawnedEntranceActor = SpawnActor(EntranceActorClass, Midpoint, FacingRotation, SpawnParams);
            //SpawnedEntranceActor->OnTileActivated.AddDynamic(this, &AProceduralSpace::HandleEntranceActivated); not being used anymore, we can call it directly from the SpaceManager
        }
        return true;
    }
    else if ((Location.Equals(GetActorLocation() + ExitPair.Key) || Location.Equals(GetActorLocation() + ExitPair.Value)) && ExitActorClass)
    {
        FVector Midpoint = CalculateTileMidpoint(ExitPair);
        Midpoint += GetActorLocation();
        if (Location.Equals(GetActorLocation() + ExitPair.Key))
        {
            SpawnedExitActor = SpawnActor(ExitActorClass, Midpoint, FacingRotation, SpawnParams);
            //SpawnedEntranceActor->OnTileActivated.AddDynamic(this, &AProceduralSpace::HandleExitActivated); not being used anymore, we can call it directly from the SpaceManager
        }
        return true;
    }

    return false;
}


void AProceduralSpace::SpawnActorsBasedOnMap()
{
    SaveGroundTileLocations();
    
    for (const auto& Elem : SpawnMap)
    {
        TSubclassOf<ATileActor> ActorClass = Elem.Key;
        float SpawnChance = Elem.Value;

        float RandomValue = FMath::FRand();
        if (RandomValue <= SpawnChance)
        {
            float SpawnZOffset = GroundTileHeight;
            FVector RandomLocation = GetRandomGroundTile() ; 
            if (IsLocationValid(RandomLocation))
            {
                FRotator Rotation = FRotator::ZeroRotator;
                FActorSpawnParameters SpawnParams;
                ATileActor* NewActor = GetWorld()->SpawnActor<ATileActor>(ActorClass, RandomLocation, Rotation, SpawnParams);
                if (NewActor)
                {
                    NewActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                }
            }
        }
    }
}

FVector AProceduralSpace::GetRandomGroundTile()
{
    if (GroundTileLocations.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, GroundTileLocations.Num() - 1);
        FVector SelectedTile = GroundTileLocations[RandomIndex];
        SelectedTile.Z += GroundTileHeight; // Adjust Z to be above the ground level
        return SelectedTile;
    }

    // Return a default location if no ground tile is found (shouldn't happen)
    return GetActorLocation();
}

FVector AProceduralSpace::GetRandomLocationInRoom()
{
    // Verify and log the actor's name for debugging


    float MinX = GetActorLocation().X + TileSize; // Avoid the left wall
    float MaxX = GetActorLocation().X + (Rows - 2) * TileSize; // Avoid the right wall
    float MinY = GetActorLocation().Y + TileSize; // Avoid the bottom wall
    float MaxY = GetActorLocation().Y + (Columns - 2) * TileSize; // Avoid the top wall

    float RandomX = FMath::FRandRange(MinX, MaxX);
    float RandomY = FMath::FRandRange(MinY, MaxY);

    float SpawnZOffset = GroundTileHeight;; // Offset to spawn slightly above the ground

    return FVector(RandomX, RandomY, GetActorLocation().Z + SpawnZOffset); // Adjust Z to be above the ground level
}

bool AProceduralSpace::IsLocationValid(const FVector& Location)
{
    // Verify and log the actor's name for debugging
    FString ActorName = GetName();
    //UE_LOG(LogTemp, Warning, TEXT("Validating location for Actor: %s at Location: %s"), *ActorName, *Location.ToString());

    // Example: Simple overlap check with other actors
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this); // Ignore the current actor

    FHitResult HitResult;
    FVector BoxHalfSize(TileSize / 2.1, TileSize / 2.1, TileSize / 2.1); // Half size of the box
    FVector BoxLocation = Location + FVector(0, 0, TileSize / 2); // Offset the box a bit higher

    bool bHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        BoxLocation,
        BoxLocation,
        FQuat::Identity,
        ECC_Visibility,
        FCollisionShape::MakeBox(BoxHalfSize),
        QueryParams
    );

    // Draw a debug box at the location being checked
    DrawDebugBox(GetWorld(), BoxLocation + FVector3d(TileSize / 2,TileSize / 2,0), BoxHalfSize, FColor::Blue, false, 20.0f);

    // Log the result of the collision check for debugging
    if (bHit)
    {
        if (HitResult.GetActor())
        {
            UE_LOG(LogTemp, Warning, TEXT("Location %s is not valid: hit %s"), *BoxLocation.ToString(), *HitResult.GetActor()->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Location %s is not valid: hit something"), *BoxLocation.ToString());
        }
        // Draw a red debug box if the location is not valid
        DrawDebugBox(GetWorld(), BoxLocation + FVector3d(TileSize / 2,TileSize / 2,0), BoxHalfSize, FColor::Red, false, 20.0f);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Location %s is valid"), *BoxLocation.ToString());
        // Draw a green debug box if the location is valid
        DrawDebugBox(GetWorld(), BoxLocation + FVector3d(TileSize / 2,TileSize / 2,0), BoxHalfSize, FColor::Green, false, 20.0f);
    }

    return !bHit;
}

void AProceduralSpace::SaveGroundTileLocations()
{
    GroundTileLocations.Empty(); // Clear the array before populating

    FVector ActorLocation = GetActorLocation();
    FRotator ActorRotation = GetActorRotation();
    FTransform ActorTransform = GetActorTransform();

    for (int32 Row = 1; Row < Rows - 1; ++Row)
    {
        for (int32 Column = 1; Column < Columns - 1; ++Column)
        {
            FVector LocalTileLocation = FVector(Row * TileSize, Column * TileSize, 0);
            FVector WorldTileLocation = ActorTransform.TransformPosition(LocalTileLocation);
            GroundTileLocations.Add(WorldTileLocation);
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Ground tile locations saved. Total: %d"), GroundTileLocations.Num());
}

FRotator AProceduralSpace::CalculateFacingRotation(const FVector& Location) const
{
    if (Location.X == GetActorLocation().X)
    {
        return FRotator(0.0f, 90.0f, 0.0f); // Facing right
    }
    else if (Location.X == GetActorLocation().X + (Rows - 1) * TileSize)
    {
        return FRotator(0.0f, -90.0f, 0.0f); // Facing left
    }
    else if (Location.Y == GetActorLocation().Y)
    {
        return FRotator(0.0f, 0.0f, 0.0f); // Facing down
    }
    else if (Location.Y == GetActorLocation().Y + (Columns - 1) * TileSize)
    {
        return FRotator(0.0f, 180.0f, 0.0f); // Facing up
    }
    return FRotator::ZeroRotator;
}

FVector AProceduralSpace::CalculateTileMidpoint(const TPair<FVector, FVector>& TilePair) const
{
    FVector Midpoint = (TilePair.Key + TilePair.Value) / 2.0f;
    Midpoint += FVector(TileSize / 2.0f, TileSize / 2.0f, 0.0f);
    return Midpoint;
}

FLinearColor AProceduralSpace::DetermineTileColor(const FVector& Location) const
{
    const float Tolerance = TileSize / 2.0f; // Tolerance to include midpoints

    FLinearColor Color;

    // Adjusted conditions to include midpoints within the tolerance
    if (FMath::IsNearlyEqual(Location.X, GetActorLocation().X, Tolerance)) // Left
    {
        Color = FLinearColor::Red; // Tint for left side
    }
    else if (FMath::IsNearlyEqual(Location.X, GetActorLocation().X + (Rows - 1) * TileSize, Tolerance)) // Right
    {
        Color = FLinearColor::Green; // Tint for right side
    }
    else if (FMath::IsNearlyEqual(Location.Y, GetActorLocation().Y, Tolerance)) // Bottom
    {
        Color = FLinearColor::Blue; // Tint for bottom side
    }
    else if (FMath::IsNearlyEqual(Location.Y, GetActorLocation().Y + (Columns - 1) * TileSize, Tolerance)) // Top
    {
        Color = FLinearColor::Yellow; // Tint for top side
    }
    else // Default color if not an edge
    {
        Color = FLinearColor::White;
    }

    return Color;
}

FVector AProceduralSpace::CalculateGridCenter() const
{
    return FVector((Rows - 1) * TileSize / 2.0f, (Columns - 1) * TileSize / 2.0f, 0.0f);
}

bool AProceduralSpace::IsEdgeTile(int32 Row, int32 Column) const
{
    return Row == 0 || Column == 0 || Row == Rows - 1 || Column == Columns - 1;
}

bool AProceduralSpace::IsCornerTile(int32 Row, int32 Column) const
{
    return (Row == 0 && Column == 0) ||
           (Row == 0 && Column == Columns - 1) ||
           (Row == Rows - 1 && Column == 0) ||
           (Row == Rows - 1 && Column == Columns - 1);
}