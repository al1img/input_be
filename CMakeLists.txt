cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "input_be")

project(${PROJECT_NAME})

# set(INPUT_SOURCES
# )

set(BE_SOURCES
	src/InputBackend.cpp
)

include_directories(
	src
	${XEN_INCLUDE_PATH}
	${XENBE_INCLUDE_PATH}
	${IF_INCLUDE_PATH}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall")

link_directories(${XEN_LIB_PATH} ${XENBE_LIB_PATH})

# add_library(be_input STATIC ${INPUT_SOURCES})

add_executable(${PROJECT_NAME} ${BE_SOURCES})

target_link_libraries(${PROJECT_NAME}
#	be_input
	xenbe
	xenctrl
	xenstore
	xenevtchn
	xengnttab
	pthread
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/doxygen.cfg
		${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
		@ONLY
	)
	
	add_custom_target(
		doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)
