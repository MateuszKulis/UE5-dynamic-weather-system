#include "DayNightCycle.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Math/UnrealMathUtility.h"

ADayNightCycle::ADayNightCycle()
{
    PrimaryActorTick.bCanEverTick = true;
    TimeOfDay = 12.0f;  // Start w po�udnie
    TimeSpeed = 1.0f;   // Normalna szybko�� czasu
}

void ADayNightCycle::BeginPlay()
{
    Super::BeginPlay();
}

void ADayNightCycle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Aktualizacja czasu dnia
    TimeOfDay += DeltaTime * TimeSpeed;
    TimeOfDay = FMath::Fmod(TimeOfDay, 24.0f);  // Zap�tlenie czasu

    // Obliczanie k�ta s�o�ca
    float SunAngle = (TimeOfDay / 24.0f) * 360.0f;

    // Ustawienie rotacji s�o�ca (Directional Light)
    if (DirectionalLight)
    {
        DirectionalLight->SetActorRotation(FRotator(SunAngle, 90.0f, 0.0f));

        // Dostosowanie intensywno�ci �wiat�a w zale�no�ci od k�ta s�o�ca
        float LightIntensity = FMath::Lerp(4.0f, 10.0f, FMath::Clamp(FMath::Cos(FMath::DegreesToRadians(SunAngle)), 0.4f, 1.0f));
        DirectionalLight->GetLightComponent()->SetIntensity(LightIntensity);
    }

    // Ustawienie rotacji Ksi�yca
    if (Moon)
    {
        float MoonAngle = SunAngle;
        Moon->SetActorRotation(FRotator(MoonAngle, 0.0f, 0.0f));
    }

    // Zmiana g�sto�ci mg�y podczas dnia i nocy
    if (ExponentialHeightFog)
    {
        float FogDensity = FMath::Lerp(0.1f, 1.0f, FMath::Clamp(SunAngle / 180.0f, 0.0f, 1.0f));
        ExponentialHeightFog->GetComponent()->SetFogDensity(FogDensity);
    }
}

