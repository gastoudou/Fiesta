/* GLM Studio @ copyright 2018 */

#pragma once

class FontManager;

class MoneyManager
{
public:
	MoneyManager() = default;
	~MoneyManager() = default;

	static MoneyManager* GetInstance()
	{
		static MoneyManager instance;
		return &instance;
	}

	void Render( Renderer* _renderer, FontManager* _fonter ) const;
	void RenderDebug( Renderer* _renderer, FontManager* _fonter ) const;
	void ShutDown();

	void AddMoney( int _money );
	int GetScore() const;

private:
	int money = 90;
};