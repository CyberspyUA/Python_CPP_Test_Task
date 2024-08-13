// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedularWall.h"

// Sets default values
AProcedularWall::AProcedularWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProceduralMeshComp = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMeshComp"));
	RootComponent = ProceduralMeshComp;

	ProceduralMeshComp->SetVisibility(true);
    ProceduralMeshComp->SetCastShadow(true);

    // Ensure the component is visible in the editor
    ProceduralMeshComp->bVisibleInRayTracing = true;
    ProceduralMeshComp->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
    ProceduralMeshComp->SetGenerateOverlapEvents(true);

	WallLength = 1000.0f;
	WallHeight = 600.0f;
	WallWidth = 200.0f;
	WindowLength = 200.0f;
	WindowHeight = 150.0f;
	XAxisWindowIndentation = 300.0f;
    ZAxisWindowIndentation = 0.0f;
	NumberOfWindows = 1;
    bMakeExclusion = false;
}

// Called when the game starts or when spawned
void AProcedularWall::BeginPlay()
{
	Super::BeginPlay();
	GenerateWallMesh();
    GenerateWindowMesh();
}

// Called every frame
void AProcedularWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#if WITH_EDITOR
void AProcedularWall::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    if(bMakeExclusion)
	{
		GenerateWindowExcluded();
	}
	else
	{
		GenerateWallMesh();
		GenerateWindowMesh();
	}
    
}
#endif

