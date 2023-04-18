// Module for interfacing with adc

#include "lua.h"
#include "module.h"
#include "lauxlib.h"
#include "platform.h"
#include "osc/osc.h"

#include <stdint.h>
#include "user_interface.h"

static int osc_set_ifs( lua_State* L)
{
  const char *address = luaL_checkstring(L, 1); // adress
  unsigned arg1 = luaL_checkinteger( L, 2 ); // arg1 integer
  float arg2 = (float)luaL_checknumber( L, 3 ); // arg2 float
  const char *arg3 = luaL_checkstring(L, 4);  // arg3 string

  char buffer[128];
  char *pBuffer = buffer;

  int size = tosc_writeMessage(
      buffer,
      sizeof(buffer),
      address,
      "ifs",
      arg1,
      arg2,
      arg3
      );
  lua_pushlstring(L, pBuffer, size);
  lua_pushinteger(L, size);
  return 2;
}

static int osc_set_iiff( lua_State* L)
{
  const char *address = luaL_checkstring(L, 1); // adress
  unsigned arg1 = luaL_checkinteger( L, 2 ); // arg1 integer
  unsigned arg2 = luaL_checkinteger( L, 3 ); // arg2 integer
  float arg3 = (float)luaL_checknumber( L, 4 ); // arg3 float
  float arg4 = (float)luaL_checknumber( L, 5 ); // arg4 float

  char buffer[128];
  char *pBuffer = buffer;

  int size = tosc_writeMessage(
      buffer,
      sizeof(buffer),
      address,
      "iiff",
      arg1,
      arg2,
      arg3,
      arg4
      );
  lua_pushlstring(L, pBuffer, size);
  lua_pushinteger(L, size);
  return 2;
}

LROT_BEGIN(osc, NULL, 0)
  LROT_FUNCENTRY( set_ifs, osc_set_ifs )
  LROT_FUNCENTRY( set_iiff, osc_set_iiff )
LROT_END(osc, NULL, 0)


NODEMCU_MODULE(OSC, "osc", osc, NULL);
