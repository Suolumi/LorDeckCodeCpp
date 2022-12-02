cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

project(LorDeckCode)

include_directories(include cppcodec)

add_executable(${CMAKE_PROJECT_NAME}
	src/LoRDeck.cpp
	src/main.cpp
	src/utils.cpp
)

add_executable(deckTesting
	src/LoRDeck.cpp
	tests/main.cpp
	src/utils.cpp
)

add_test(tests deckTesting)