set(SRC_LIST ../friend.pb.cc callfriendservice.cc )

add_executable(consumer ${SRC_LIST})
target_link_libraries(consumer mprpc protobuf)