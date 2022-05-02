###
 # @Author: your name
 # @Date: 2022-04-27 20:21:51
 # @LastEditTime: 2022-05-02 23:10:21
 # @LastEditors: Please set LastEditors
 # @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 # @FilePath: /linux/RPC/autobuild.sh
### 
#!/bin/bash

set -e

rm -rf `pwd`/build/*
cd `pwd`/build &&
	cmake .. &&
	make
cd ..
cp -r `pwd`/src/include `pwd`/lib