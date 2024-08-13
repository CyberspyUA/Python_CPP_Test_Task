// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProcedularWall.generated.h"

UCLASS()
class CPPDEVELOPERTESTTASK_API AProcedularWall : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
public:	
	// Sets default values for this actor's properties
	AProcedularWall();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GenerateWallMesh();
	void GenerateWindowExcluded();
	void GenerateWindowMesh();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProceduralMeshComponent* ProceduralMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Wall", meta = (MultiLine = "true"))
	float WallLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Wall", meta = (MultiLine = "true"))
	float WallHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Wall", meta = (MultiLine = "true"))
	float WallWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Wall", meta = (MultiLine = "true"))
	UMaterialInstance* WallMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Window", meta = (MultiLine = "true"))
	float WindowLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Window", meta = (MultiLine = "true"))
	float WindowHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Window", meta = (MultiLine = "true"))
	float XAxisWindowIndentation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Window", meta = (MultiLine = "true"))
	float ZAxisWindowIndentation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Window", meta = (MultiLine = "true"))
	int32 NumberOfWindows;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Window", meta = (MultiLine = "true"))
	UMaterialInstance* WindowMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Window", meta = (MultiLine = "true"))
	bool bMakeExclusion;
	
};
