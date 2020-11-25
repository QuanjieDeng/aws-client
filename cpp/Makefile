all: client



client:
	g++ -std=c++11  -I/usr/local/include/ -L/usr/local/lib64   -laws-cpp-sdk-core -laws-cpp-sdk-s3 main.cpp   -o client

clean:
	rm  -rf  client