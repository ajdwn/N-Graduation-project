// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ABEntityData.h" //Entity������ ����������
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

public:
	// Get�Լ�, ���� ��ȿ�ϸ� ����, �ƴϸ� �׳� �⺻ �����ڸ� ���� �Ѱ��ֵ��� ����
	FORCEINLINE FABEntityData GetCharacterStat(int32 ID) const
	{
		return EntityDataTable.IsValidIndex(ID - 1) ? EntityDataTable[ID - 1] : FABEntityData();
	}

	UPROPERTY()
	// �� ��� Entity?
	int32 HowManyEntity;

private:
	TArray<FABEntityData> EntityDataTable; // ���̺���� ���������� �����ؼ� �ʿ��� ���� ��ü�鿡�� �����ϱ� ���� Talbe Array
};
