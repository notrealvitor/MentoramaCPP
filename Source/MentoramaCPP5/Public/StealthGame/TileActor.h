#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTileActivated);

UCLASS()
class MENTORAMACPP5_API ATileActor : public AActor
{
	GENERATED_BODY()
    
public:    
	ATileActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tile Settings")
	int32 Index;

	UPROPERTY(BlueprintReadOnly, Category="Tile Settings")
	FString TileType;

	UPROPERTY(BlueprintReadOnly, Category="Tile Settings")
	FLinearColor DebugColor; //this is not only for debug, I ended up using it for the reference of the side of the wall in the manager

	UPROPERTY(BlueprintReadWrite)
	bool ShowDebugColor = false;
	
	void SetTileColor(const FLinearColor& Color);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnTileActivated OnTileActivated; //Made this his to be activated in BP

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateTile();
	

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
};