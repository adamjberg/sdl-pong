web:
	emcc src/main.c -s WASM=1 -s USE_SDL=2 -o public/index.html

pong:
	clang src/main.c -o pong -I include -L lib -l SDL2-2.0.0