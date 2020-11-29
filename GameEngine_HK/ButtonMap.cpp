#include "include/ButtonMap.h"

std::map<std::string, Button*> ButtonMap::buttons;

std::map<std::string, Button*>& ButtonMap::GetMap()
{
	return buttons;
}
