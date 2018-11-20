/* GLM Studio @ copyright 2018 */

#pragma once

class FontManager;

class MoneyManager
{
public:
	static MoneyManager* GetInstance()
	{
		static MoneyManager instance;
		return &instance;
	}

	void		Render( Renderer* _renderer, FontManager* _fonter ) const;
	void		AddMoney( int _money );
	int			GetScore() const;

private:
	int money = 90;
};