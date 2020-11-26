# aws-client
aws SDK的使用示例

- nodejs   nodejs的使用示例
- cpp   C++版本的客户端使用示例


## nodejs 
- nodejs版本直接包含aws-sdk 包就可以使用

## C++ 
- C++版本示例中是在linux系统下使用的示例，其他环境 可以参考文档 
C++版本的github地址 
英文版的接口说明    https://sdk.amazonaws.com/cpp/api/LATEST/index.html
官方的代码示例  https://github.com/awsdocs/aws-doc-sdk-examples/blob/master/cpp/example_code/s3/put_object.cpp


### linux环境下编译安装
- 默认安装的路径是  /usr/local
```
下载源码
git clone https://github.com/aws/aws-sdk-cpp.git
创建build文件夹，不要在aws-sdk-cpp源码文件夹中创建
sudo mkdir sdk_build
cd sdk_build
sudo cmake   sdk源码文件夹 -D CMAKE_BUILD_TYPE=[Debug | Release]
如果只想编译s3  
sudo cmake -D CMAKE_BUILD_TYPE=[Debug | Release] -D BUILD_ONLY="s3"

然后 make &&make  install  
通过上面两步骤  aws-s3的动态库就已经完成了安装  下一步就可以在代码中使用了 

需要注意编译参数
-I/usr/local/include/ -L/usr/local/lib64   -laws-cpp-sdk-core -laws-cpp-sdk-s3

```
### linux环境下静态库的生成
```
下载源码
git clone https://github.com/aws/aws-sdk-cpp.git
创建构建文件夹，构建文件夹最好不要在源码文件夹中
mkdir -p /tmp/build; cd /tmp/build
生成Makefile
cmake -DCMAKE_BUILD_TYPE=Release /tmp/aws-sdk-cpp-1.0.164(源码路径，根据自己的实际情况修改)   -D BUILD_ONLY="s3" (s3标识只编译s3，全部编译很耗时)   -DBUILD_SHARED_LIBS="OFF"（生成静态库）
编译
make 
安装
如果是默认安装 直接make  install 即可

```

### 如何在项目中集成静态库 
- 有时候我们希望把sdk作为项目的静态库，然后把相关的头文件都放在项目的th3part中，这样写代码时也有相关的代码提示，比较方便，下面记录这一过程 
- 首先在上一节已经知道如何编译出静态库，如果直接make install  默认安装的位置是 /usr/local
  现在我们希望得到.a文件以及相关的依赖，可以临时指定一个安装路径，这样就能比较方便的得到纯净的相关代码 
- 在make编译成功之后，创建文件夹 在  build目录创建install文件夹 
 mkdir install  
- 执行安装动作 安装到 install 目录 
make install DESTDIR=./install -C aws-cpp-sdk-core
make install DESTDIR=./install -C aws-cpp-sdk-s3
成功后，在install/usr/local/lib64可以看到 lib-aws-cpp-sdk-core.a 和   lib-aws-cpp-sdk-s3.a 两个静态库
在 install/usr/local 可以看到aws文件夹，这样.a  库和头文件我们就都有了，
把aws 文件内容全部拷贝到 th3part中，把两个.a 文件拷贝到  th3part/lib中
然后编写Makefile

```
CC = g++
CCFLAGS = -DNDEBUG  -std=c++11 -O0
INCLUDE := -I../aws_client_cpp/th3part/
LDFLAGS := -L../aws_client_cpp/th3part/lib  -Wl,-rpath ./ -Wl,-rpath ../aws_client_cpp/th3part/lib
LIBS  := -lcurl -pthread -lcrypto -Wl,--start-group  -laws-c-common -laws-checksums  -laws-c-event-stream -laws-cpp-sdk-core -laws-cpp-sdk-s3  -Wl,--end-group

make: main
	rm *.o
	@echo success
	
main:
	$(CC) $(CCFLAGS) $(INCLUDE) -c -o main.o main.cpp
	$(CC) $(CCFLAGS) $(INCLUDE) $(LDFLAGS) -o client main.o $(LIBS)

clean:
	rm  -rf  client
```
到这里如果直接make 是不行的，你会发现 还有三个库 laws-c-common -laws-checksums  -laws-c-event-stream
这是AWS-SDK-CPP  1.7版本后单独依赖的三个库，在build/.deps/i/stall  中已经编译好了，同样的
把 build/.deps/install/lib64 下的 libaws-c-common.a libaws-c-event-stream.a  libaws-checksums.a 拷贝到th3part/lib目中
把 build/.deps/install/include/aws 下的所有文件件拷贝到 th3part/aws目录中
th3part的目录完整应该是 
```
th3part
├── aws
│   ├── checksums
│   ├── common
│   ├── core
│   ├── event-stream
│   ├── s3
└── lib
    ├── libaws-c-common.a
    ├── libaws-c-event-stream.a
    ├── libaws-checksums.a
    ├── libaws-cpp-sdk-core.a
    └── libaws-cpp-sdk-s3.a
```
然后直接make 即可编译成功
 







