#include <genesis.h>

#include "CrowdManager.h"
/*#include "ActionsManager.h"
#include "MoneyManager.h"

#include "SGDKRenderer.h"
#include "SGDKEvent.h"*/

#pragma optimize( "", off )

int main()
{
	/*srand( ( int )( time( NULL ) ) );*/

	int quit = 0;

	/*float deltaTime = EventManager::FIXED_TIME_STAMP;
	bool pause = false;

	// add options
	ActionsManager::GetInstance()->AddSelect( Vector2( 0.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option1" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 135.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option2" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 270.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option3" );
	ActionsManager::GetInstance()->AddSelect( Vector2( 405.0f, 870.0f ), Vector2( 135.0f, 90.0f ), "option4" );

	ActionsManager::GetInstance()->AddServe( Vector2( 0.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar1", 0 );
	ActionsManager::GetInstance()->AddServe( Vector2( 180.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar2", 1 );
	ActionsManager::GetInstance()->AddServe( Vector2( 360.0f, 640.0f ), Vector2( 180.0f, 90.0f ), "bar3", 2 );

	Renderer* renderer = new SGDKRenderer;
	EventManager* eventer = new SGDKEventManager;

	renderer->Init();

	// TEMP
	Texture* gTexture = renderer->LoadTexture( "affiche.jpg" );*/

	while ( !quit )
	{
		/*eventer->Update( quit, pause, deltaTime );

		// UPDATE
		ActionsManager::GetInstance()->Update( deltaTime );
		const int level = MoneyManager::GetInstance()->GetScore() / 100;
		CrowdManager::GetInstance()->Update( deltaTime * ( 1.0f + level * 0.1f ) );

		// RENDER
		renderer->StartRender();

		ActionsManager::GetInstance()->Render( renderer );
		CrowdManager::GetInstance()->Render( renderer );

		MoneyManager::GetInstance()->Render( renderer );
		RenderStatic( renderer );

		std::stringstream oss;
		oss << "Level: " << level + 1;
		renderer->DrawText( 450, 50, 0, 0, 0, oss.str().c_str() );

		if ( pause )
		{
			renderer->DrawBG( gTexture, 0, 0 );
			DrawPause( renderer );
		}
		else
		{
			DrawTitle( renderer );
		}

		renderer->EndRender();*/
	}

	/*renderer->FreeTexture( gTexture );
	renderer->ShutDown();*/

	return 0;
}