void AProcedularWall::GenerateWallMesh()
{
	// Clear previous mesh data
    ProceduralMeshComp->ClearMeshSection(0);

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;


	float HalfWallWidth = WallWidth / 2.0f;
	//Vertices for the wall
	//Front face
	Vertices.Add(FVector(0, -HalfWallWidth, 0));
	Vertices.Add(FVector(WallLength, -HalfWallWidth, 0));
	Vertices.Add(FVector(WallLength, -HalfWallWidth, WallHeight));
	Vertices.Add(FVector(0, -HalfWallWidth, WallHeight));
	//Back face
	Vertices.Add(FVector(0, HalfWallWidth, 0));
	Vertices.Add(FVector(WallLength, HalfWallWidth, 0));
	Vertices.Add(FVector(WallLength, HalfWallWidth, WallHeight));
	Vertices.Add(FVector(0, HalfWallWidth, WallHeight));
	//Left face
    Vertices.Add(FVector(WallLength, -HalfWallWidth, 0));
    Vertices.Add(FVector(WallLength, HalfWallWidth, 0));
    Vertices.Add(FVector(WallLength, HalfWallWidth, WallHeight));
    Vertices.Add(FVector(WallLength, -HalfWallWidth, WallHeight));

    //Right face
    Vertices.Add(FVector(0, -HalfWallWidth, 0));
    Vertices.Add(FVector(0, HalfWallWidth, 0));
    Vertices.Add(FVector(0, HalfWallWidth, WallHeight));
    Vertices.Add(FVector(0, -HalfWallWidth, WallHeight));

    //Top face
    Vertices.Add(FVector(0, -HalfWallWidth, WallHeight));
    Vertices.Add(FVector(WallLength, -HalfWallWidth, WallHeight));
    Vertices.Add(FVector(WallLength, HalfWallWidth, WallHeight));
    Vertices.Add(FVector(0, HalfWallWidth, WallHeight));

    //Bottom face
    Vertices.Add(FVector(0, -HalfWallWidth, 0));
    Vertices.Add(FVector(WallLength, -HalfWallWidth, 0));
    Vertices.Add(FVector(WallLength, HalfWallWidth, 0));
    Vertices.Add(FVector(0, HalfWallWidth, 0));

	// Front face triangles
    Triangles.Add(0); Triangles.Add(2); Triangles.Add(1);
    Triangles.Add(0); Triangles.Add(3); Triangles.Add(2);

    // Back face triangles
    Triangles.Add(4); Triangles.Add(5); Triangles.Add(6);
    Triangles.Add(4); Triangles.Add(6); Triangles.Add(7);

    // Left face triangles
    Triangles.Add(8); Triangles.Add(10); Triangles.Add(9);
    Triangles.Add(8); Triangles.Add(11); Triangles.Add(10);

    // Right face triangles
    Triangles.Add(12); Triangles.Add(13); Triangles.Add(14);
    Triangles.Add(12); Triangles.Add(14); Triangles.Add(15);

    // Top face triangles
    Triangles.Add(16); Triangles.Add(18); Triangles.Add(17);
    Triangles.Add(16); Triangles.Add(19); Triangles.Add(18);

    // Bottom face triangles
    Triangles.Add(20); Triangles.Add(21); Triangles.Add(22);
    Triangles.Add(20); Triangles.Add(22); Triangles.Add(23);

    // Normals for each face
    Normals.Add(FVector(0, -1, 0)); // Front face
    Normals.Add(FVector(0, -1, 0));
    Normals.Add(FVector(0, -1, 0));
    Normals.Add(FVector(0, -1, 0));

    Normals.Add(FVector(0, 1, 0)); // Back face
    Normals.Add(FVector(0, 1, 0));
    Normals.Add(FVector(0, 1, 0));
    Normals.Add(FVector(0, 1, 0));

    Normals.Add(FVector(-1, 0, 0)); // Left face
    Normals.Add(FVector(-1, 0, 0));
    Normals.Add(FVector(-1, 0, 0));
    Normals.Add(FVector(-1, 0, 0));

    Normals.Add(FVector(1, 0, 0)); // Right face
    Normals.Add(FVector(1, 0, 0));
    Normals.Add(FVector(1, 0, 0));
    Normals.Add(FVector(1, 0, 0));

    Normals.Add(FVector(0, 0, 1)); // Top face
    Normals.Add(FVector(0, 0, 1));
    Normals.Add(FVector(0, 0, 1));
    Normals.Add(FVector(0, 0, 1));

    Normals.Add(FVector(0, 0, -1)); // Bottom face
    Normals.Add(FVector(0, 0, -1));
    Normals.Add(FVector(0, 0, -1));
    Normals.Add(FVector(0, 0, -1));

    // UVs (simple planar mapping)
    for (int32 i = 0; i < 6; ++i)
    {
        UVs.Add(FVector2D(0, 0));
        UVs.Add(FVector2D(1, 0));
        UVs.Add(FVector2D(1, 1));
        UVs.Add(FVector2D(0, 1));
    }
    ProceduralMeshComp->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, TArray<FColor>(), Tangents, true);
	

    // Assign a material if one is set
	if (WallMaterial)
	{
		ProceduralMeshComp->SetMaterial(0, WallMaterial);
        /*ProceduralMeshComp->SetMeshSectionVisible(0, true);*/
	}
    
}

