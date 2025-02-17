#include "ABGameSingleton.h"

DEFINE_LOG_CATEGORY(LogABGameSingleton);

UABGameSingleton::UABGameSingleton()
{
	// ���� DataTable �ּҸ� �����´�.
	// DataTable�� �� ���·� Key,Value ������ ���´�.
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Game/DataTable/EntityDataTable.EntityDataTable"));
	if (nullptr != DataTableRef.Object)
	{
		// ������ �´��� üũ
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		// Key���� ���������� ���� ������ Key���� �ʿ����, Value���� Array�� ����
		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, EntityDataTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FABEntityData*>(Value);
			}
		);
	}
	/*	
	for (const FABEntityData& EntityData : EntityDataTable)
		{
			UE_LOG(LogABGameSingleton, Error, TEXT("Entity Name: %s, HP: %d, Move Speed: %d, Normal Skill: %s, Special Skill: %s"),
				*EntityData.EntityName, EntityData.HP, EntityData.MoveSpeed, *EntityData.NormalSkill, *EntityData.SpecialSkill);
		}
	*/ //�� ��µ�
	// �迭�� ������ 0���� ū�� Ȯ��
	HowManyEntity = EntityDataTable.Num();
	// EntityDataTable�� ����� �����͸� �ֿܼ� ���
	ensure(HowManyEntity > 0);
	//UE_LOG(LogABGameSingleton, Error, TEXT("HowManyEntity: %d"), HowManyEntity);
	//-> LogABGameSingleton: Error: HowManyEntity: 7
}

// Singleton Get() �Լ�
UABGameSingleton& UABGameSingleton::Get()
{
	// CastChecked�� �����ϰ� �˻�, GEngine�� �ִ� �Ʊ� ������ GameSingleton�� ��������
	UABGameSingleton* Singleton = CastChecked<UABGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}
	// Ȥ�� ���� ���� Singleton�� null ���̶�� ������ ��쵵�� ��
	// �ڵ��� �帧�� ���ؼ� return���� �ν��Ͻ��� �����ϰ� ������
	UE_LOG(LogABGameSingleton, Error, TEXT("Invalide Game Singleton"));
	return *NewObject<UABGameSingleton>();
}
