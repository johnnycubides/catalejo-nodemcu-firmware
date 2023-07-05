// Module for interfacing with adc

#include "lua.h"
#include "module.h"
#include "lauxlib.h"
#include "platform.h"
#include "osc/osc.h"

#include <stdint.h>
#include <string.h>
#include "user_interface.h"

static int osc_set_ifs( lua_State* L)
{
  const char *address = luaL_checkstring(L, 1); // address
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
  const char *address = luaL_checkstring(L, 1); // address
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

/* static int osc_set_ffff( lua_State* L) */
/* { */
/*   const char *address = luaL_checkstring(L, 1); // address */
/*   float arg1 = (float)luaL_checknumber( L, 2 ); // arg3 float */
/*   float arg2 = (float)luaL_checknumber( L, 3 ); // arg3 float */
/*   float arg3 = (float)luaL_checknumber( L, 4 ); // arg3 float */
/*   float arg4 = (float)luaL_checknumber( L, 5 ); // arg4 float */

/*   char buffer[128]; */
/*   char *pBuffer = buffer; */

/*   int size = tosc_writeMessage( */
/*       buffer, */
/*       sizeof(buffer), */
/*       address, */
/*       "ffff", */
/*       arg1, */
/*       arg2, */
/*       arg3, */
/*       arg4 */
/*       ); */
/*   lua_pushlstring(L, pBuffer, size); */
/*   lua_pushinteger(L, size); */
/*   return 2; */
/* } */

/* static int osc_get_ifs( lua_State* L) */
/* { */
/*   uint8_t size = luaL_checkinteger(L, 1); */
/*   const char *pBuffer = luaL_checkstring(L, 2); // buffer */

/*   int len = strlen(pBuffer); // the number of bytes read from the socket */
/*   tosc_message osc; // declare the TinyOSC structure */

/*   char buffer[size +1]; */
/*   /1* strcpy(buffer, pBuffer); *1/ */
/*   memcpy(buffer, pBuffer, size+1); */

/*   char address[24]; */
/*   char *pAddress = address; */
/*   /1* char *pAddress; *1/ */
/*   int argInt = 0; */
/*   int argFloat = 0.0; */
  
/*   if (!tosc_parseMessage(&osc, buffer,size)) */
/*   { */
/*     pAddress = tosc_getAddress(&osc); */
/*     argInt = tosc_getNextInt32(&osc); */
/*     argFloat = tosc_getNextFloat(&osc); */
/*     const char *text = tosc_getNextString(&osc); */
/*     lua_pushlstring(L, pAddress, strlen(pAddress)); */
/*     lua_pushinteger(L, argInt); */
/*     lua_pushnumber(L, argFloat); */
/*     lua_pushlstring(L, text, strlen(text)); */
/*     return 5; */
/*   } */
/*   lua_pushlstring(L, pAddress, strlen(pAddress)); */
/*   lua_pushinteger(L, argInt); */
/*   lua_pushnumber(L, argFloat); */
/*   lua_pushlstring(L, "empty", 5); */
/*   return 5; */
/* } */

static int osc_get_iifs( lua_State* L)
{
  uint8_t size = luaL_checkinteger(L, 1);
  const char *pBuffer = luaL_checkstring(L, 2); // buffer

  int len = strlen(pBuffer); // the number of bytes read from the socket
  tosc_message osc; // declare the TinyOSC structure

  char buffer[size +1];
  /* strcpy(buffer, pBuffer); */
  memcpy(buffer, pBuffer, size+1);

  char address[24];
  char *pAddress = address;
  /* char *pAddress; */
  int argInt[] = {0,0};
  float argFloat = 0.0;
  
  if (!tosc_parseMessage(&osc, buffer,size))
  {
    pAddress = tosc_getAddress(&osc);
    argInt[0] = tosc_getNextInt32(&osc);
    argInt[1] = tosc_getNextInt32(&osc);
    argFloat = tosc_getNextFloat(&osc);
    const char *text = tosc_getNextString(&osc);
    lua_pushlstring(L, pAddress, strlen(pAddress));
    lua_pushinteger(L, argInt[0]);
    lua_pushinteger(L, argInt[1]);
    lua_pushnumber(L, argFloat);
    lua_pushlstring(L, text, strlen(text));
    return 5;
  }
  lua_pushlstring(L, pAddress, strlen(pAddress));
  lua_pushinteger(L, argInt[0]);
  lua_pushinteger(L, argInt[1]);
  lua_pushnumber(L, argFloat);
  lua_pushlstring(L, "e", 1);
  return 5;
}

/* static int osc_get_iiff( lua_State* L) */
/* { */
/*   uint8_t size = luaL_checkinteger(L, 1); */
/*   const char *pBuffer = luaL_checkstring(L, 2); // buffer */

/*   int len = strlen(pBuffer); // the number of bytes read from the socket */
/*   tosc_message osc; // declare the TinyOSC structure */

/*   char buffer[size +1]; */
/*   /1* strcpy(buffer, pBuffer); *1/ */
/*   memcpy(buffer, pBuffer, size+1); */

/*   char address[24]; */
/*   char *pAddress = address; */
/*   /1* char *pAddress; *1/ */
/*   int argInt[] = {0,0}; */
/*   int argFloat[] = {0.0,0.0}; */
  
/*   if (!tosc_parseMessage(&osc, buffer,size)) */
/*   { */
/*     pAddress = tosc_getAddress(&osc); */
/*     argInt[0] = tosc_getNextInt32(&osc); */
/*     argInt[1] = tosc_getNextInt32(&osc); */
/*     argFloat[0] = tosc_getNextFloat(&osc); */
/*     argFloat[1] = tosc_getNextFloat(&osc); */
/*   } */

/*   lua_pushlstring(L, pAddress, strlen(pAddress)); */
/*   lua_pushinteger(L, argInt[0]); */
/*   lua_pushinteger(L, argInt[1]); */
/*   lua_pushnumber(L, argFloat[0]); */
/*   lua_pushnumber(L, argFloat[1]); */

/*   return 5; */
/* } */

/* static int osc_get_ffff( lua_State* L) */
/* { */
/*   uint8_t size = luaL_checkinteger(L, 1); */
/*   const char *pBuffer = luaL_checkstring(L, 2); // buffer */

/*   int len = strlen(pBuffer); // the number of bytes read from the socket */
/*   tosc_message osc; // declare the TinyOSC structure */

/*   char buffer[size +1]; */
/*   /1* strcpy(buffer, pBuffer); *1/ */
/*   memcpy(buffer, pBuffer, size+1); */

/*   char address[24]; */
/*   char *pAddress = address; */
/*   /1* char *pAddress; *1/ */
/*   float arg[4] = {0,0,0,0}; */
  
/*   /1* arg[3] = tosc_parseMessage(&osc, buffer, size); *1/ */
/*   if (!tosc_parseMessage(&osc, buffer,size)) */
/*   { */
/*     pAddress = tosc_getAddress(&osc); */
/*     for (uint8_t i = 0; osc.format[i] != '\0'; i++) */
/*     { */
/*       /1* arg[i] = 0.0; *1/ */
/*       arg[i] = tosc_getNextFloat(&osc); */
/*     } */
/*   } */

/*   lua_pushlstring(L, pAddress, strlen(pAddress)); */
/*   for (uint8_t i = 0; i < 4; i++) */
/*   { */
/*     lua_pushnumber(L, arg[i]); */
/*   } */
/*   return 5; */
/* } */

LROT_BEGIN(osc, NULL, 0)
  LROT_FUNCENTRY( set_ifs, osc_set_ifs )
  LROT_FUNCENTRY( set_iiff, osc_set_iiff )
  /* LROT_FUNCENTRY( set_ffff, osc_set_ffff ) */
  /* LROT_FUNCENTRY( get_ifs, osc_get_ifs ) */
  LROT_FUNCENTRY( get_iifs, osc_get_iifs )
  /* LROT_FUNCENTRY( get_ffff, osc_get_ffff ) */
LROT_END(osc, NULL, 0)


NODEMCU_MODULE(OSC, "osc", osc, NULL);
