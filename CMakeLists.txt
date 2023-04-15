cmake_minimum_required(VERSION 3.0.2)
project(RAIIandRuleOfZero)

set(CMAKE_BUILD_TYPE Release)

set(SRC_DIR src)
set(LIB_DIR lib)
set(BIN_DIR bin)
set(INCLUDE_DIR include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

set(TARGET_NAIVE_VECTOR naive_vector)
set(TARGET_CLOSER_TO_RULE_OF_0 closer_to_rule_of_0)
set(TARGET_RULE_OF_0 rule_of_0)


include_directories(${INCLUDE_DIR} "/export/devel/platform/boost/$ENV{BOOST_VERSION}/boost/include")

link_directories( ${LIB_DIR} )
#set(APP_LINK_LIBS ${TARGET_LIB} dcpsisocpp2 ddskernel dl pthread)

set(CMAKE_CXX_FLAGS "-fPIC -O3 -Wall -Wno-unused-function -std=c++20")

set(SOURCES_NAIVE_VECTOR ${SRC_DIR}/NaiveVector.cpp)
set(SOURCES_CLOSER_TO_RULE_OF_0 ${SRC_DIR}/CloserToRuleOf0.cpp)
set(SOURCES_RULE_OF_0 ${SRC_DIR}/TrueRuleOf0.cpp)

#add_library(${TARGET_LIB} STATIC ${SOURCES_LIB})

add_executable(${TARGET_NAIVE_VECTOR} ${SOURCES_NAIVE_VECTOR})
add_executable(${TARGET_CLOSER_TO_RULE_OF_0} ${SOURCES_CLOSER_TO_RULE_OF_0})
add_executable(${TARGET_RULE_OF_0} ${SOURCES_RULE_OF_0})

#target_link_libraries(${TARGET_SUB} ${APP_LINK_LIBS})

#add_dependencies( ${TARGET_SUB} ${TARGET_LIB} )
