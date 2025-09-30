# src/app/CMakeLists.txt

file(GLOB APP_SOURCES CONFIGURE_DEPENDS source/*.cpp)

add_library(app ${APP_SOURCES})

target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(app PUBLIC
        render
        game-components
        entities
        events
        widgets
        utilities
        asset-handler
        nlohmann_json::nlohmann_json
)

add_executable(Pixel_Slash main.cpp)
target_link_libraries(Pixel_Slash PRIVATE app)