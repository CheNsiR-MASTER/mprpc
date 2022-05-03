# mprpc
基于muduo网络库 和 protobuf实现的RPC通信框架

该项目中使用ZooKeeper实现了方法的注册与分发，使用缓存队列实现了日志系统

# 项目编译:
1.在项目根目录下运行

```
 ./autobuild.sh
```

2.进入build目录下运行
```
cmake ..

make
```


