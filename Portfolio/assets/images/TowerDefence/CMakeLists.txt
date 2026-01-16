cmake_minimum_required(VERSION 3.30)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    set(SFML_DIR "C:/SFML/lib/cmake/SFML")
endif()

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(TowerDefense
        main.cpp
        Tower.cpp
        Tower.h
        Player.cpp
        Player.h
        BomberTower.cpp
        BomberTower.h
        Cell.cpp
        Cell.h
        Map.cpp
        Map.h
        SniperTower.cpp
        SniperTower.h
        WizardTower.cpp
        WizardTower.h
        Critter.cpp
        Critter.h
        CritterGroupGenerator.cpp
        CritterGroupGenerator.h
        UIComponents/Button.cpp
        UIComponents/Button.h
        UIComponents/Menu.cpp
        UIComponents/Menu.h
        CritterObserver.h
        MapObserver.h
        Observer.h
        Subject.h
        TowerObserver.cpp
        TowerObserver.h
        BossCritter.cpp
        CritterFactory.cpp
        FastCritter.cpp
        WeakCritter.cpp
        BossCritter.h
        CritterFactory.h
        FastCritter.h
        WeakCritter.h
        StrongCritter.cpp
        StrongCritter.h
        TowerStats.cpp
        TowerStats.h
        CritterStats.cpp
        CritterStats.h
        BurningDamageDecorator.cpp
        FreezingDamageDecorator.cpp
        SplashDamageDecorator.cpp
        TowerDecorator.cpp
        BurningDamageDecorator.h
        FreezingDamageDecorator.h
        SplashDamageDecorator.h
        TowerDecorator.h
        NearestTargetingStrategy.h
        RandomTargetingStrategy.h
        StrongestTargetingStrategy.h
        TargetingStrategy.h
        TargetingStrategy.cpp
        TowerDecoratorUtility.h
        TowerDecoratorUtility.cpp
)

target_link_libraries(TowerDefense PRIVATE SFML::Graphics SFML::Window SFML::System)
