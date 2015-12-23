all:
	if [ ! -d "./bin" ];\
		then mkdir bin;\
	fi
	g++ src/main.cpp -w -lSDL2 -lSDL2_image -lSDL2_mixer -o bin/a.out

clean:
	rm -rf bin
