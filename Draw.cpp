#include "Draw.h"

SDL_Window* Draw::win = NULL;
SDL_Renderer* Draw::ren = NULL;
int Draw::W = 0;
int Draw::H = 0;
Vec2 Draw::ZERO(0, 0);
Color Draw::stored_color;
Color Draw::background_color;
bool Draw::isInited = false;
HWND Draw::hwnd;

int Draw::initDraw(string caption, int w, int h) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	//在屏幕中央创建窗口

	win = SDL_CreateWindow(caption.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (win == NULL)
		return -1;

	//创建渲染器
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
		return -2;



	//SDL_SetWindowTitle(win, "测试");

	//texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);

	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
	//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	//ren = r;
	W = w;
	H = h;
	background_color = Color(100, 100, 100, 255);
	isInited = true;

	hwnd = GetForegroundWindow();
	cout << hwnd << endl;
	return 0;
}

void Draw::quitDraw() {
	SDL_DestroyRenderer(ren);
	SDL_Quit();
	IMG_Quit();
}

void Draw::DrawLine(Line2D& line, Color& color) {
	Vec2 from = line.st + ZERO;
	Vec2 to = line.ed + ZERO;
	SetColor(color);
	SDL_RenderDrawLine(ren, round(from.x), round(from.y), round(to.x), round(to.y));
}

void Draw::DrawLine(Line2D& line) {
	DrawLine(line, Color::WHITE);
}

void Draw::SetColor(Color& c) {
	SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
}

void Draw::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(ren, r, g, b, a);
}

void Draw::StoreColor() {
	Uint8 a, r, g, b;
	SDL_GetRenderDrawColor(ren, &r, &g, &b, &a);
	stored_color = Color(r, g, b, a);
}

void Draw::FillScreen(int x, int y, int w, int h) {
	SDL_RenderFillRect(ren, NULL);
}

void Draw::CleanCanvas() {
	SDL_RenderClear(ren);
	StoreColor();//保存当前画笔颜色
	SetColor(background_color);
	FillScreen(0, 0, W, H);
	SetColor(stored_color);
}

void Draw::RefreshCanvas() {

	SDL_RenderPresent(ren);
}