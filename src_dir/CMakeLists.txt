file(GLOB_RECURSE source *.cpp *.h)

link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(program ${source})

target_link_libraries(program ${GTKMM_LIBRARIES} -lfftw3 -lm -pthread)