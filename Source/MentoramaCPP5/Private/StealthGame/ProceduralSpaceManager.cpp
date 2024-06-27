#include "StealthGame/ProceduralSpaceManager.h"

#include "EngineUtils.h"
#include "NavigationSystemTypes.h"
#include "Engine/World.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "StealthGame/ProceduralSpace.h"
#include "StealthGame/TileActor.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "AI/NavigationSystemBase.h"
#include "Builders/CubeBuilder.h"
#include "Components/BrushComponent.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "Components/BrushComponent.h"
#include "AI/NavigationSystemBase.h"
#include "Engine/Polys.h"
#include "Model.h"

AProceduralSpaceManager::AProceduralSpaceManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AProceduralSpaceManager::BeginPlay()
{
    Super::BeginPlay();
    ClearRooms();
    GenerateNextRoom();
    GenerateNextRoom();
}

void AProceduralSpaceManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProceduralSpaceManager::EraseLastRoom()
{
    if (CreatedRooms.Num() > 2)
    {
        if (CreatedRooms.IsValidIndex(0) && CreatedRooms[0])
        {
            CreatedRooms[0]->ClearGrid();
            CreatedRooms[0]->Destroy();
            CreatedRooms.RemoveAt(0);
        }
    }
}

void AProceduralSpaceManager::SortRowsAndColumns()
{ 
    int32 N = 7 + (TotalRoomsCreatedCounter/2);
    NewRoomRows = FMath::RandRange(5, N);           //less than 5  will break the room
    NewRoomColumns = FMath::RandRange(5, N);        //less than 5  will break the room
}

void AProceduralSpaceManager::GenerateNextRoom()
{
    if (!RoomClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("RoomClass is not assigned."));
        return;
    }
    FVector RoomLocation = FVector(0.0f, 0.0f, 0.0f); // Initial location for the new room
    FRotator RoomRotation = FRotator::ZeroRotator;
    FActorSpawnParameters SpawnParams;

    AProceduralSpace* NewRoom = GetWorld()->SpawnActor<AProceduralSpace>(RoomClass, RoomLocation, RoomRotation, SpawnParams);

    if (NewRoom)
    {
        // Set the actor classes for the new room
        NewRoom->WallActorClass = WallActorClass;
        NewRoom->EntranceActorClass = EntranceActorClass;
        NewRoom->ExitActorClass = ExitActorClass;

        // Pass the spawn map to the new room
        NewRoom->SpawnMap = SpawnMap;
        
        // Call GenerateGrid on the new room
        SortRowsAndColumns(); //Sort the RoomSize based on how many rooms were created
        NewRoom->GenerateGrid(NewRoomRows, NewRoomColumns);

        NewRoom->SpawnedEntranceActor->OnTileActivated.AddDynamic(this, &AProceduralSpaceManager::ProceedToNextRoom);
        
        if (CreatedRooms.Num() <= 0) //Close the entrance if it is the first room
        {
            NewRoom->SpawnedEntranceActor->ActivateTile();           
        } 
        
        CreatedRooms.Add(NewRoom); // Keep track of the created room
        TotalRoomsCreatedCounter++;

        // Align the new room with the previous one if applicable
        AlignNewRoomWithPrevious();
        NewRoom->SpawnActorsBasedOnMap();
        
        FVector NewRoomMidpoint, PreviousRoomMidpoint, NewRoomMSize, PreviousRoomSize;
        
        GetActorMidpointAndSize(NewRoom, NewRoomMidpoint, NewRoomMSize);
        if (StorePreviousRoom)
        {
            GetActorMidpointAndSize(StorePreviousRoom, PreviousRoomMidpoint, PreviousRoomSize);
        }
        AdjustNavMeshVolume((NewRoomMidpoint + PreviousRoomMidpoint) / 2, NewRoomMSize+PreviousRoomSize);
    }
    else UE_LOG(LogTemp, Warning, TEXT("Failed to create new room"));
}


void AProceduralSpaceManager::AlignNewRoomWithPrevious()
{
    if (CreatedRooms.Num() < 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough rooms to align. At least one existing room is required."));
        return;
    }

    StorePreviousRoom = CreatedRooms[CreatedRooms.Num() - 2];
    AProceduralSpace* LastRoom = CreatedRooms.Last();

    // Find the rotation needed to align the rooms
    FRotator RotationDifference = AlignPassagesRotation(StorePreviousRoom, LastRoom);

    // Apply rotation difference
    LastRoom->SetActorRotation(RotationDifference); // Apply rotation difference

    // Align the passages' locations
    AlignPassagesLocation(StorePreviousRoom, LastRoom);
}

