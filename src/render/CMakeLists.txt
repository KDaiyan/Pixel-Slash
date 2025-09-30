# src/render/CMakeLists.txt

file(GLOB RENDER_SOURCES CONFIGURE_DEPENDS source/*.cpp)

add_library(render ${RENDER_SOURCES})

target_include_directories(render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(render PUBLIC
        SFML::Graphics
        SFML::Window
        SFML::System
)