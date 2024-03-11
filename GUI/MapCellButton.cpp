#include "MapEditor.h"
using namespace CampaignEditor;

MapCellButton::MapCellButton(int x, int y, int w, int h, int _x, int _y) : Fl_Button(x, y, w, h)
{
	this->x = _x;
	this->y = _y;
	std::cout << _x << "," << _y << std::endl;
}