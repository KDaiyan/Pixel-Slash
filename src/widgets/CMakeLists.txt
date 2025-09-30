# src/widgets/CMakeLists.txt

file(GLOB WIDGET_SOURCES CONFIGURE_DEPENDS source/*.cpp)

add_library(widgets ${WIDGET_SOURCES})

target_include_directories(widgets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(widgets PUBLIC
        render
        events
        game-components
        asset-handler
)
