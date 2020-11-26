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
