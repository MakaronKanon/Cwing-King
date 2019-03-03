# Makefile for generating executable for Windows ??x86??


o_files = windowsout/startup.o windowsout/windows_graphics.o windowsout/windows_delay.o windowsout/windows_input.o windowsout/snake.o windowsout/windows_init.o \
windowsout/windows_platform.o windowsout/obstacle.o windowsout/windows_asciidisplay.o windowsout/splashScreen.o \
windowsout/gameoverScreen.o

h_includes = -I src/snake -I src/windows -I src/windows/SDL/include -I src/windows/SDL/include/SDL2 -I src

define_flags = -D WINDOWS

endgoal: windowsout/cwingking.exe

windowsout/cwingking.exe: $(o_files)
	gcc -g -o windowsout/cwingking.exe $(o_files) -Lsrc/windows/SDL/lib -lmingw32 -lSDL2main -lSDL2

windowsout/%.o: %.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

#$< is source, $@ is target
windowsout/startup.o: src/startup.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/windows_graphics.o: src/windows/windows_graphics.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/windows_delay.o: src/windows/windows_delay.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/windows_input.o: src/windows/windows_input.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/snake.o: src/snake/snake.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/windows_init.o: src/windows/windows_init.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/windows_platform.o: src/windows/windows_platform.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/obstacle.o: src/snake/obstacle.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/windows_asciidisplay.o: src/windows/windows_asciidisplay.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/splashScreen.o: src/splashScreen.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/gameoverScreen.o: src/gameoverScreen.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

clean:
	rm $(o_files) windowsout/cwingking.exe
