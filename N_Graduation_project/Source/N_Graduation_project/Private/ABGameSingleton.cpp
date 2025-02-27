#include "ABGameSingleton.h"

DEFINE_LOG_CATEGORY(LogABGameSingleton);

UABGameSingleton::UABGameSingleton()
{
	// ���� DataTable �ּҸ� �����´�.
	// DataTable�� �� ���·� Key,Value ������ ���´�.
	static ConstructorHelpers::FObjectFinder<UDataTable> EntityDataTableRef(TEXT("/Game/DataTable/EntityDataTable.EntityDataTable"));
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataTableRef(TEXT("/Game/DataTable/SkillData.SkillData"));
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillEffectDataTableRef(TEXT("/Game/DataTable/SkillEffectData.SkillEffectData"));

	//if (nullptr != DataTableRef.Object)
	//{
	//	// ������ �´��� üũ
	//	const UDataTable* DataTable = DataTableRef.Object;
	//	check(DataTable->GetRowMap().Num() > 0);
	//	// Key���� ���������� ���� ������ Key���� �ʿ����, Value���� Array�� ����
	//	TArray<uint8*> ValueArray;
	//	DataTable->GetRowMap().GenerateValueArray(ValueArray);
	//	Algo::Transform(ValueArray, EntityDataTable,
	//		[](uint8* Value)
	//		{
	//			return *reinterpret_cast<FABEntityData*>(Value);
	//		}
	//	);
	//}

	// DataTable, DataMap�� ������ ����
	if (EntityDataTableRef.Succeeded())
	{
		UDataTable* DataTable = EntityDataTableRef.Object;
		TArray<FABEntityData*> Rows;
		DataTable->GetAllRows<FABEntityData>(TEXT(""), Rows);

		for (FABEntityData* Row : Rows)
		{
			EntityDataTable.Add(*Row);
			EntityDataMap.Add(Row->EntityGroupID, *Row);
		}
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
	

	// DataTable, DataMap�� ������ ����
	if (SkillDataTableRef.Succeeded())
	{
		UDataTable* DataTable = SkillDataTableRef.Object;
		TArray<FSkillData*> Rows;
		DataTable->GetAllRows<FSkillData>(TEXT(""), Rows);

		for (FSkillData* Row : Rows)
		{
			SkillDataTable.Add(*Row);
			//FSkillDataMap.Add(Row->EntityGroupID, *Row);
		}
	}

	// Ȯ�� �Ϸ� 
	//for (const FSkillData& SkillData : SkillDataTable)
	//{
	//	UE_LOG(LogABGameSingleton, Error, TEXT("SkillID: %s, SkillName: %s, SkillType: %s, SkillRange: %d, SkillDuration: %.1f, SkillCoolTime: %.1f, SkillTypeShape: %s, SkillTypeSizeX: %d, SkillTypeSizeY: %d, ProjectileSpeed: %d"),
	//		*SkillData.SkillID, *SkillData.SkillName, *SkillData.SkillType, SkillData.SkillRange, SkillData.SkillDuration, SkillData.SkillCoolTime, *SkillData.SkillTypeShape, SkillData.SkillTypeSizeX, SkillData.SkillTypeSizeY, SkillData.ProjectileSpeed);
	//}
	
	// �迭�� ������ 0���� ū�� Ȯ��
	HowManySkill = SkillDataTable.Num();
	// SkillDataTable�� ����� �����͸� �ֿܼ� ���
	ensure(HowManySkill > 0);
	UE_LOG(LogABGameSingleton, Error, TEXT("HowManySkill: %d"), HowManySkill);


	// DataTable, DataMap�� ������ ����
	if (SkillEffectDataTableRef.Succeeded())
	{
		UDataTable* DataTable = SkillEffectDataTableRef.Object;
		TArray<FSkillEffectData*> Rows;
		DataTable->GetAllRows<FSkillEffectData>(TEXT(""), Rows);

		for (FSkillEffectData* Row : Rows)
		{
			SkillEffectDataTable.Add(*Row);
			//SkillEffectDataMap.Add(Row->EntityGroupID, *Row);
		}
	}

	// Ȯ�� �Ϸ� 
	//for (const FSkillEffectData& SkillEffectData : SkillEffectDataTable)
	//{
	//	UE_LOG(LogABGameSingleton, Error, TEXT("SkillNameID: %s, EffectID: %s, EffectType: %s, EffectValue01: %.1f, EffectValue02: %.1f"),
	//		*SkillEffectData.SkillNameID, *SkillEffectData.EffectID, *SkillEffectData.EffectType, SkillEffectData.EffectValue01, SkillEffectData.EffectValue02);
	//}
	// �迭�� ������ 0���� ū�� Ȯ��
	HowManySkillEffect = SkillEffectDataTable.Num();
	// SkillDataTable�� ����� �����͸� �ֿܼ� ���
	ensure(HowManySkillEffect > 0);
	UE_LOG(LogABGameSingleton, Error, TEXT("HowManySkillEffect: %d"), HowManySkillEffect);
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

// Entity GroupID�� Ű ������ Data �˻� 
bool UABGameSingleton::GetEntityDataByGroupID(const FString& GroupID, FABEntityData& OutEntityData) const
{
	if (const FABEntityData* FoundData = EntityDataMap.Find(GroupID))
	{
		OutEntityData = *FoundData;
		return true;
	}
	return false;
}
