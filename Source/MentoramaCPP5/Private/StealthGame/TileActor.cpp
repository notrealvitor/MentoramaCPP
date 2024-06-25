#include "StealthGame/TileActor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Util/ColorConstants.h"

// Sets default values
ATileActor::ATileActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Index = -1;

	// Initialize the root scene component
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	// Initialize the static mesh component and attach it to the root component
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	DebugColor = FLinearColor::Black;
}

// Called when the game starts or when spawned
void ATileActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATileActor::SetTileColor(const FLinearColor& Color)
{
	if (StaticMeshComponent)
	{
		UMaterialInstanceDynamic* DynMaterial = StaticMeshComponent->CreateAndSetMaterialInstanceDynamic(0);
		if (DynMaterial)
		{	if (ShowDebugColor)
			{
				DynMaterial->SetVectorParameterValue("SurfaceColor", Color);				
			}
			DebugColor = Color;
		}
	}
}