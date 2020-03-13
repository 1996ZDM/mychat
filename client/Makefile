#变量赋值
TARGET=Client
DEP=*.c
CFLAG=-o
CC=gcc
GTK=`pkg-config gtk+-2.0 --libs --cflags gthread-2.0`
LIB:= -lrt
#编译.c文件
$(TARGET):$(DEP)
	$(CC) $(CFLAG) $@ $^ $(GTK) -g -pthread -lm
all:$(TARGET)
#清空.o文件
clean:all
	rm -f *.o
#安装
install:clean
	cp $(TARGET) /user/local/bin 
