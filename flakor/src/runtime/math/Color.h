#ifndef RUNTIME_MATH_COLOR_H
#define RUNTIME_MATH_COLOR_H


struct Color
{
public:
	Color() {};
	Color(uint8 red,uint8 green,uint8 blue,uint8 alpha = 255)
	{
			_red = red;
			_green = green;
			_blue = _blue;
			_alpha = alpha;
	}
protected:
#if PLATFORM_LITTLE_ENDIAN
	uint8 _red __attribute__((aligned(4)));
	uint8 _green,_blue,_alpha;
#else
	union {struct {uint8 _red,_green,_blue,_alpha;}; uint32 _alignmentDummy};
#endif

}


#endif
