/* GLM Studio @ copyright 2018 */

#include "stdafx.h"
#include "MoneyManager.h"

void MoneyManager::Render( Renderer* _renderer, FontManager* _fonter ) const
{
	std::stringstream oss;
	oss << "Money: " << money;
	_renderer->DrawText( 350, 750, 0, 0, 255, oss.str().c_str(), _fonter->Small() );
}

void MoneyManager::AddMoney( int _money )
{
	money += _money;
}

int MoneyManager::GetScore() const
{
	return money;
}