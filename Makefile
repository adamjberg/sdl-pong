web:
	emcc src/main.c -Oz -s WASM=1 -s USE_SDL=2 --shell-file emscripten/template/index.html -o public/index.html

pong: src/main.c
	clang src/main.c -o pong -I include -L lib -l SDL2-2.0.0