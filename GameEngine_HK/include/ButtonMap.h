#pragma once

#include<SFML/Graphics.hpp>
#include "Button.h"

static class ButtonMap
{
private:
	static std::map<std::string, Button*> buttons;

public:
	static std::map<std::string, Button*>& GetMap();
};

