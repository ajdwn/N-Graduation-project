// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABEntityData.h" // Entity Data 구조체
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

	// 블루프린트에서 설정할 GroupID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString EntityGroupID;

	// ABEntityData 구조체 사용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FABEntityData EntityData;

	// 설정한 GroupID를 키 값으로 가져온 데이터를 적용하는 함수
	UFUNCTION(BlueprintCallable, Category = "Data")
	void UpdateEntityData();

};
