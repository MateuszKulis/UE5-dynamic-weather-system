#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/PointLightComponent.h"
#include "DayNightCycle.generated.h"

UCLASS()
class WEATHERSYSTEM_API ADayNightCycle : public AActor
{
    GENERATED_BODY()

public:
    ADayNightCycle();

protected:
    virtual void BeginPlay() override;

public:
    // Funkcja wykonywana co klatk�
    virtual void Tick(float DeltaTime) override;

    // Zmienna przechowuj�ca aktualny czas dnia (0.0f - 24.0f)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
    float TimeOfDay;

    // Zmienna kontroluj�ca szybko�� up�ywu czasu
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
    float TimeSpeed;

    // Referencja do Directional Light w scenie (S�o�ce)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
    ADirectionalLight* DirectionalLight;

    // Referencja do Height Fog w scenie
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
    AExponentialHeightFog* ExponentialHeightFog;

    // Referencja do Ksi�yca (mo�e by� Static Mesh, Directional Light, lub Point Light)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DayNight")
    AActor* Moon;



};
