#################### Import the 'io_tools' library here ########################
find_library(TOOL 
             NAME io_tools
             PATHS ${LIBRARY_OUTPUT_PATH})
#################### Create a library 'image' below this line ##################
add_library(image image.h io_tools.h image.cpp)
target_link_libraries(image ${TOOL})