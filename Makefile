LUA_HEADER_PATH=/usr/include/lua5.1

profile.so: profile.c profile.h
	g++ -O3 -I${LUA_HEADER_PATH} $< -o $@ -shared -std=c++11 -fPIC

.PHONY: clean
clean:
	rm profile.so
