// Fill out your copyright notice in the Description page of Project Settings.


#include "Tester.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"
#include "EntityWidget.h"

// Sets default values
ATester::ATester()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// UStaticMeshComponent�� �����ڿ��� CreateDefaultSubobject�� ����
	// �����ڿ��� �̸� ��������� nullptr ������ ���� ���� 
	m_pMeshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	// RootComponent ���� -> �� �ϸ� m_pMeshCom nullptr ���� �߻�
	if (!m_pMeshCom)
	{
		m_pMeshCom = NewObject<UStaticMeshComponent>(this, TEXT("MeshComponent"));
		m_pMeshCom->RegisterComponent();
		RootComponent = m_pMeshCom;
	}
}

// Called when the game starts or when spawned
void ATester::BeginPlay()
{
	Super::BeginPlay();

	if (!m_pMeshCom)
	{
		m_pMeshCom = NewObject<UStaticMeshComponent>(this, TEXT("MeshComponent"));
		m_pMeshCom->RegisterComponent();
		RootComponent = m_pMeshCom;
	}

	UpdateEntityData();
	SpawnEntityPreset();
}

// Called every frame
void ATester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATester::UpdateEntityData()
{
	if (UABGameSingleton::Get().GetEntityDataByGroupID(EntityGroupID, EntityData))
	{
		SetActorLabel(EntityData.EntityName);
		SetMaxHp(EntityData.HP);
		SetMoveSpeed(EntityData.MoveSpeed);
		SetPreset(EntityData.PresetReference);

		UE_LOG(LogABGameSingleton, Error, TEXT("Entity Name: %s, HP: %d, Move Speed: %d"),
			*EntityData.EntityName, EntityData.HP, EntityData.MoveSpeed);

		//SpawnEntityPreset();
	}

}
/*void ATester::SpawnEntityPreset()
{
	//null���� ���� null Ȯ�� �ڵ� �ʿ�(���ϲ��ϱ�)
	//�ι�° ������� ��������
	if (EntityPresetClass)
	{
		AActor* SpawnedEntityPreset = GetWorld()->SpawnActor<AActor>(EntityPresetClass, GetActorLocation(), GetActorRotation());
		// EntityPreset���� WidgetComponent�� ����
		if (UWidgetComponent* WidgetComponent = SpawnedEntityPreset->FindComponentByClass<UWidgetComponent>())
		{
			if (UEntityWidget* MyEntityWidget = Cast<UEntityWidget>(WidgetComponent->GetWidget()))
			{
				MyEntityWidget->UpdateHealthBar(EntityData.HP);
				MyEntityWidget->SetEntityName(FText::FromString(EntityData.EntityName));
			}
		}
	}
}
*/

void ATester::SpawnEntityPreset()
{
	if (EntityPresetClass)
	{
		AActor* SpawnedEntityPreset = GetWorld()->SpawnActor<AActor>(EntityPresetClass, GetActorLocation(), GetActorRotation());

		if (SpawnedEntityPreset)
		{
			// UWidgetComponent�� null�̸� �������� �ʱ�ȭ
			UWidgetComponent* WidgetComponent = SpawnedEntityPreset->FindComponentByClass<UWidgetComponent>();

			if (!WidgetComponent)
			{
				// UWidgetComponent�� ������ ���ο� ������Ʈ�� �߰�
				WidgetComponent = NewObject<UWidgetComponent>(SpawnedEntityPreset);
				if (WidgetComponent)
				{
					// WidgetComponent�� �θ� ÷���ϰ� ���
					WidgetComponent->SetupAttachment(SpawnedEntityPreset->GetRootComponent()); // �θ� ������Ʈ�� ÷��
					WidgetComponent->RegisterComponent();  // ������Ʈ�� ���忡 ���
				}
			}

			// WidgetComponent�� ����� �ʱ�ȭ�Ǿ����� Ȯ��
			if (WidgetComponent)
			{
				// ������ �����ͼ� ������Ʈ
				UUserWidget* UserWidget = WidgetComponent->GetWidget();
				if (UEntityWidget* MyEntityWidget = Cast<UEntityWidget>(UserWidget))
				{
					// �������� ������ ����
					MyEntityWidget->UpdateHealthBar(EntityData.HP);
					MyEntityWidget->SetEntityName(FText::FromString(EntityData.EntityName));
				}
				else
				{
					// UEntityWidget���� ĳ���� ���� ��, �α׸� ������� �ʰ� ó���� ����.
				}
			}
			else
			{
				// WidgetComponent�� null�� ���
			}
		}
		else
		{
			// Spawn�� EntityPreset�� ��ȿ���� ���� (null�� ���)
		}
	}
	else
	{
		// EntityPresetClass�� null�� ���
	}
}



