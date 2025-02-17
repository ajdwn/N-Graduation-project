#include "ABGameSingleton.h"

DEFINE_LOG_CATEGORY(LogABGameSingleton);

UABGameSingleton::UABGameSingleton()
{
	// 만든 DataTable 주소를 가져온다.
	// DataTable은 맵 형태로 Key,Value 값으로 들어온다.
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Game/DataTable/EntityDataTable.EntityDataTable"));
	if (nullptr != DataTableRef.Object)
	{
		// 갯수가 맞는지 체크
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		// Key값은 순차적으로 오기 때문에 Key값은 필요없고, Value값만 Array에 저장
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
	*/ //잘 출력됨
	// 배열의 갯수가 0보다 큰지 확인
	HowManyEntity = EntityDataTable.Num();
	// EntityDataTable에 저장된 데이터를 콘솔에 출력
	ensure(HowManyEntity > 0);
	//UE_LOG(LogABGameSingleton, Error, TEXT("HowManyEntity: %d"), HowManyEntity);
	//-> LogABGameSingleton: Error: HowManyEntity: 7
}

// Singleton Get() 함수
UABGameSingleton& UABGameSingleton::Get()
{
	// CastChecked로 강력하게 검사, GEngine에 있는 아까 적용한 GameSingleton을 가져오기
	UABGameSingleton* Singleton = CastChecked<UABGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}
	// 혹시 몰라서 만약 Singleton이 null 값이라면 에러를 띄우도록 함
	// 코드의 흐름을 위해서 return값의 인스턴스를 생성하고 리턴함
	UE_LOG(LogABGameSingleton, Error, TEXT("Invalide Game Singleton"));
	return *NewObject<UABGameSingleton>();
}
