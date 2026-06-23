file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(Game
    ${GAME_SOURCES}
)

target_link_libraries(Game PRIVATE
    MountainSDK
)