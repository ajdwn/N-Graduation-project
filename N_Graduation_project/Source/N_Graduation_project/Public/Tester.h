// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABEntityData.h" // Entity Data ����ü
#include "ABGameSingleton.h"
#include "Tester.generated.h"

UCLASS()
class N_GRADUATION_PROJECT_API ATester : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATester();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// �������Ʈ���� ������ GroupID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString EntityGroupID;

	// ABEntityData ����ü ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FABEntityData EntityData;

	// ������ GroupID�� Ű ������ ������ �����͸� �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Data")
	void UpdateEntityData();

};
