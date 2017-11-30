# Toy function time profiler for Lua 
## How to use
Wrapper a code region you want to profile with start\_profile and stop\_profile.
The profile results will be on stdout.
<pre><code>
profile = require 'profile'
profile.start\_profile()
profile.stop\_profile()
</pre><code>
