# src/entities/CMakeLists.txt

file(GLOB ENTITY_SOURCES CONFIGURE_DEPENDS source/*.cpp)

add_library(entities ${ENTITY_SOURCES})

target_include_directories(entities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(entities PUBLIC
        game-components
        events
        utilities
        render
)
