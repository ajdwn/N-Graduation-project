#include "EntityWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UEntityWidget::UpdateHealthBar(int32 NewHealth)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(FMath::Clamp(NewHealth / NewHealth, 0.0f, 1.0f));
       // GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Health updated: %d"), NewHealth));
    }
}

void UEntityWidget::SetEntityName(FText NewName)
{
    if (EntityName)
    {
        EntityName->SetText(NewName);
       // GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Name: %s"), *NewName.ToString()));
    }
}
