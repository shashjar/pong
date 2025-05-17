CC = clang
CFLAGS = -Wall -Wextra -I/opt/homebrew/opt/raylib/include
LDFLAGS = -L/opt/homebrew/opt/raylib/lib -lraylib \
          -framework OpenGL -framework Cocoa -framework IOKit \
          -framework CoreVideo -framework AudioToolbox

pong: main.c
	$(CC) main.c -o pong $(CFLAGS) $(LDFLAGS)

clean:
	rm -f pong
