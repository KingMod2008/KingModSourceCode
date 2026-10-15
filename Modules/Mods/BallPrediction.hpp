#pragma once
#include "../../pch.hpp"
#include <vector>
#include <string>
#include <chrono>

                         
class UCanvas;

                                
struct BallPredictionConfig
{
    bool bEnabled = false;
    bool bShowLine = true;                                       
    float fPredictionTime = 3.0f;                                                      
    float fTimeStep = 1.0f / 120.0f;                                                
    float fLineColorRGB[3] = { 1.0f, 1.0f, 1.0f };                                 
    char szLineColorHex[8] = "FFFFFF";                
    FLinearColor cLineColor = { 1.0f, 1.0f, 1.0f, 1.0f };                              
    float fPointRadius = 3.0f;                                     
    int iMaxPoints = 40;                                                
    bool bSafeConfig = true;                                                                        
    
                   
    bool bUseSpeedColor = false;                                      
    float fThickness = 2.0f;                             
    float fOpacity = 1.0f;                             
    bool bShowBallShape = false;                                                                     
    float fBallShapeScale = 1.0f;                                 
    float fMaxReach = 2000.0f;                                                                                   

                      
    bool bPredictGoal = true;                                         
    FLinearColor cGoalColor = { 1.0f, 0.0f, 0.0f, 1.0f };                

                                                                            
                                                                   
    bool bShowGoalImpact = true;
    bool bShowGoalTimer = true;                                                      

                                                                            
    bool bShowLanding = true;
    FLinearColor cLandingColor = { 0.1f, 0.8f, 1.0f, 1.0f };        

                                                              
    bool bShowBounces = false;

                                                                               
    bool bExtraSmoothing = true;

                                                                            
                                                                 
                                                      
                                                                     
    int iDrawStyle = 0;

                                                                       
    bool  bRainbow = false;
    float fRainbowSpeed = 50.0f;                                          

                                                              
    int iTickrate = 120;

                                                                            
    bool bGoalCrosshair = true;
    FLinearColor cGoalCrosshairColor = { 1.0f, 1.0f, 0.0f, 1.0f };          

                                                                           
    bool bPreHitEnabled = false;
                                                                          
                                                                                
                                                                        
    int iPreHitCarMode = 0;
    int iPreHitSelectedCarIndex = 0;
    float fPreHitMaxCarDistance = 1800.0f;
    float fPreHitLookAhead = 1.25f;
    float fPreHitHitboxPadding = 14.0f;                                                   
                                                                         
                                                                         

                                     
};

namespace BallPrediction
{
                                                      
    void Draw(class UCanvas* canvas);

                                                         
    struct PredictionData {
        const std::vector<FVector>* WorldPoints;
        bool bGoalPredicted;
                                                                         
        FVector GoalImpactPoint;
        bool bHasGoalImpact;
        float fGoalImpactTime;                                                      
                                       
        FVector LandingPoint;
        bool bHasLanding;
                                              
        const std::vector<FVector>* BouncePoints;
    };
    PredictionData GetPredictionData();

    struct PreHitPredictionData {
        int CarIndex = -1;
        size_t ContactPathIndex = 0;
        FVector ContactPoint{ 0.f, 0.f, 0.f };
        FVector CarHitboxExtent{ 0.f, 0.f, 0.f };
        float TimeToHit = 0.0f;
        float CurrentCarDistance = 0.0f;
        float CarSpeed = 0.0f;
        float ClosingSpeed = 0.0f;
        float Throttle = 0.0f;
        float Steer = 0.0f;
        bool OnGround = false;
        bool Boosting = false;
        std::vector<FVector> WorldPoints;
    };

                                                                         
                                                               
    void UpdatePreHitPredictions();
    const std::vector<PreHitPredictionData>& GetPreHitPredictions();

    
                                                                  
    void UpdatePrediction();

                                     
    BallPredictionConfig& GetSettings();
    
                                                       
    void UpdateColorFromPicker();
    
             
    void SetEnabled(bool enabled);
    bool IsEnabled();
    
                                                       
    void ForceRefresh();

                                                                             
                                                                              
                                                         
    std::vector<std::string> ListPresets();
    bool        SavePreset(const std::string& name);
    bool        LoadPreset(const std::string& name);
    bool        DeletePreset(const std::string& name);
    void        SetFavorite(const std::string& name);
    std::string GetFavorite();
    void        ApplyFavoriteOnStartup();

                                                   
    using BallPredictionSettings = BallPredictionConfig;
}
