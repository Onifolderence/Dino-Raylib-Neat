run: main
	./server/game/build/main

main: ./server/game/src/main.c
	gcc ./server/game/src/main.c -o ./server/game/build/main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
