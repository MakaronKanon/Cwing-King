# Makefile for generating executable for Windows ??x86??

o_files = windowsout/startup.o windowsout/windows_graphics.o windowsout/windows_delay.o windowsout/windows_input.o windowsout/snake.o windowsout/windows_init.o \
windowsout/windows_platform.o windowsout/windows_asciidisplay.o

h_includes = -I src/snake -I src/windows -I src/windows/SDL/include -I src/windows/SDL/include/SDL2 -I src

define_flags = -D WINDOWS

endgoal: windowsout/cwingking.exe

windowsout/cwingking.exe: $(o_files)
	gcc -o windowsout/cwingking.exe $(o_files) -Lsrc/windows/SDL/lib -lmingw32 -lSDL2main -lSDL2

windowsout/startup.o: src/startup.c
	gcc -c src/startup.c $(define_flags) -o windowsout/startup.o $(h_includes)

windowsout/windows_graphics.o: src/windows/windows_graphics.c
	gcc -c src/windows/windows_graphics.c $(define_flags) -o windowsout/windows_graphics.o $(h_includes)

windowsout/windows_delay.o: src/windows/windows_delay.c
	gcc -c src/windows/windows_delay.c $(define_flags) -o windowsout/windows_delay.o $(h_includes)

windowsout/windows_input.o: src/windows/windows_input.c
	gcc -c src/windows/windows_input.c $(define_flags) -o windowsout/windows_input.o $(h_includes)

windowsout/snake.o: src/snake/snake.c
	gcc -c src/snake/snake.c $(define_flags) -o windowsout/snake.o $(h_includes)

windowsout/windows_init.o: src/windows/windows_init.c
	gcc -c src/windows/windows_init.c $(define_flags) -o windowsout/windows_init.o $(h_includes)

windowsout/windows_platform.o: src/windows/windows_platform.c
	gcc -c src/windows/windows_platform.c $(define_flags) -o windowsout/windows_platform.o $(h_includes)

windowsout/windows_asciidisplay.o: src/windows/windows_asciidisplay.c
	gcc -c src/windows/windows_asciidisplay.c $(define_flags) -o windowsout/windows_asciidisplay.o $(h_includes)

clean:
	rm $(o_files) windowsout/cwingking.exe
