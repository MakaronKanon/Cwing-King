# Makefile for generating executable for Windows ??x86??

o_files = windowsout/startup.o windowsout/windows_graphics.o windowsout/windows_delay.o windowsout/windows_input.o windowsout/snake.o windowsout/windows_init.o

h_includes = -I src/snake

endgoal: windowsout/cwingking.exe

windowsout/cwingking.exe: $(o_files)
	gcc -o windowsout/cwingking.exe $(o_files) -Lsrc/windows/SDL/lib -lmingw32 -lSDL2main -lSDL2

windowsout/startup.o: src/startup.c
	gcc -c src/startup.c -D WINDOWS -o windowsout/startup.o -I src/windows -I src/windows/SDL/include -I src/windows/SDL/include/SDL2 $(h_includes)

windowsout/windows_graphics.o: src/windows/windows_graphics.c
	gcc -c src/windows/windows_graphics.c -D WINDOWS -o windowsout/windows_graphics.o -I src/windows -I src/windows/SDL/include/SDL2

windowsout/windows_delay.o: src/windows/windows_delay.c
	gcc -c src/windows/windows_delay.c -D WINDOWS -o windowsout/windows_delay.o -I src/windows -I src/windows/SDL/include/SDL2

windowsout/windows_input.o: src/windows/windows_input.c
	gcc -c src/windows/windows_input.c -D WINDOWS -o windowsout/windows_input.o -I src/windows -I src/windows/SDL/include/SDL2 -I src

windowsout/snake.o: src/snake/snake.c
	gcc -c src/snake/snake.c -D WINDOWS -o windowsout/snake.o -I src/windows -I src/windows/SDL/include/SDL2 -I src -I src/snake

windowsout/windows_init.o: src/windows/windows_init.c
	gcc -c src/windows/windows_init.c -D WINDOWS -o windowsout/windows_init.o -I src/windows -I src/windows/SDL/include/SDL2 -I src

clean:
	rm $(o_files) windowsout/cwingking.exe