float AProceduralSpaceManager::CalculateNewRoomRotation(float PreviousConnector, float NewConnector)
{
    float RotationMatrix[4][4] = {
        {180.0f, 270.0f, 0.0f, 90.0f},   // PreviousConnector 0
        {90.0f, 180.0f, 270.0f, 0.0f},   // PreviousConnector 90
        {0.0f, 90.0f, 180.0f, 270.0f},   // PreviousConnector 180
        {270.0f, 0.0f, 90.0f, 180.0f}    // PreviousConnector -90
    };

    // Function to map connector angles to indices
    auto ConnectorToIndex = [](float Connector) -> int
    {
        if (std::fabs(Connector - 0.0f) < 1e-6) return 0;
        if (std::fabs(Connector - 90.0f) < 1e-6) return 1;
        if (std::fabs(Connector - 180.0f) < 1e-6 || std::fabs(Connector + 180.0f) < 1e-6) return 2;
        if (std::fabs(Connector - 270.0f) < 1e-6 || std::fabs(Connector + 90.0f) < 1e-6) return 3;
        return -1; // Handle error case appropriately
    };

    int PreviousIndex = ConnectorToIndex(PreviousConnector);
    int NewIndex = ConnectorToIndex(NewConnector);

    // Ensure indices are valid
    if (PreviousIndex == -1 || NewIndex == -1)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid connector angle provided: PreviousConnector=%f, NewConnector=%f"), PreviousConnector, NewConnector);
        return 0.0f; // Return a default value (0.0f) or handle it as you see fit
    }
    return RotationMatrix[PreviousIndex][NewIndex];
}

FRotator AProceduralSpaceManager::AlignPassagesRotation(AProceduralSpace* PreviousRoom, AProceduralSpace* NewRoom)
{
    ATileActor* PreviousRoomConnector = PreviousRoom->SpawnedExitActor;
    ATileActor* NewRoomConnector = NewRoom->SpawnedEntranceActor;

    if (PreviousRoomConnector && NewRoomConnector)
    {
        float PreviousConnectorYaw = PreviousRoom->SpawnedExitActor->GetActorRotation().Yaw;      
        float NewConnectorYaw = NewRoomConnector->GetActorRotation().Yaw;
        float NewRoomRotation = CalculateNewRoomRotation(PreviousConnectorYaw, NewConnectorYaw);
        float PreviousRoomRotation = PreviousRoom->GetActorRotation().Yaw;

        if (PreviousRoomRotation == 90 || PreviousRoomRotation == -90) //for some reason when the Previous room is 90 or -90, the NewRoom needs a 180 offset
        {
            NewRoomRotation += 180;
        }
        
        return FRotator(0.0f, NewRoomRotation, 0.0f);
    }
    return FRotator::ZeroRotator;
}

void AProceduralSpaceManager::AlignPassagesLocation(AProceduralSpace* PreviousRoom, AProceduralSpace* LastRoom)
{
    FVector PreviousExitLocation;
    FVector LastEntranceLocation;

    // Find the ExitActor in the PreviousRoom
    TArray<AActor*> PreviousRoomActors;
    PreviousRoom->GetAttachedActors(PreviousRoomActors);
    for (AActor* Actor : PreviousRoomActors)
    {
        if (Actor->IsA(ExitActorClass))
        {
            PreviousExitLocation = Actor->GetActorLocation();
            break;
        }
    }

    // Find the EntranceActor in the LastRoom
    TArray<AActor*> LastRoomActors;
    LastRoom->GetAttachedActors(LastRoomActors);
    for (AActor* Actor : LastRoomActors)
    {
        if (Actor->IsA(EntranceActorClass))
        {
            LastEntranceLocation = Actor->GetActorLocation();
            break;
        }
    }
    FVector3d ConnectorsOffset;

    ATileActor* PreviousRoomConnector = PreviousRoom->SpawnedExitActor;
    float PreviousRoomConnectorRotationYaw = PreviousRoomConnector->GetActorRotation().Yaw;
    float TileSize = PreviousRoom->TileSize;
    FLinearColor PreviousRoomConnectorColor = PreviousRoomConnector->DebugColor;
    
    float PreviousRoomRotation = PreviousRoom->GetActorRotation().Yaw;
    
    //When the room is spawned rotated some calculations change
    //Theres probably a better math for that but I cant spending too much time in this
    if (PreviousRoomConnectorColor == FLinearColor::Red)
    {
        ConnectorsOffset = FVector(-TileSize , 0, 0);
        if (PreviousRoomRotation == 90 ) ConnectorsOffset = FVector(0, -TileSize, 0);
        if (PreviousRoomRotation == 180 ) ConnectorsOffset = FVector(TileSize, 0, 0);
        if (PreviousRoomRotation == -90 ) ConnectorsOffset = FVector(0, TileSize, 0);
    }
    else if (PreviousRoomConnectorColor == FLinearColor::Green)
    {
        ConnectorsOffset = FVector(TileSize, 0, 0);
        if (PreviousRoomRotation == 90 ) ConnectorsOffset = FVector(0, TileSize, 0);
        if (PreviousRoomRotation == 180 ) ConnectorsOffset = FVector(-TileSize, 0, 0);
        if (PreviousRoomRotation == -90 ) ConnectorsOffset = FVector(0, -TileSize, 0);
    }
    else if (PreviousRoomConnectorColor == FLinearColor::Blue)
    {
        ConnectorsOffset = FVector(0, -TileSize, 0);
        if (PreviousRoomRotation == 90 ) ConnectorsOffset = FVector(TileSize, 0, 0);
        if (PreviousRoomRotation == 180 ) ConnectorsOffset = FVector(0, TileSize, 0);
        if (PreviousRoomRotation == -90 ) ConnectorsOffset = FVector(-TileSize, 0, 0);
    }
    else if (PreviousRoomConnectorColor == FLinearColor::Yellow)
    {
        ConnectorsOffset = FVector(0, TileSize, 0);
        if (PreviousRoomRotation == 90 ) ConnectorsOffset = FVector(-TileSize, 0, 0);
        if (PreviousRoomRotation == 180 ) ConnectorsOffset = FVector(0, -TileSize, 0);
        if (PreviousRoomRotation == -90 ) ConnectorsOffset = FVector(TileSize, 0, 0);
    }

    FVector Offset = PreviousExitLocation - LastEntranceLocation + ConnectorsOffset;
    LastRoom->AddActorWorldOffset(Offset);
}

