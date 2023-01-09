
aux_source_directory(src SRC_FILES)

add_library(protolib STATIC ${SRC_FILES})
target_include_directories(protolib PUBLIC include)
