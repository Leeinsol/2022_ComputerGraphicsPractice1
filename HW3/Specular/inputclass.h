////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_
#include <directxmath.h>
#include <dinput.h>

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize(HINSTANCE);

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
	LPDIRECTINPUT8 DirectInput;

	bool IsKeyDown(unsigned int);
	bool InitDirectInput(HINSTANCE);
	void DetectInput(double time);

	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	XMMATRIX camRotationMatrix;
	XMMATRIX groundWorld;

	float moveLeftRight = 0.0f;
	float moveBackForward = 0.0f;

	float camYaw = 0.0f;
	float camPitch = 0.0f;

	void UpdateCamera();

	XMMATRIX camView;
	XMMATRIX camProjection;

	XMVECTOR camPosition;
	XMVECTOR camTarget;
	XMVECTOR camUp;

	DIMOUSESTATE mouseLastState;
	HWND hwnd = NULL;
	__int64 frameTimeOld = 0;


	double GetFrameTime();
	IDirectInputDevice8* DIKeyboard;
	IDirectInputDevice8* DIMouse;

	bool IsLeftPressed();
	bool IsRightPressed();
	bool IsUpPressed();
	bool IsDownPressed();

private:
	bool m_keys[256];

};

#endif