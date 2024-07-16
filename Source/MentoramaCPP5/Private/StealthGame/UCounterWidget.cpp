#include "StealthGame/UCounterWidget.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "Logging/LogMacros.h"

void UCounterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Ensure CounterText is valid before proceeding
    if (!CounterText)
    {
        UE_LOG(LogTemp, Error, TEXT("CounterText is null. Ensure it is properly bound in the UMG editor."));
        return;
    }

    // Initialize widget based on display type
    UpdateDisplayTypeDetails();
}

void UCounterWidget::SetValue(int32 NewValue)
{
    Value = NewValue;
    TargetValue = Value;
    UpdateDisplayTypeDetails();
}

void UCounterWidget::UpdateDisplayTypeDetails()
{
    if (!CounterText)
    {
        UE_LOG(LogTemp, Error, TEXT("CounterText is null. Cannot update display details."));
        return;
    }

    FString DisplayText;

    switch (DisplayType)
    {
    case EDisplayType::DT_Time:
    {
        // Convert Value (in milliseconds) to time format
        int32 TotalMilliseconds = (Value % 1000) / 10;
        int32 TotalSeconds = Value / 1000;
        int32 Minutes = TotalSeconds / 60;
        int32 Seconds = TotalSeconds % 60;
        DisplayText = FString::Printf(TEXT("%02d:%02d:%02d"), Minutes, Seconds, TotalMilliseconds);
        //UE_LOG(LogTemp, Warning, TEXT("Current Value: %d to TIME: %d:%02d:%02d"), Value, Minutes, Seconds, TotalMilliseconds);
        break;
    }
case EDisplayType::DT_Standard:
    {
        // Display as a standard number
        DisplayText = FString::Printf(TEXT("%d"), Value);
        break;
    }
    case EDisplayType::DT_Ratio:
    {
        // Display as a ratio
        DisplayText = FString::Printf(TEXT("%d/%d"), Value, ValueMax);
        break;
    }
    default:
        break;
    }

    CounterText->SetText(FText::FromString(DisplayText));
}

void UCounterWidget::StartCounter(float UpdateInterval)
{
    // Start or resume the counter with the specified update interval
    TargetValue = Value;
    Value = 0;
    GetWorld()->GetTimerManager().SetTimer(CounterTimerHandle, this, &UCounterWidget::UpdateCounter, UpdateInterval / 1000.0f, true);
}

void UCounterWidget::UpdateCounter()
{
    //UE_LOG(LogTemp, Log, TEXT("UpdateCounter called. Current Value: %d, IncreaseRatio: %f, TargetValue: %d"), Value, IncreaseRatio, TargetValue);

    if (FMath::Abs(IncreaseRatio) < KINDA_SMALL_NUMBER)
    {
        GetWorld()->GetTimerManager().ClearTimer(CounterTimerHandle);
        UE_LOG(LogTemp, Warning, TEXT("Increase ratios is too low: %f. UpdateCounter not updating"), IncreaseRatio);
        OnCounterEnded.Broadcast(); // Broadcast the delegate
        return;
    }

    Value += FMath::RoundToInt(IncreaseRatio); // Update value according to IncreaseRatio
    UpdateDisplayTypeDetails();

    // Stop the counter if it reaches the boundary conditions
    if ((IncreaseRatio > 0 && Value >= TargetValue) || (IncreaseRatio < 0 && Value <= 0))
    {
        GetWorld()->GetTimerManager().ClearTimer(CounterTimerHandle);
        UE_LOG(LogTemp, Warning, TEXT("Update counter ending"));
        OnCounterEnded.Broadcast(); // Broadcast the delegate
    }
}

int32 UCounterWidget::CalculateScore() const
{
    int32 Score = 0;

    switch (DisplayType)
    {
    case EDisplayType::DT_Time:
    {
        // Calculate score based on the number of milliseconds per point
        Score = TargetValue / MillisecondsPerPoint;
        break;
    }
    case EDisplayType::DT_Standard:
    {
        // Standard score is Value * ScorePerValue
        Score = TargetValue * ScorePerValue;
        break;
    }
    case EDisplayType::DT_Ratio:
    {
        // Calculate score based on the ratio and multiply by ScorePerValue
        Score = TargetValue * ScorePerValue;
        if (TargetValue == ValueMax)
        {
            Score += MaxBonus; // Add bonus if min equals max
        }
        break;
    }
    default:
        break;
    }

    return Score;
}

#if WITH_EDITOR
void UCounterWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    UpdateDisplayTypeDetails();
}
#endif