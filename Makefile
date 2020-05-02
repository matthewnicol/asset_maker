assetmaker:
	gcc -c src/frame.c -o build/frame.o
	gcc -c src/palette.c -o build/palette.o
	gcc -c src/colour.c -o build/colour.o
	gcc -c src/colour_select.c -o build/colour_select.o
	gcc -c src/mouse.c -o build/mouse.o
	gcc -c src/component.c -o build/component.o
	gcc -c src/window_globals.c -o build/window_globals.o
	gcc -c src/list.c -o build/list.o
	gcc -c src/main.c -Lglew -lglut -lGL -o build/main.o
	gcc -Lglew -lglut -lGL -lGLU -o ./build/a.out \
		build/list.o \
		build/component.o \
		build/colour.o \
		build/mouse.o \
		/usr/local/include/c_libraries/except.o \
		/usr/local/include/c_libraries/assert.o \
		/usr/local/include/c_libraries/mem.o \
		build/window_globals.o \
		build/colour_select.o \
		build/main.o \
		build/palette.o \
		build/frame.o
