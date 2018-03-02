#include "DrawingTool.hpp"
#include "MathUtilities.hpp"

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL.h>
#include <SDL_ttf.h>

const int CIRCLE_PRECISSION = 100; //Greater is Better, don't use 0!

DrawingTool::DrawingTool() {
}

void SetUp (Vector2 position, Color color, float rotAng = 0.0f, float scale = 1.0f) {
	glLoadIdentity(); //Restart Identity Matrix
	glTranslatef(position.x, position.y, 0.0f);

	if (rotAng != 0.0f) glRotatef(rotAng, 0.0f, 0.0f, 1.0f); //If it is not default rotation angle 

	if (scale != 1.0f) glScalef(scale, scale, 0.0f);

	glColor4f(color.red, color.green, color.blue, color.alpha);


}

void DrawingTool::DrawCircle(Vector2 position, float radius, Color lineColor, float lineWidth)
{
	float PI2 = MathUtilities::PI*2.0f;
	float delta = PI2 / CIRCLE_PRECISSION;

	SetUp(position, lineColor);
	glLineWidth(lineWidth);

	glBegin(GL_LINE_LOOP);

	for (float ang = 0; ang < PI2; ang += delta)
		glVertex2f(radius*cos(ang), sin(ang));

	glEnd();
}


void DrawingTool::DrawLineStrip(std::vector<Vector2> points, Vector2 position, Color lineColor, float lineWidth)
{
	SetUp(position, lineColor, lineWidth);
	glLineWidth(lineWidth);

	glBegin(GL_LINE_STRIP);

	for (Vector2 point : points)
		glVertex2f(point.x, point.y);

	glEnd();
}

void DrawingTool::DrawLineLoop(std::vector<Vector2> points, Vector2 position, Color lineColor, float lineWidth, float rotAng, float scale)
{
	SetUp(position, lineColor, rotAng, scale);
	glLineWidth(lineWidth);

	glBegin(GL_LINE_LOOP);

	for (Vector2 point : points)
		glVertex2f(point.x, point.y);

	glEnd();
}

void DrawingTool::DrawPolygon(std::vector<Vector2> points, Vector2 position, Color innerColor, float rotAng, float scale)
{
	SetUp(position, innerColor, rotAng, scale);

	glBegin(GL_POLYGON);

	for (Vector2 point : points)
		glVertex2f(point.x, point.y);

	glEnd();
}

unsigned int power_two_floor(unsigned int val) {
	unsigned int power = 2, nextVal = power * 2;
	while ((nextVal *= 2) <= val)
		power *= 2;
	return power * 2;
}


void DrawingTool::RenderText(std::string message, Font font, Color color, float x, float y)
{
	glLoadIdentity();
	glTranslatef(x, y, 0.f);

	SDL_Color sdlColor;
	sdlColor.a = 255 * color.alpha;
	sdlColor.r = 255 * color.red;
	sdlColor.g = 255 * color.green;
	sdlColor.b = 255 * color.blue;
	
	SDL_Surface *surface;

	//Render font to a SDL_Surface
	if ((surface = TTF_RenderText_Blended(font.m_font, message.c_str(), sdlColor)) == nullptr) {
		TTF_CloseFont(font.m_font);
		puts("TTF_RenderText error: ");
		return;
	}

	GLuint texId;

	//Generate OpenGL texture
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	//Avoid mipmap filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Find the first power of two for OpenGL image 
	int w = power_two_floor(surface->w) * 2;
	int h = power_two_floor(surface->h) * 2;

	//Create a surface to the correct size in RGB format, and copy the old image

	SDL_Surface * s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(surface, NULL, s, NULL);

	//Copy the created image into OpenGL format
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);

	//Draw the OpenGL texture as a Quad
	glBegin(GL_QUADS); {
		glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(0.0f + surface->w, 0.0f, 0.0f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(0.0f + surface->w, 0.0f + surface->h, 0.0f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, 0.0f + surface->h, 0.0f);
	} glEnd();
	glDisable(GL_TEXTURE_2D);

	//Cleanup
	SDL_FreeSurface(s);
	SDL_FreeSurface(surface);
	glDeleteTextures(1, &texId);
}
