# Toy function time profiler for Lua
This toy Lua profiler measures the execution time of functions in regions of interest. This profile provide a simple example to show how to use Lua C API debug interface.

## How to use
First, build profile.so  with Makefile; you need to set where Lua header file is in Makefile. Then place profile.so in your Lua module search path.
Wrapper a code region you want to profile with start\_profile and stop\_profile.
The profile results will be on stdout.

```lua
profile = require 'profile'
profile.start_profile()
-- The beginning of ROI
func() 
-- The end of ROI
profile.stop\profile()
```
