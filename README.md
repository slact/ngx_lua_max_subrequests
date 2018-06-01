Subrequest info for [lua_nginx_module](https://github.com/openresty/lua-nginx-module) and [openresty](http://openresty.org/). Count the number of max, active, and remaining subrequests for an HTTP request. Useful for [`ngx.location.capture_multi`](https://github.com/openresty/lua-nginx-module#ngxlocationcapture_multi).

# API
```lua
local max_subrequests = require "ngx.max_subrequests"
```

### `max_subrequests.max()`
Returns absolute max number of active subrequests allowed. This is equal to `NGX_HTTP_MAX_SUBREQUESTS + 1`.

### `max_subrequests.active()`
Returns number of active subrequests for the current request.

### `max_subrequests.remaining()`
Returns number of remaining active subrequests for the current request. Starting more subrequests than this number will result in a `subrequests cycle while processing` error.