void ATester::SetMaxHp(int32 MaxHp)
{
	currentHp = MaxHp;
}

void ATester::SetMoveSpeed(int32 MoveSpeed)
{
	currentSpeed = MoveSpeed;
}

void ATester::SetPreset(FString PresetReference)
{
	currentPreset = PresetReference;

	// ������ �̸����� �޽� ���� ���� �Ҵ�
	if (currentPreset == "PCPreset.uasset")
	{
		// �𸮾� ������ ���������� ���� ���� ��Ŭ�� ->  !!���۷���!! ���� -> �ؽ�Ʈ�� �־��ֱ�

		// FObjectFinder�� �ݵ�� �����ڿ����� ��� ����, �Լ� ������ ����� �� �ٷ� ũ���� �߻�
		//ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));
		/*if (BodyMesh.Succeeded())
		{

		}*/
		//m_pMeshCom->SetStaticMesh(BodyMesh.Object);
		//RootComponent = m_pMeshCom;

		//FString MeshPath = TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'");
		//UStaticMesh* LoadedMesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);

		// ������ ���� �� �������� �޽ø� �ε��ϱ� ���� FSoftObjectPath�� ����� �񵿱� �ε� 
		FSoftObjectPath MeshPath(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));

		UStaticMesh* LoadedMesh = Cast<UStaticMesh>(MeshPath.TryLoad());
		if (LoadedMesh)
		{
			// ���̷�Ż �޽ø� ����� ��� SetSkeletalMesh() ���
			m_pMeshCom->SetStaticMesh(LoadedMesh);
		}
	}


	if (currentPreset == "WildBoarPreset.uasset")
	{
		FSoftObjectPath MeshPath(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Bush.SM_Bush'"));

		UStaticMesh* LoadedMesh = Cast<UStaticMesh>(MeshPath.TryLoad());
		if (LoadedMesh)
		{
			m_pMeshCom->SetStaticMesh(LoadedMesh);
		}
	}

	if (currentPreset == "InpermonPreset.uasset")
	{
		FSoftObjectPath MeshPath(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_TableRound.SM_TableRound'"));

		UStaticMesh* LoadedMesh = Cast<UStaticMesh>(MeshPath.TryLoad());
		if (LoadedMesh)
		{
			m_pMeshCom->SetStaticMesh(LoadedMesh);
		}
	}

	if (currentPreset == "FreezardPreset.uasset")
	{
		FSoftObjectPath MeshPath(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Statue.SM_Statue'"));

		UStaticMesh* LoadedMesh = Cast<UStaticMesh>(MeshPath.TryLoad());
		if (LoadedMesh)
		{
			m_pMeshCom->SetStaticMesh(LoadedMesh);
		}
	}

	if (currentPreset == "StoneGolemPreset.uasset")
	{
		FSoftObjectPath MeshPath(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Lamp_Ceiling.SM_Lamp_Ceiling'"));

		UStaticMesh* LoadedMesh = Cast<UStaticMesh>(MeshPath.TryLoad());
		if (LoadedMesh)
		{
			m_pMeshCom->SetStaticMesh(LoadedMesh);
		}
	}
}


