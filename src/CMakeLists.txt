set(SOURCES
    consumer/Consumer.cpp
    provider/Provider.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
