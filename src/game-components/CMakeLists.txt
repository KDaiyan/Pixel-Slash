# src/game-components/CMakeLists.txt

file(GLOB GAMECOMP_SOURCES CONFIGURE_DEPENDS source/*.cpp)

add_library(game-components ${GAMECOMP_SOURCES})

target_include_directories(game-components PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(game-components PUBLIC
        utilities
        render
        asset-handler
        entities
        nlohmann_json::nlohmann_json
)
