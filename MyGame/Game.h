#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Mario.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include<unordered_map>

#include "Scene.h"
#include "Camera.h"

using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024

#define OVERWORLD_MAP	4
#define WORLD1_1_MAP	3
#define WORLD1_3_MAP	2

class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	/*float cam_x = 0.0f;
	float cam_y = 0.0f;*/
	CCamera* main_cam;
	CMario* player;

	int screen_width;
	int screen_height;

	unordered_map <int, LPSCENE > scenes;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);
public:
	void InitKeyboard();
	void SetKeyhHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void Init(HWND hWnd);
	void Draw(int nx,int ny,float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	void Load(LPCWSTR gameFile);
	int current_scene;
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(int scene_id);

	void SetMainCamera(CCamera*  cam) { this->main_cam = cam; }
	void SetMainPlayer(CMario* mario) { this->player = mario; }

	CCamera* GetMainCamera() { return this->main_cam; }
	CMario* GetPlayer() { return this->player; }

	void DeletePlayer() { this->player = NULL; };
	void DeleteCam() {
		main_cam->Unload();
		main_cam = NULL;
	}

	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }

	static void SweptAABB(
		float ml,
		float mt,
		float mr,
		float mb,
		float dx,
		float dy,
		float sl,
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny
	);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static CGame* GetInstance();
	//void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }

	~CGame();
};


