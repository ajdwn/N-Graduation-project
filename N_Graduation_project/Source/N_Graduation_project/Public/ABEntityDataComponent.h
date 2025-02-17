// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABEntityDataComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate); // Hp�� 0�϶�, �׾��ٶ�� �ñ׳��� ��������Ʈ
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float /*CurrentHp*/); // HP�� ����� ������ ������ ��ü�鿡�� ���� ü���� �Ѱ���

// ClassGroup = (Custom) : Ŭ������ �𸮾� �������� Ŭ���� ���������� � �׷쿡 ������ �����ϴµ� 
// Custom���� �ϸ� ����� ���� Ŭ������ Custom �׷쿡 ���ϰ� �Ǿ� Ŭ���� ���������� ���� �ĺ��� �� ����
// meta�� BlueprintSpawnableComponent�� �����ϸ� �� Ŭ������ �������Ʈ���� ������ �� ����
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class N_GRADUATION_PROJECT_API UABEntityDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UABEntityDataComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// ��������Ʈ ���� ����
	FOnHPZeroDelegate OnHPZero;
	FOnHPChangedDelegate OnHPChanged;

	FORCEINLINE float GetMaxHp() { return MaxHP; }
	FORCEINLINE float GetCurrentHp() { return CurrentHP; }
	float ApplyDamage(float InDamage);

	float GetHpPercentage() const; // ���� Hp ���� ���
	void TransformEntity(float NewMaxHp); // ���� �� Hp ������ ����

protected:
	void SetHP(float NewHP);

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float MaxHP;

};

