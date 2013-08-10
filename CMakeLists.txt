project(se_constraints)

add_definitions(-std=c++11)

set(SRC_LIST constraints.cpp main.cpp relations.cpp)
add_executable(se_constraints ${SRC_LIST})

install(TARGETS se_constraints RUNTIME DESTINATION bin)
