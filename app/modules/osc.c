// Module for interfacing with adc

#include "module.h"
#include "lauxlib.h"
#include "platform.h"

#include <stdint.h>
#include "user_interface.h"

static int osc_set( lua_State* L)
{
  unsigned id = luaL_checkinteger( L, 1 );
  lua_pushinteger( L, 3);
  return 1;
}

LROT_BEGIN(osc, NULL, 0)
  LROT_FUNCENTRY( set, osc_set )
LROT_END(osc, NULL, 0)


NODEMCU_MODULE(OSC, "osc", osc, NULL);
