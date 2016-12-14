
extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#ifdef _DEBUG
#pragma comment(lib,"luaD.lib")
#else
#pragma comment(lib,"lua.lib")
#endif

bool RunLuaFile(const char *lpszLuaFile, int argc, const char *argv[])
{
	const char* szError = NULL;
	lua_State* L = lua_open();
	if ( L ){
		luaL_openlibs(L);
		if ( luaL_loadfile(L, lpszLuaFile) ) {
			szError = lua_tostring(L, 1);
			printf(szError);
			lua_pop(L, 1);
		}else{
			//����в�����ѹ�����
			if ( argv != NULL ) {
				for ( int i = 0; i < argc; ++i ) {
					lua_pushstring(L, argv[i]);  
				}//endfor
			}

			int err = lua_pcall(L, argc, LUA_MULTRET, 0);  
			if ( err ){
				szError = lua_tostring(L, 1);
				printf(szError);
				lua_pop(L, 1);
			}
		}

		lua_close(L);
	}

	return szError==NULL;
}

int main(int argc, const char *argv[])
{
	const char* lpszLuaFile = NULL;
	const char **args = NULL;
	int nLuaArgs = 0;

	if ( argc > 1 ) {
		lpszLuaFile = argv[1];
		if ( argc > 2 ) {
			args = &argv[2];
			nLuaArgs = argc - 2;
		}
	}

	if ( lpszLuaFile!=NULL ){
		if ( RunLuaFile((const char *)lpszLuaFile, nLuaArgs, args)==false ) {
			getc(stdin);
		}
	}else{
		printf("usage: LuaFile, [args]\nargs will be passed to LuaFile. 2009-08-02 by sing");
		getc(stdin);
	}

	return 0;
}