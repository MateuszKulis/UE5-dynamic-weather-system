#include "DayNightCycle.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Math/UnrealMathUtility.h"

ADayNightCycle::ADayNightCycle()
{
    PrimaryActorTick.bCanEverTick = true;
    TimeOfDay = 12.0f;  // Start w po³udnie
    TimeSpeed = 1.0f;   // Normalna szybkoœæ czasu
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
    TimeOfDay = FMath::Fmod(TimeOfDay, 24.0f);  // Zapêtlenie czasu

    // Obliczanie k¹ta s³oñca
    float SunAngle = (TimeOfDay / 24.0f) * 360.0f;

    // Ustawienie rotacji s³oñca (Directional Light)
    if (DirectionalLight)
    {
        DirectionalLight->SetActorRotation(FRotator(SunAngle, 90.0f, 0.0f));

        // Dostosowanie intensywnoœci œwiat³a w zale¿noœci od k¹ta s³oñca
        float LightIntensity = FMath::Lerp(4.0f, 10.0f, FMath::Clamp(FMath::Cos(FMath::DegreesToRadians(SunAngle)), 0.4f, 1.0f));
        DirectionalLight->GetLightComponent()->SetIntensity(LightIntensity);
    }

    // Ustawienie rotacji Ksiê¿yca
    if (Moon)
    {
        float MoonAngle = SunAngle;
        Moon->SetActorRotation(FRotator(MoonAngle, 0.0f, 0.0f));
    }

    // Zmiana gêstoœci mg³y podczas dnia i nocy
    if (ExponentialHeightFog)
    {
        float FogDensity = FMath::Lerp(0.1f, 1.0f, FMath::Clamp(SunAngle / 180.0f, 0.0f, 1.0f));
        ExponentialHeightFog->GetComponent()->SetFogDensity(FogDensity);
    }
}