void AProceduralSpaceManager::ClearRooms()
{
    for (AProceduralSpace* Room : CreatedRooms)
    {
        if (Room)
        {
            Room->ClearGrid(); // Clear the grid of the room
            Room->Destroy(); // Destroy the room actor
        }
    }
    CreatedRooms.Empty(); // Clear the array of created rooms
    TotalRoomsCreatedCounter = 0;
}

void AProceduralSpaceManager::ProceedToNextRoom()
{
    if (CreatedRooms.Num() >= 2) //the system needs at least two rooms to work
    {
        AProceduralSpace* NewRoom = CreatedRooms[CreatedRooms.Num() - 1];
        AProceduralSpace* PreviousRoom = CreatedRooms[CreatedRooms.Num() - 2];
    
        if (NewRoom && PreviousRoom)
        {
            GenerateNextRoom();
            PreviousRoom->SpawnedExitActor->OnTileActivated.Broadcast(); //make the door close and activate the collider
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProceduralSpaceManager::EraseLastRoom, 1.0f, false);
            //EraseLastRoom();
        }
        else
        {
            // Handle the case where one or both of the pointers are invalid
            UE_LOG(LogTemp, Error, TEXT("NewRoom or PreviousRoom is not valid."));
        }
    }
    else
    {
        // Handle the case where there are not enough elements in the array
        UE_LOG(LogTemp, Error, TEXT("Not enough rooms in CreatedRooms array. The system needs at least two rooms created to work"));
    }
    
}

void AProceduralSpaceManager::AdjustNavMeshVolume(const FVector& NewLocation, const FVector& NewExtent)
{
    if (NavMeshVolume)
    {
        // Adjust the location and extent of the NavMeshBoundsVolume
        NavMeshVolume->SetActorLocation(NewLocation);
        NavMeshVolume->SetActorScale3D(NewExtent);

        // Update the brush settings
        UBrushComponent* BrushComponent = NavMeshVolume->GetBrushComponent();
        if (BrushComponent)
        {
            BrushComponent->SetMobility(EComponentMobility::Static);
            BrushComponent->bAlwaysCreatePhysicsState = true;

            // Update the brush transform
            FTransform BrushTransform;
            BrushTransform.SetLocation(NewLocation);
            BrushTransform.SetScale3D(NewExtent); // Use the extent directly as the scale
            BrushComponent->SetWorldTransform(BrushTransform);

            // Rebuild the brush collision
            BrushComponent->BuildSimpleBrushCollision();
            BrushComponent->ReregisterComponent();
        }

        // Get the navigation system and update the navigation bounds
        UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
        if (NavSys)
        {
            NavSys->OnNavigationBoundsUpdated(NavMeshVolume);
        }
    }
}

void AProceduralSpaceManager::GetActorMidpointAndSize(AActor* Actor, FVector& OutMidpoint, FVector& OutSize) const
{
    if (Actor)
    {
        FVector Origin, BoxExtent;
        Actor->GetActorBounds(false, Origin, BoxExtent);

        FVector Min = Origin - BoxExtent;
        FVector Max = Origin + BoxExtent;

        // Include bounds of attached actors
        TArray<AActor*> AttachedActors;
        Actor->GetAttachedActors(AttachedActors);
        for (AActor* AttachedActor : AttachedActors)
        {
            FVector AttachedOrigin, AttachedBoxExtent;
            AttachedActor->GetActorBounds(false, AttachedOrigin, AttachedBoxExtent);

            FVector AttachedMin = AttachedOrigin - AttachedBoxExtent;
            FVector AttachedMax = AttachedOrigin + AttachedBoxExtent;

            Min = Min.ComponentMin(AttachedMin);
            Max = Max.ComponentMax(AttachedMax);
        }

        OutMidpoint = (Min + Max) / 2;
        OutSize = Max - Min;
    }
    else
    {
        OutMidpoint = FVector::ZeroVector;
        OutSize = FVector::ZeroVector;
    }
}