////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textureshaderclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

	void onoffAmbientLight();
	void onoffDiffuseLight();
	void onoffSpecularLight();
	
	void MoveForward();
	void MoveBack();
	void Moveleft();
	void MoveRight();

	bool HandleInput();

	bool InitializeTime();
	void TimeFrame();
	float GetTime();

	int m_frequency;
	float m_ticksPerMs;
	int m_startTime;
	float m_frameTime;

	CameraClass* m_Camera;
private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	ModelClass* m_Model;
	ModelClass* m_Ground;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	TextureShaderClass* m_TextureShader = nullptr;

	bool isAmbient;
	bool isDiffuse;
	bool isSpecular;

	XMFLOAT3 CamPos, CamRot;
	float speed = 2.0f;
	float PreX, PreY;
};

#endif