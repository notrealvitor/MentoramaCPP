#include "ArkanoidTP/Brick.h"

#include "ArkanoidTP/Ball.h"

ABrick::ABrick()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABrick::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	
	ABall* HitBall = Cast<ABall>(Other);
	Health = Health - HitBall->BallDamage;
	OnBrickHit.Broadcast();
	
	if(Health<=0)
	{
		OnBrickDestroyed.Broadcast(this);
		DestroyFeedback();
		if(TimeForFeedbackDestroy > 0)
		{
			SetLifeSpan(TimeForFeedbackDestroy);
		}
		else
		{
			Destroy();
		}
	}
}

int ABrick::GetScoreValue()
{
	return 10;
}



