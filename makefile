OS = LINUX

CC = gcc
CFLAGS = -I./include/ -L./libs/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
NAME = sandsim

ifeq ($(OS), WINDOWS)
CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -s -O1 -I./include/ -L./libs/ -Wl,--subsystem,windows -lraylibwin -lopengl32 -lgdi32 -lwinmm -static -lpthread -DPLATFORM_DESKTOP
NAME = sandsim.exe
endif
OBJ = main.o

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $^ $(CFLAGS)

clean:
	rm *.o
