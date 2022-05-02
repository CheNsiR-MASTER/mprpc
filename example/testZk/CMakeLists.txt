add_executable(createNode testCreateNode.cc)
add_executable(getNode testGetNode.cc)

target_link_libraries(createNode mprpc protobuf)
target_link_libraries(getNode mprpc protobuf)