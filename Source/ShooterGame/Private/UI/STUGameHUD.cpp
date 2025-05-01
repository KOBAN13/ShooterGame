// Shoot Then Up Game, All Rights Reserved

#include "STUGameHUD.h"
#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();

    DrawCrosshair();
}

void ASTUGameHUD::DrawCrosshair()
{
    const auto SizeX = Canvas -> SizeX / 2;
    const auto SizeY = Canvas -> SizeY / 2;

    const TInterval<float> Center(SizeX, SizeY);

    constexpr auto HalfLineSize = 10.0f;
    constexpr auto LineThickness = 2.0f;
    const auto LineColor = FLinearColor::Green;
    
    DrawLine(
        Center.Min - HalfLineSize,
        Center.Max,
        Center.Min + HalfLineSize,
        Center.Max,
        LineColor,
        LineThickness
    );

    DrawLine(
        Center.Min,
        Center.Max - HalfLineSize,
        Center.Min,
        Center.Max + HalfLineSize,
        LineColor,
        LineThickness
    );
}