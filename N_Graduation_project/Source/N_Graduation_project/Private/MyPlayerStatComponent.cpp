#include "MyPlayerStatComponent.h"
#include "N_Graduation_project/N_Graduation_projectCharacter.h"
#include "MyCharacterWidget.h"
#include "WidgetActor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "MyGameInstance.h"
UMyPlayerStatComponent::UMyPlayerStatComponent()
{
	CurrentMana = 10;
	NewMaxHP = 150;
	PastMaxHP = 150;
	CurrentHP = 150;
	PastCurrentHP = 150;
	MonsterName = "PlayerCharacter";
	Change = true;
	bIsFreezing = false;
	OriginalSpeed = 0.f;
}

UMyCharacterWidget* UMyPlayerStatComponent::GetHUD() const
{
	if(AActor* Owner = GetOwner())
	{
		if(UWidgetActor* WidgetActor = Owner->FindComponentByClass<UWidgetActor>())
		{
			return WidgetActor->GetHUDWidget();
		}
	}
	return nullptr;
}

void UMyPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UMyPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	if(ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner()))
	{
		OwnerPlayer = Cast<AN_Graduation_projectCharacter>(CharacterOwner);
	}

	UpdateHUD(); // ���� ���� �� HUD �ʱ�ȭ

}

void UMyPlayerStatComponent::SetHP(float NewHP)
{
	//	PastCurrentHP = CurrentHP;
	CurrentHP = FMath::Clamp(NewHP,0.0f,NewMaxHP);
	UpdateHUD();
	UE_LOG(LogTemp,Error,TEXT("Now Hp:%f"),NewHP);


	if(CurrentHP == 0)
	{
		OwnerPlayer->OnPlayerDead();
	}
}

void UMyPlayerStatComponent::SetMaxHp(int MaxHp)
{
	//PastMaxHP = NewMaxHP;
	NewMaxHP = MaxHp;
}

void UMyPlayerStatComponent::ApplyDamage(float DamageAmount)
{
	SetHP(CurrentHP - DamageAmount);
}

void UMyPlayerStatComponent::SetMana(int NewMana)
{
	CurrentMana = NewMana;
	UpdateHUD();
}

void UMyPlayerStatComponent::UseMana(int ManaAmount)
{
	if(CurrentMana >= ManaAmount)
	{
		SetMana(CurrentMana - ManaAmount);
	}
	else 		UE_LOG(LogTemp,Error,TEXT("마나가 부족합니다"));

}

void UMyPlayerStatComponent::RegenerateMana()
{
	if(CurrentMana < 10)
	{
		SetMana(CurrentMana + 1);
	}
	if(CurrentMana >= 2) {
		Change = true;
	}
}

void UMyPlayerStatComponent::TransformToEntity(FString Name,int HP,int Mana)
{
	auto* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(!MyGameInstance) return;
	UE_LOG(LogTemp,Error,TEXT("Loadgame TransformToEntity:%s, %d, %d"),*Name,HP,Mana);

	if(CurrentMana >= Mana)
	{
		MyGameInstance->PlayerFullHP=HP;
		Change = true;
		PastMaxHP = NewMaxHP;
		PastCurrentHP = CurrentHP;
		UE_LOG(LogTemp,Log,TEXT("maxhp %f %f "),PastCurrentHP,PastMaxHP);
		if(CurrentHP<=0){
			CurrentHP=150;
		}
		if(UMyCharacterWidget* HUD = GetHUD())
		{
			GetWorld()->GetTimerManager().SetTimer(ManaRegenTimerHandle,this,&UMyPlayerStatComponent::RegenerateMana,4.0f,true);

			MonsterName = Name;
			HUD->SkillName = MonsterName;
			HUD->SetSkillIcon();
			HUD->ChangeIcon(MonsterName);

			HUD->PassedTimeNomal = 0.0f;
			HUD->PassedTimeSpecial = 0.0f;
			HUD->SkillCoolTimeNomal = 0.0f;
			HUD->SkillCoolTimeSpecial = 0.0f;
			HUD->CanNomal = true;
			HUD->CanSpecial = true;

			HUD->UpdateNomalSkillCooldown(0.0f,true,false);
			HUD->UpdateSpecialSkillCooldown(0.0f,false,true);
		}


		UE_LOG(LogTemp,Log,TEXT("maxhp2 %f %f %d "),PastCurrentHP,PastMaxHP,NewMaxHP);
		if(PastCurrentHP == PastMaxHP)
		{
			SetMaxHp(HP);
			SetHP(HP);
		} else
		{
			// 변신 전 HP 비율을 유지
			float HPPercent = PastCurrentHP / PastMaxHP;
			float NewHP = HPPercent * HP;

			SetMaxHp(HP);
			SetHP(FMath::CeilToFloat(NewHP));
		}

		UseMana(Mana);
	} else
	{
		Change = false;
}
}

void UMyPlayerStatComponent::UpdateHUD()
{
	if(UMyCharacterWidget* HUD = GetHUD())
	{
		HUD->UpdateHPBar(CurrentHP,NewMaxHP);
		HUD->UpdateMana(CurrentMana);
		HUD->ChangeIcon(MonsterName);
	}
}

