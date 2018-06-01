#include <ngx_lua_max_subrequests.h>
#include <lauxlib.h>
#include "ngx_http_lua_api.h"

#include <assert.h>

//#define DEBUG_ON

static int ngx_lua_max_subrequests_get_total(lua_State *L) {
  lua_pushnumber(L, NGX_HTTP_MAX_SUBREQUESTS + 1);
  return 1;
}

static int ngx_lua_max_subrequests_get_active(lua_State *L) {
  ngx_http_request_t *r = ngx_http_lua_get_request(L);
  lua_pushnumber(L, NGX_HTTP_MAX_SUBREQUESTS + 1 - r->subrequests);
  return 1;
}

static int ngx_lua_max_subrequests_get_remaining(lua_State *L) {
  ngx_http_request_t *r = ngx_http_lua_get_request(L);
  lua_pushnumber(L, r->subrequests);
  return 1;
}


static int ngx_lua_max_subrequests_init_module(lua_State * L) {
  int t = lua_gettop(L) + 1;
  lua_createtable(L, 0, 3);
  lua_pushcfunction(L, ngx_lua_max_subrequests_get_total);
  lua_setfield(L, t, "max");
  
  lua_pushcfunction(L, ngx_lua_max_subrequests_get_active);
  lua_setfield(L, t, "active");
  
  lua_pushcfunction(L, ngx_lua_max_subrequests_get_remaining);
  lua_setfield(L, t, "remaining");
  return 1;
}

static ngx_int_t ngx_lua_max_subrequests_init_postconfig(ngx_conf_t *cf) {  
  if (ngx_http_lua_add_package_preload(cf, "ngx.max_subrequests", ngx_lua_max_subrequests_init_module) != NGX_OK) {
    return NGX_ERROR;
  }
  
  return NGX_OK;
}

static ngx_http_module_t  ngx_lua_max_subrequests_ctx = {
  NULL,                          /* preconfiguration */
  ngx_lua_max_subrequests_init_postconfig, /* postconfiguration */
  NULL,                          /* create main configuration */
  NULL,                          /* init main configuration */
  NULL,                          /* create server configuration */
  NULL,                          /* merge server configuration */
  NULL,                          /* create location configuration */
  NULL,                          /* merge location configuration */
};

static ngx_command_t  ngx_lua_max_subrequests_commands[] = {
  ngx_null_command
};

ngx_module_t  ngx_lua_max_subrequests_module = {
  NGX_MODULE_V1,
  &ngx_lua_max_subrequests_ctx,  /* module context */
  ngx_lua_max_subrequests_commands, /* module directives */
  NGX_HTTP_MODULE,               /* module type */
  NULL,                          /* init master */
  NULL,                          /* init module */
  NULL,                          /* init process */
  NULL,                          /* init thread */
  NULL,                          /* exit thread */
  NULL,                          /* exit process */
  NULL,                          /* exit master */
  NGX_MODULE_V1_PADDING
};
