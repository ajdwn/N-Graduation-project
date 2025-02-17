// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABEntityDataComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPZeroDelegate); // Hp가 0일때, 죽었다라는 시그널의 델리게이트
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHPChangedDelegate, float /*CurrentHp*/); // HP가 변경될 때마다 구독한 객체들에게 현재 체력을 넘겨줌

// ClassGroup = (Custom) : 클래스가 언리얼 에디터의 클래스 브라우저에게 어떤 그룹에 속할지 지정하는데 
// Custom으로 하면 사용자 정의 클래스를 Custom 그룹에 속하게 되어 클래스 브라우저에서 쉽게 식별할 수 있음
// meta를 BlueprintSpawnableComponent를 지정하면 이 클래스가 블루프린트에서 스폰될 수 있음
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
	// 델리게이트 변수 선언
	FOnHPZeroDelegate OnHPZero;
	FOnHPChangedDelegate OnHPChanged;

	FORCEINLINE float GetMaxHp() { return MaxHP; }
	FORCEINLINE float GetCurrentHp() { return CurrentHP; }
	float ApplyDamage(float InDamage);

	float GetHpPercentage() const; // 현재 Hp 비율 계산
	void TransformEntity(float NewMaxHp); // 변신 후 Hp 비율을 적용

protected:
	void SetHP(float NewHP);

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float MaxHP;

};

