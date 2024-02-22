#include "D2DSprites.h"

D2DSprites::D2DSprites() : index(0), width(0), height(0), keycolor(0),
centorX(0), centorY(0), DelayFrame(0), damage(0), oriX(0), oriY(0), sheetIndex(0),
collision1(RECT{ 0,0,0,0 }),
collision2(RECT{ 0,0,0,0 })
{
}

D2DSprites::D2DSprites(int index, int width,
	int height, int KeyColor, int centerPosX, int centerPosY, 
	int delayFrame,const RECT& collision1, const RECT& collision2, int damage)
	: index(index), width(width), height(height), keycolor(KeyColor), 
	centorX(centerPosX), centorY(centerPosY), DelayFrame(delayFrame), collision1(collision1),
	collision2(collision2),damage(damage), oriX(0),oriY(0),sheetIndex(0)
{

}
