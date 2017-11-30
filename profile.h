extern "C" {

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int luaopen_profiler(lua_State *L);
int start_profile(lua_State *L);
int stop_profile(lua_State *L);

}
