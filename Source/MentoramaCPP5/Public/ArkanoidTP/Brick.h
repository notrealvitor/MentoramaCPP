// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBrickHit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBrickDestroyed, class ABrick*, brick);

UCLASS()
class MENTORAMACPP5_API ABrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrick();

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
	UPROPERTY(BlueprintReadWrite)
	int Health;
	
	UPROPERTY(BlueprintAssignable)
	FOnBrickHit	OnBrickHit;
	
	UFUNCTION(BlueprintImplementableEvent)
	void DestroyFeedback();
	
	UPROPERTY(BlueprintAssignable)
	FOnBrickDestroyed OnBrickDestroyed;

	UFUNCTION(BlueprintCallable) //calling this in the editor is causing some terrible editor corruption (I was calling it after the destroy)
	int GetScoreValue();
	
	UPROPERTY(BlueprintReadWrite)
	float TimeForFeedbackDestroy = 0.1f;
};
