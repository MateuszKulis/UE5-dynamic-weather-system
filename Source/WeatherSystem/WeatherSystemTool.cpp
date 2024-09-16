#include "WeatherSystemTool.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h" 

AWeatherSystemTool::AWeatherSystemTool()
{
    PrimaryActorTick.bCanEverTick = true;

    RainEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("RainEffect"));
    RainEffect->SetupAttachment(RootComponent);

    StormEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("StormEffect"));
    StormEffect->SetupAttachment(RootComponent);

    FogEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FogEffect"));
    FogEffect->SetupAttachment(RootComponent);
}

void AWeatherSystemTool::BeginPlay()
{
    Super::BeginPlay();

    RainEffect->Deactivate();
    StormEffect->Deactivate();
    FogEffect->Deactivate();

    GetWorldTimerManager().SetTimer(WeatherEffectTimerHandle, this, &AWeatherSystemTool::StartRandomWeatherEffect, 10.0f, false);
}

void AWeatherSystemTool::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AWeatherSystemTool::StartRain()
{
    if (RainEffect)
    {
        RainEffect->Activate(true); 
    }
}

void AWeatherSystemTool::StartStorm()
{
    if (StormEffect)
    {
        StormEffect->Activate(true);  
    }
}

void AWeatherSystemTool::StartFog()
{
    if (FogEffect)
    {
        FogEffect->Activate(true);  
    }
}

void AWeatherSystemTool::StartRandomWeatherEffect()
{
    int32 RandomEffect = UKismetMathLibrary::RandomIntegerInRange(0, 2);

    switch (RandomEffect)
    {
    case 0:
        StartRain();  
        break;
    case 1:
        StartStorm();  
        break;
    case 2:
        StartFog(); 
        break;
    default:
        break;
    }

    float RandomDuration = UKismetMathLibrary::RandomFloatInRange(5.0f, 15.0f);

    GetWorldTimerManager().SetTimer(StopEffectTimerHandle, this, &AWeatherSystemTool::StopCurrentEffect, RandomDuration, false);
}

void AWeatherSystemTool::StopCurrentEffect()
{
    if (RainEffect)
    {
        RainEffect->Deactivate();
    }
    if (StormEffect)
    {
        StormEffect->Deactivate();
    }
    if (FogEffect)
    {
        FogEffect->Deactivate();
    }

    float RandomDelay = UKismetMathLibrary::RandomFloatInRange(5.0f, 10.0f);
    GetWorldTimerManager().SetTimer(WeatherEffectTimerHandle, this, &AWeatherSystemTool::StartRandomWeatherEffect, RandomDelay, false);
}
