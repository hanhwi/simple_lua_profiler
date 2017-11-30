#include "profile.h"
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <unordered_map>
#include <cassert>
#include <vector>

clock_t start_time, prev_clock;
std::unordered_map<const char*, clock_t> tot_time;
std::vector<const char*> prev_funcs;

static inline double
clk_to_second(clock_t clk){
    return clk / (double) CLOCKS_PER_SEC;
}

static void set_timer (lua_State *L, lua_Debug *ar){
    lua_getinfo(L, "nS", ar);
    if (ar->name){
        if (ar->event == LUA_HOOKCALL){
            tot_time[prev_funcs.back()] += clock() - prev_clock;
            prev_funcs.push_back(ar->name);
        } else if (ar->event == LUA_HOOKRET){
            tot_time[ar->name] += clock() - prev_clock;
            prev_funcs.pop_back();
        }
        prev_clock = clock();
    }
}

int start_profile(lua_State *L)
{
    lua_sethook(L, set_timer, LUA_MASKCALL | LUA_MASKRET, 0);
    prev_funcs.resize(100);
    prev_funcs.push_back("basefunc");
    start_time = prev_clock = clock();
    return 0;
}

int stop_profile(lua_State* L){
    double exec_secs = clk_to_second(clock() - start_time);
    printf("[PROFILE] Stop clock profiler\n");
    printf("FuncName: Time[s]\n");
    for (auto& info: tot_time){
        assert(info.first);
        if (strcmp(info.first, "start_profile") == 0
            || strcmp(info.first, "stop_profile") == 0){
            continue;
        }
        printf("%s: %.2f sec\n", info.first, clk_to_second(info.second));
    }
    printf("=========================\n");
    printf("Total exec clocks %.2f\n", exec_secs);
    return 0;
}

int
luaopen_profiler(lua_State *L){
    lua_newtable(L);
    lua_pushcfunction(L, start_profile);
    lua_setfield(L, -2, "start_profile");
    lua_pushcfunction(L, stop_profile);
    lua_setfield(L, -2, "stop_profile");
    return 1;
}
