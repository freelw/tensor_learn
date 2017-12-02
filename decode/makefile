DIR_INC = ./
DIR_LIB = ./
TARGET	= ./decoder
CFLAGS = -g -Wall -I$(DIR_INC) -L$(DIR_LIB)
LDFLAGS += -lstdc++
OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c *.cpp))
$(TARGET) : $(OBJECTS)
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)
%.o : %.c
	gcc -c $(CFLAGS) $< -o $@
clean:
	@rm -f *.o $(TARGET)
.PHONY:clean
