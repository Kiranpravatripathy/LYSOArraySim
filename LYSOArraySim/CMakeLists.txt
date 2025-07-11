cmake_minimum_required(VERSION 3.1...3.27)
project(LYSOArraySim)

find_package(Geant4 REQUIRED)

add_executable(LYSOArraySim
    LYSOArraySim.cc
    src/DetectorConstruction.cc
    src/PrimaryGeneratorAction.cc
    src/LYSOHit.cc
    src/LYSOSensitiveDetector.cc
    src/EventAction.cc
)

target_include_directories(LYSOArraySim PRIVATE include ${Geant4_INCLUDE_DIRS})
target_link_libraries(LYSOArraySim ${Geant4_LIBRARIES})