void AProcedularWall::GenerateWindowExcluded()
{
    // Clear previous mesh data
    ProceduralMeshComp->ClearMeshSection(0);

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FProcMeshTangent> Tangents;

    float HalfWallWidth = WallWidth / 2.0f;
    float currentIndentationX = 0.0f;

    for (int32 windowIndex = 0; windowIndex <= NumberOfWindows; ++windowIndex)
    {
        float windowLeft = XAxisWindowIndentation + windowIndex * (WindowLength + XAxisWindowIndentation);
        float windowRight = windowLeft + WindowLength;
        float windowBottom = ZAxisWindowIndentation;
        float windowTop = windowBottom + WindowHeight;

        if (windowIndex == NumberOfWindows || windowRight > WallLength)
        {
            windowLeft = WallLength;  // End the wall segment at the end of the wall
            windowRight = WallLength;
        }

        // Create the wall segment up to the start of the window
        if (currentIndentationX < windowLeft)
        {
            // Front face
            Vertices.Add(FVector(currentIndentationX, -HalfWallWidth, 0));               // Bottom Left
            Vertices.Add(FVector(windowLeft, -HalfWallWidth, 0));                        // Bottom Right
            Vertices.Add(FVector(windowLeft, -HalfWallWidth, WallHeight));               // Top Right
            Vertices.Add(FVector(currentIndentationX, -HalfWallWidth, WallHeight));      // Top Left

            // Back face
            Vertices.Add(FVector(currentIndentationX, HalfWallWidth, 0));                // Bottom Left
            Vertices.Add(FVector(windowLeft, HalfWallWidth, 0));                         // Bottom Right
            Vertices.Add(FVector(windowLeft, HalfWallWidth, WallHeight));                // Top Right
            Vertices.Add(FVector(currentIndentationX, HalfWallWidth, WallHeight));       // Top Left

            int32 BaseIndex = Vertices.Num() - 8;

            // Front face triangles
            Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 2); Triangles.Add(BaseIndex + 1);
            Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 3); Triangles.Add(BaseIndex + 2);

            // Back face triangles
            Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 5); Triangles.Add(BaseIndex + 6);
            Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 6); Triangles.Add(BaseIndex + 7);

            // Normals for the front and back faces
            for (int32 j = 0; j < 4; ++j)
            {
                Normals.Add(FVector(0, -1, 0)); // Front face
                Normals.Add(FVector(0, 1, 0));  // Back face
            }

            // UVs (simple planar mapping)
            for (int32 j = 0; j < 2; ++j)
            {
                UVs.Add(FVector2D(0, 0));
                UVs.Add(FVector2D(1, 0));
                UVs.Add(FVector2D(1, 1));
                UVs.Add(FVector2D(0, 1));
            }
        }

        // Create the wall segment after the window up to the next window or end of the wall
        if (windowRight <= WallLength)
        {
            // Front face (Above and below window)
            Vertices.Add(FVector(windowLeft, -HalfWallWidth, 0));                        // Bottom Left
            Vertices.Add(FVector(windowRight, -HalfWallWidth, 0));                       // Bottom Right
            Vertices.Add(FVector(windowRight, -HalfWallWidth, windowBottom));            // Top Right (below window)
            Vertices.Add(FVector(windowLeft, -HalfWallWidth, windowBottom));             // Top Left (below window)

            Vertices.Add(FVector(windowLeft, -HalfWallWidth, windowTop));                // Bottom Left (above window)
            Vertices.Add(FVector(windowRight, -HalfWallWidth, windowTop));               // Bottom Right (above window)
            Vertices.Add(FVector(windowRight, -HalfWallWidth, WallHeight));              // Top Right
            Vertices.Add(FVector(windowLeft, -HalfWallWidth, WallHeight));               // Top Left

            // Back face (Above and below window)
            Vertices.Add(FVector(windowLeft, HalfWallWidth, 0));                         // Bottom Left
            Vertices.Add(FVector(windowRight, HalfWallWidth, 0));                        // Bottom Right
            Vertices.Add(FVector(windowRight, HalfWallWidth, windowBottom));             // Top Right (below window)
            Vertices.Add(FVector(windowLeft, HalfWallWidth, windowBottom));              // Top Left (below window)

            Vertices.Add(FVector(windowLeft, HalfWallWidth, windowTop));                 // Bottom Left (above window)
            Vertices.Add(FVector(windowRight, HalfWallWidth, windowTop));                // Bottom Right (above window)
            Vertices.Add(FVector(windowRight, HalfWallWidth, WallHeight));               // Top Right
            Vertices.Add(FVector(windowLeft, HalfWallWidth, WallHeight));                // Top Left

            int32 BaseIndex = Vertices.Num() - 16;

            // Front face triangles (below window)
            Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 2); Triangles.Add(BaseIndex + 1);
            Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 3); Triangles.Add(BaseIndex + 2);

            // Front face triangles (above window)
            Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 6); Triangles.Add(BaseIndex + 5);
            Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 7); Triangles.Add(BaseIndex + 6);

            // Back face triangles (below window)
            Triangles.Add(BaseIndex + 8); Triangles.Add(BaseIndex + 9); Triangles.Add(BaseIndex + 10);
            Triangles.Add(BaseIndex + 8); Triangles.Add(BaseIndex + 10); Triangles.Add(BaseIndex + 11);

            // Back face triangles (above window)
            Triangles.Add(BaseIndex + 12); Triangles.Add(BaseIndex + 13); Triangles.Add(BaseIndex + 14);
            Triangles.Add(BaseIndex + 12); Triangles.Add(BaseIndex + 14); Triangles.Add(BaseIndex + 15);

            // Normals for the front and back faces (above and below window)
            for (int32 j = 0; j < 8; ++j)
            {
                Normals.Add(FVector(0, -1, 0)); // Front face
                Normals.Add(FVector(0, 1, 0));  // Back face
            }

            // UVs (simple planar mapping)
            for (int32 j = 0; j < 4; ++j)
            {
                UVs.Add(FVector2D(0, 0));
                UVs.Add(FVector2D(1, 0));
                UVs.Add(FVector2D(1, 1));
                UVs.Add(FVector2D(0, 1));
            }
        }

        // Generate side faces
        if (windowIndex == 0 || windowRight >= WallLength)
        {
            // Left side face
            Vertices.Add(FVector(currentIndentationX, -HalfWallWidth, 0)); // Bottom left front
            Vertices.Add(FVector(currentIndentationX, HalfWallWidth, 0));  // Bottom left back
            Vertices.Add(FVector(currentIndentationX, HalfWallWidth, WallHeight)); // Top left back
            Vertices.Add(FVector(currentIndentationX, -HalfWallWidth, WallHeight)); // Top left front

            // Right side face
            Vertices.Add(FVector(windowRight, -HalfWallWidth, 0)); // Bottom right front
            Vertices.Add(FVector(windowRight, HalfWallWidth, 0));  // Bottom right back
            Vertices.Add(FVector(windowRight, HalfWallWidth, WallHeight)); // Top right back
            Vertices.Add(FVector(windowRight, -HalfWallWidth, WallHeight)); // Top right front

            int32 BaseIndex = Vertices.Num() - 8;

            // Left side triangles
            Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 2); Triangles.Add(BaseIndex + 1);
            Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 3); Triangles.Add(BaseIndex + 2);

            // Right side triangles
            Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 6); Triangles.Add(BaseIndex + 5);
            Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 7); Triangles.Add(BaseIndex + 6);

            // Normals for the side faces
            for (int32 j = 0; j < 4; ++j)
            {
                Normals.Add(FVector(-1, 0, 0)); // Left side face
                Normals.Add(FVector(1, 0, 0));  // Right side face
            }

            // UVs (simple planar mapping for the sides)
            for (int32 j = 0; j < 4; ++j)
            {
                UVs.Add(FVector2D(0, 0));
                UVs.Add(FVector2D(1, 0));
                UVs.Add(FVector2D(1, 1));
                UVs.Add(FVector2D(0, 1));
            }
        }

        // Move to the next segment start point after the window
        currentIndentationX = windowRight;
    }

    // Top face of the wall
    Vertices.Add(FVector(0, -HalfWallWidth, WallHeight)); // Bottom left
    Vertices.Add(FVector(WallLength, -HalfWallWidth, WallHeight)); // Bottom right
    Vertices.Add(FVector(WallLength, HalfWallWidth, WallHeight)); // Top right
    Vertices.Add(FVector(0, HalfWallWidth, WallHeight)); // Top left

    // Bottom face of the wall
    Vertices.Add(FVector(0, -HalfWallWidth, 0)); // Bottom left
    Vertices.Add(FVector(WallLength, -HalfWallWidth, 0)); // Bottom right
    Vertices.Add(FVector(WallLength, HalfWallWidth, 0)); // Top right
    Vertices.Add(FVector(0, HalfWallWidth, 0)); // Top left

    int32 BaseIndex = Vertices.Num() - 8;
    // Top face triangles
    Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 2); Triangles.Add(BaseIndex + 1);
    Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 3); Triangles.Add(BaseIndex + 2);

    // Bottom face triangles
    Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 5); Triangles.Add(BaseIndex + 6);
    Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 6); Triangles.Add(BaseIndex + 7);

    // Normals for the top and bottom faces
    for (int32 j = 0; j < 4; ++j)
    {
        Normals.Add(FVector(0, 0, 1));  // Top face
        Normals.Add(FVector(0, 0, -1)); // Bottom face
    }

    // UVs (simple planar mapping for top and bottom faces)
    for (int32 j = 0; j < 4; ++j)
    {
        UVs.Add(FVector2D(0, 0));
        UVs.Add(FVector2D(1, 0));
        UVs.Add(FVector2D(1, 1));
        UVs.Add(FVector2D(0, 1));
    }

    // Create the wall mesh section with excluded windows
    ProceduralMeshComp->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, TArray<FColor>(), Tangents, true);

    // Assign a material if one is set
    if (WallMaterial)
    {
        ProceduralMeshComp->SetMaterial(0, WallMaterial);
    }
}



