# Makefile for generating executable for Windows ??x86??

o_files = windowsout/startup.o windowsout/windows_graphics.o windowsout/windows_delay.o windowsout/windows_input.o windowsout/snake.o windowsout/windows_init.o \
windowsout/windows_platform.o windowsout/obstacle.o windowsout/windows_asciidisplay.o windowsout/splashScreen.o \
windowsout/gameoverScreen.o

h_includes = -I src/snake -I src/windows -I src/windows/SDL/include -I src/windows/SDL/include/SDL2 -I src

define_flags = -D WINDOWS

endgoal: windowsout/cwingking.exe

windowsout/cwingking.exe: $(o_files)
	gcc -g -o windowsout/cwingking.exe $(o_files) -Lsrc/windows/SDL/lib -lmingw32 -lSDL2main -lSDL2

windowsout/startup.o: src/startup.c
	gcc -g -c src/startup.c $(define_flags) -o windowsout/startup.o $(h_includes)

windowsout/windows_graphics.o: src/windows/windows_graphics.c
	gcc -g -c src/windows/windows_graphics.c $(define_flags) -o windowsout/windows_graphics.o $(h_includes)

windowsout/windows_delay.o: src/windows/windows_delay.c
	gcc -g -c src/windows/windows_delay.c $(define_flags) -o windowsout/windows_delay.o $(h_includes)

windowsout/windows_input.o: src/windows/windows_input.c
	gcc -g -c src/windows/windows_input.c $(define_flags) -o windowsout/windows_input.o $(h_includes)

windowsout/snake.o: src/snake/snake.c
	gcc -g -c src/snake/snake.c $(define_flags) -o windowsout/snake.o $(h_includes)

windowsout/windows_init.o: src/windows/windows_init.c
	gcc -g -c src/windows/windows_init.c $(define_flags) -o windowsout/windows_init.o $(h_includes)

windowsout/windows_platform.o: src/windows/windows_platform.c
	gcc -g -c src/windows/windows_platform.c $(define_flags) -o windowsout/windows_platform.o $(h_includes)

windowsout/obstacle.o: src/snake/obstacle.c
	gcc -g -c src/snake/obstacle.c $(define_flags) -o windowsout/obstacle.o $(h_includes)

windowsout/windows_asciidisplay.o: src/windows/windows_asciidisplay.c
	gcc -g -c src/windows/windows_asciidisplay.c $(define_flags) -o windowsout/windows_asciidisplay.o $(h_includes)

windowsout/splashScreen.o: src/splashScreen.c
	gcc -g -c src/splashScreen.c $(define_flags) -o windowsout/splashScreen.o $(h_includes)

windowsout/gameoverScreen.o: src/gameoverScreen.c
	gcc -g -c src/gameoverScreen.c $(define_flags) -o windowsout/gameoverScreen.o $(h_includes)

clean:
	rm $(o_files) windowsout/cwingking.exe
