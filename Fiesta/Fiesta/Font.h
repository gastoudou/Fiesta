#pragma once

class Font
{
public:
	enum Format
	{
		CENTER = 0,
		LEFT,
	};
};

class FontManager
{
public:

	virtual void Init() = 0;
	virtual void ShutDown() = 0;
	virtual Font* Normal() const = 0;
	virtual Font* Small() const = 0;

protected:
	bool init = false;
};