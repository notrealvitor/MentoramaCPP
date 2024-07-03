#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UCounterWidget.generated.h"

UENUM(BlueprintType)
enum class EDisplayType : uint8
{
    DT_Time       UMETA(DisplayName = "Time (00:00:00)"),
    DT_Standard   UMETA(DisplayName = "Standard (0000)"),
    DT_Ratio      UMETA(DisplayName = "Ratio (0/0)")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCounterEnded);

UCLASS()
class MENTORAMACPP5_API UCounterWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
    EDisplayType DisplayType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
    int32 Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter", meta = (EditCondition = "DisplayType == EDisplayType::DT_Ratio"))
    int32 ValueMax;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
    float IncreaseRatio = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
    int32 MillisecondsPerPoint; // Time type: milliseconds per score point

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
    int32 MaxBonus; // Ratio type: bonus points for max/max

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
    float ScorePerValue; // Multiplier for the value

    UPROPERTY(BlueprintAssignable, Category = "Counter")
    FOnCounterEnded OnCounterEnded;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CounterText;

    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable, Category = "Counter")
    void UpdateDisplayTypeDetails();

    UFUNCTION(BlueprintCallable, Category = "Counter")
    void SetValue(int32 NewValue);

    UFUNCTION(BlueprintCallable, Category = "Counter")
    void StartCounter(float UpdateInterval);

    UFUNCTION(BlueprintCallable, Category = "Counter")
    int32 CalculateScore() const;

    UPROPERTY(BlueprintReadOnly, Category = "Counter")
    int TargetValue;

private:
    FTimerHandle CounterTimerHandle;
    void UpdateCounter();

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};