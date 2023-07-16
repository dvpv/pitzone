set(SOURCES
    flow/Flow.cpp
    store/Store.cpp
    updater/Updater.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${DEPENDENCY_LIBS})
