/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "GameStateManager.h"

#pragma optimize( "", off )

int main( int /*_argc*/, char** /*_args[]*/ )
{
	GameStateManager gameMgr;

	while ( !gameMgr.Quit() )
	{
		gameMgr.Update();
	}

	return 0;
}

#pragma optimize( "", on )