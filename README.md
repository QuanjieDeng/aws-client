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

因为我希望直接把静态库和头文件放在项目中，所以单独存放一个文件夹
mkdir -p /tmp/install
make install DESTDIR=/tmp/install -C aws-cpp-sdk-core
make install DESTDIR=/tmp/install -C aws-cpp-sdk-s3
x这样.a库和头文件就都在  /tmp/install中了 在项目中创建th3part/aws文件夹
分别把/tmp/install  目录中的 core和s3文件夹拷贝进去，
然后创建th3part/aws/lib 文件夹
拷贝 libaws_sdk_cpp_core.a   libawc_sdk_cpp_s3.a 到lib文件夹 

在编译项目时加参数 -I./th3part/aws -Lth3part/aws/lib   -laws-cpp-sdk-core -laws-cpp-sdk-s3

```
