/* GLM Studio @ copyright 2018 */

#pragma once

class MoneyManager
{
public:
	static MoneyManager* GetInstance()
	{
		static MoneyManager instance;
		return &instance;
	}

	void Render( SDL_Renderer* _renderer, TTF_Font* _font ) const;
	void AddMoney( int _money );

private:
	int money = 0;
};