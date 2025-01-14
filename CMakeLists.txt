cmake_minimum_required(VERSION 3.30)
project(sim)


set(CMAKE_PREFIX_PATH ${HOME}/geant4/geant4-v11.2.2-install) #added only for CLion, working in the terminal without it

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*)
file(GLOB macros ${PROJECT_SOURCE_DIR}/macros/*.mac)
file(COPY ${MACRO_FILES} DESTINATION ${CMAKE_BINARY_DIR}/)

add_executable(sim main.cpp ${sources}
        include/PhysicsList.hh
        src/PhysicsList.cpp
        include/ActionInitialization.hh
        src/ActionInitialization.cpp
        include/RunAction.hh
        src/RunAction.cpp
        include/DetectorConstruction.hh
        src/DetectorConstruction.cpp
        include/PrimaryGenrator.hh
        src/PrimaryGenrator.cpp
        include/SensitveDetector.hh
        src/SenstiveDetector.cpp
        include/SteppingAction.hh
        src/SteppingAction.cpp)
target_link_libraries(sim ${Geant4_LIBRARIES})
add_custom_target(test DEPENDS sim)

