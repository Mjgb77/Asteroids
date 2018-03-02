#ifndef DRAWINGTOOL_HPP_
#define DRAWINGTOOL_HPP_

#include "Color.hpp"
#include "Vector2.hpp"
#include <vector>
#include "Font.hpp"

class DrawingTool
{
public:
	/*CONSTRUCTOR*/
	DrawingTool();

	/*PUBLIC FUNCTIONS*/
	
	static void DrawCircle(Vector2 position, float radius, Color lineColor, float lineWidth);
	
	static void DrawLineLoop(std::vector<Vector2> points, Vector2 position, Color lineColor, float lineWidth, float rotAng, float scale = 1.0f);
	
	static void DrawLineStrip(std::vector<Vector2> points, Vector2 position, Color lineColor, float lineWidth);
	
	static void DrawPolygon(std::vector<Vector2> points, Vector2 position, Color innerColor,  float rotAng, float scale = 1.0f);

	static void RenderText(std::string message, Font font, Color color, float x, float y);
};

#endif // !DRAWINGTOOL_HPP_
