// Fill out your copyright notice in the Description page of Project Settings.


#include "ABEntityDataComponent.h"

// Sets default values for this component's properties
UABEntityDataComponent::UABEntityDataComponent()
{
	MaxHP = 200.0f;
	CurrentHP = MaxHP;

	bWantsInitializeComponent = true; // InitializeComponent�Լ��� ȣ�� �� �� �ֵ��� �ϱ� ���ؼ�
}

/*void UABEntityDataComponent::InitializeComponent()
{   //������ �����ֱ�� ���õ� �Լ�
	// BeginPlay �Լ� ������ ȣ���
	Super::InitializeComponent();
	SetHP(MaxHP);
}*/

// Called when the game starts
void UABEntityDataComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHP(MaxHP);
	
}

float UABEntityDataComponent::ApplyDamage(float InDamage)
{
	const float PrevHP = CurrentHP;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHP(PrevHP - ActualDamage);
	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		OnHPZero.Broadcast();
	}

	return ActualDamage;
}

void UABEntityDataComponent::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp<float>(NewHP, 0, MaxHP);
	OnHPChanged.Broadcast(CurrentHP);
}

float UABEntityDataComponent::GetHpPercentage() const
{   // ���� HP ������ ��� (0~1 ������ ��)
	if (MaxHP == 0)
	{
		return 0.0f;
	}
	return CurrentHP / MaxHP;
}
void UABEntityDataComponent::TransformEntity(float NewMaxHP)
{   // ���� �� ���ο� MaxHP�� ���� ���� HP�� �缳��

	// ���� HP ������ ���
	float HPPercentage = GetHpPercentage(); 

	// ���ο� MaxHP�� ���缭 �ٲ� CurrentHP�� ���
	float TransformedCurrentHP = NewMaxHP * HPPercentage;

	// �ٲ� CurrentHP ���� SetHP �Լ��� ����
	SetHP(TransformedCurrentHP);

	// �� MaxHP ������ ������Ʈ
	MaxHP = NewMaxHP;
}