void AProcedularWall::GenerateWindowMesh()
{
    // Clear previous mesh data
    ProceduralMeshComp->ClearMeshSection(1);

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FProcMeshTangent> Tangents;

    float currentIndentationX = XAxisWindowIndentation;
    float currentIndentationZ = ZAxisWindowIndentation; // Z-axis offset
    int32 BaseIndex = Vertices.Num();
    float HalfWallWidth = WallWidth / 2.0f;
    float Offset = 0.1f; // Small offset to avoid Z-fighting

    for (int32 windowIndex = 0; windowIndex < NumberOfWindows; ++windowIndex)
    {
        float windowLeftIndentation = currentIndentationX;
        float windowRightIndentation = currentIndentationX + WindowLength;
        float windowBottomIndentation = currentIndentationZ;
        float windowTopIndentation = currentIndentationZ + WindowHeight;

        // Ensure that windows fit within the wall's boundaries
        if (windowRightIndentation > WallLength)
        {
            windowRightIndentation = WallLength;
        }
        if (windowRightIndentation < 0)
        {
            windowRightIndentation = 0;
        }
        if (windowTopIndentation > WallHeight)
        {
            windowTopIndentation = WallHeight;
        }
        if (windowBottomIndentation < 0)
        {
            windowBottomIndentation = 0;
        }

        // Vertices for the window (front and back faces)
        // Front face of the window (slightly in front of the wall face)
        Vertices.Add(FVector(windowLeftIndentation, -HalfWallWidth - Offset, windowBottomIndentation));
        Vertices.Add(FVector(windowRightIndentation, -HalfWallWidth - Offset, windowBottomIndentation));
        Vertices.Add(FVector(windowRightIndentation, -HalfWallWidth - Offset, windowTopIndentation));
        Vertices.Add(FVector(windowLeftIndentation, -HalfWallWidth - Offset, windowTopIndentation));

        // Back face of the window (slightly behind the wall face)
        Vertices.Add(FVector(windowLeftIndentation, HalfWallWidth + Offset, windowBottomIndentation));
        Vertices.Add(FVector(windowRightIndentation, HalfWallWidth + Offset, windowBottomIndentation));
        Vertices.Add(FVector(windowRightIndentation, HalfWallWidth + Offset, windowTopIndentation));
        Vertices.Add(FVector(windowLeftIndentation, HalfWallWidth + Offset, windowTopIndentation));

        // Side faces of the window
        Vertices.Add(FVector(windowRightIndentation, -HalfWallWidth - Offset, windowBottomIndentation)); // Left bottom front
        Vertices.Add(FVector(windowRightIndentation, HalfWallWidth + Offset, windowBottomIndentation));  // Left bottom back
        Vertices.Add(FVector(windowRightIndentation, HalfWallWidth + Offset, windowTopIndentation));     // Left top back
        Vertices.Add(FVector(windowRightIndentation, -HalfWallWidth - Offset, windowTopIndentation));    // Left top front

        Vertices.Add(FVector(windowLeftIndentation, -HalfWallWidth - Offset, windowBottomIndentation));  // Right bottom front
        Vertices.Add(FVector(windowLeftIndentation, HalfWallWidth + Offset, windowBottomIndentation));   // Right bottom back
        Vertices.Add(FVector(windowLeftIndentation, HalfWallWidth + Offset, windowTopIndentation));      // Right top back
        Vertices.Add(FVector(windowLeftIndentation, -HalfWallWidth - Offset, windowTopIndentation));     // Right top front

        // Top and bottom faces of the window
        Vertices.Add(FVector(windowLeftIndentation, -HalfWallWidth - Offset, windowTopIndentation));
        Vertices.Add(FVector(windowRightIndentation, -HalfWallWidth - Offset, windowTopIndentation));
        Vertices.Add(FVector(windowRightIndentation, HalfWallWidth + Offset, windowTopIndentation));
        Vertices.Add(FVector(windowLeftIndentation, HalfWallWidth + Offset, windowTopIndentation));

        Vertices.Add(FVector(windowLeftIndentation, -HalfWallWidth - Offset, windowBottomIndentation));
        Vertices.Add(FVector(windowRightIndentation, -HalfWallWidth - Offset, windowBottomIndentation));
        Vertices.Add(FVector(windowRightIndentation, HalfWallWidth + Offset, windowBottomIndentation));
        Vertices.Add(FVector(windowLeftIndentation, HalfWallWidth + Offset, windowBottomIndentation));

        // Triangles for the window (front and back faces)
        Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 2); Triangles.Add(BaseIndex + 1);
        Triangles.Add(BaseIndex + 0); Triangles.Add(BaseIndex + 3); Triangles.Add(BaseIndex + 2);

        Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 5); Triangles.Add(BaseIndex + 6);
        Triangles.Add(BaseIndex + 4); Triangles.Add(BaseIndex + 6); Triangles.Add(BaseIndex + 7);

        // Triangles for the window sides
        Triangles.Add(BaseIndex + 8); Triangles.Add(BaseIndex + 10); Triangles.Add(BaseIndex + 9);
        Triangles.Add(BaseIndex + 8); Triangles.Add(BaseIndex + 11); Triangles.Add(BaseIndex + 10);

        Triangles.Add(BaseIndex + 12); Triangles.Add(BaseIndex + 13); Triangles.Add(BaseIndex + 14);
        Triangles.Add(BaseIndex + 12); Triangles.Add(BaseIndex + 14); Triangles.Add(BaseIndex + 15);

        // Triangles for the window top and bottom
        Triangles.Add(BaseIndex + 16); Triangles.Add(BaseIndex + 18); Triangles.Add(BaseIndex + 17);
        Triangles.Add(BaseIndex + 16); Triangles.Add(BaseIndex + 19); Triangles.Add(BaseIndex + 18);

        Triangles.Add(BaseIndex + 20); Triangles.Add(BaseIndex + 21); Triangles.Add(BaseIndex + 22);
        Triangles.Add(BaseIndex + 20); Triangles.Add(BaseIndex + 22); Triangles.Add(BaseIndex + 23);

        // Normals for each window face
        for (int32 j = 0; j < 4; ++j)
        {
            Normals.Add(FVector(0, -1, 0)); // Front face
            Normals.Add(FVector(0, 1, 0));  // Back face
            Normals.Add(FVector(-1, 0, 0)); // Left face
            Normals.Add(FVector(1, 0, 0));  // Right face
            Normals.Add(FVector(0, 0, 1));  // Top face
            Normals.Add(FVector(0, 0, -1)); // Bottom face
        }

        // UVs (simple planar mapping for windows)
        for (int32 j = 0; j < 6; ++j)
        {
            UVs.Add(FVector2D(0, 0));
            UVs.Add(FVector2D(1, 0));
            UVs.Add(FVector2D(1, 1));
            UVs.Add(FVector2D(0, 1));
        }

        currentIndentationX += WindowLength + XAxisWindowIndentation;
        BaseIndex += 24;
    }

    ProceduralMeshComp->CreateMeshSection(1, Vertices, Triangles, Normals, UVs, TArray<FColor>(), Tangents, true);

    if (WindowMaterial)
    {
        ProceduralMeshComp->SetMaterial(1, WindowMaterial);
    }
    else
    {
        ProceduralMeshComp->SetMeshSectionVisible(1, false);
    }
}
