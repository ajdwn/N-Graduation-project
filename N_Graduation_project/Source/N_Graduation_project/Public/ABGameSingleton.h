// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ABEntityData.h" //Entity������ ����������(Entity Data ����ü)
#include "SkillData.h" //SkillData������ ����������
#include "SkillEffectData.h" //SkillEffectData������ ����������
#include "ABGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogABGameSingleton, Error, All);

UCLASS()
class N_GRADUATION_PROJECT_API UABGameSingleton : public UObject
{
	GENERATED_BODY()

public:
	UABGameSingleton();
	static UABGameSingleton& Get();
	//~ABGameSingleton();

	// Get�Լ�, ���� ��ȿ�ϸ� ����, �ƴϸ� �׳� �⺻ �����ڸ� ���� �Ѱ��ֵ��� ����
	FORCEINLINE FABEntityData GetCharacterStat(int32 ID) const
	{
		return EntityDataTable.IsValidIndex(ID - 1) ? EntityDataTable[ID - 1] : FABEntityData();
	}

	// EntityGroupID�� �������� �����͸� �������� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Data")
	bool GetEntityDataByGroupID(const FString& GroupID, FABEntityData& OutEntityData) const;

	UPROPERTY()
	// �� ��� Entity?
	int32 HowManyEntity;
	int32 HowManySkill;
	int32 HowManySkillEffect;

private:
	TArray<FABEntityData> EntityDataTable; // ���̺���� ���������� �����ؼ� �ʿ��� ���� ��ü�鿡�� �����ϱ� ���� Talbe Array
	TMap<FString, FABEntityData> EntityDataMap; // EntityGroupID�� Ű ������ �����͸� �����ϴ� Map
	
	TArray<FSkillData> SkillDataTable; // ���̺���� ���������� �����ؼ� �ʿ��� ���� ��ü�鿡�� �����ϱ� ���� Talbe Array
	//TMap<FString, FSkillData> FSkillDataMap;

	TArray<FSkillEffectData> SkillEffectDataTable; // ���̺���� ���������� �����ؼ� �ʿ��� ���� ��ü�鿡�� �����ϱ� ���� Talbe Array
	//TMap<FString, FSkillEffectData> FSkillEffectDataMap;
};
