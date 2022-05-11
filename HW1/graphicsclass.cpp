////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	red = 0.0f;
	green = 0.0f;
	blue = 0.0f;

	brightness = 1.0f;
	
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Model2 = 0;
	m_Model3 = 0;
	m_ColorShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the model object.
	m_Model = new ModelClass;

	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Hexagon(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Model2 = new ModelClass;

	if (!m_Model2)
	{
		return false;
	}

	result = m_Model2->Pentagon(m_D3D->GetDevice());
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Model3 = new ModelClass;

	if (!m_Model3)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model3->Heptagon(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}
	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}
	if (m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}
	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	//rotation
	static float rotation = 0.0f;

	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation,red,green,blue,brightness);

	if (!result)
	{
		return false;
	}

	return true;
}



bool GraphicsClass::Render(float rotation, float red, float green, float blue,float bright)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	// backgroung color
	m_D3D->BeginScene(red, green, blue, bright);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);


	worldMatrix =XMMatrixRotationX(rotation);
	translateMatrix=XMMatrixTranslation(-3.5f, 0.0f, 0.0f);
	worldMatrix=XMMatrixMultiply(worldMatrix, translateMatrix);
	

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, bright);
	if (!result)
	{
		return false;
	}


	worldMatrix = XMMatrixRotationY(rotation);


	m_Model2->Render(m_D3D->GetDeviceContext());

	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, bright);
	if (!result)
	{
		return false;
	}

	worldMatrix = XMMatrixRotationZ(rotation);
	translateMatrix = XMMatrixTranslation(4.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	m_Model3->Render(m_D3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(),
		worldMatrix, viewMatrix, projectionMatrix, bright);
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::ChangeBackgroundRed()
{
	red = 1.0f;
	green = 0.0f;
	blue = 0.0f;
}

void GraphicsClass::ChangeBackgroundGreen()
{
	red = 0.0f;
	green = 1.0f;
	blue = 0.0f;
}

void GraphicsClass::ChangeBackgroundBlue()
{
	red = 0.0f;
	green = 0.0f;
	blue = 1.0f;
}

void GraphicsClass::ChangeFillMode(int mode)
{
	m_D3D->fillmode = mode;
	m_D3D->ChangeRasterizerState();
}

void GraphicsClass::ChangeBrightnss(float bright)
{
	brightness = bright;
}


