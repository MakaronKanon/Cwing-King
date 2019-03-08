# Makefile for generating executable for Windows ??x86??


o_files = windowsout/startup.o windowsout/windows_graphics.o windowsout/windows_delay.o windowsout/windows_input.o windowsout/player.o windowsout/windows_init.o \
windowsout/windows_platform.o windowsout/obstacle.o windowsout/windows_asciidisplay.o windowsout/splashscreen.o \
windowsout/gameover_screen.o windowsout/roof.o windowsout/rope.o windowsout/obstacle_manager.o windowsout/rng.o

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

windowsout/player.o: src/snake/player.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/windows_init.o: src/windows/windows_init.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/windows_platform.o: src/windows/windows_platform.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/obstacle.o: src/snake/obstacle.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/windows_asciidisplay.o: src/windows/windows_asciidisplay.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/splashscreen.o: src/splashscreen.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/gameover_screen.o: src/gameover_screen.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/roof.o: src/snake/roof.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)


windowsout/rope.o: src/snake/rope.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/obstacle_manager.o: src/snake/obstacle_manager.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

windowsout/rng.o: src/rng.c
	gcc -g -c $< $(define_flags) -o $@ $(h_includes)

clean:
	rm $(o_files) windowsout/cwingking.exe
