////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_Ground = 0;
	m_LightShader = 0;
	m_Light = 0;
	isAmbient = true;
	isDiffuse = true;
	isSpecular = true;

	CamPos.x = 0.0f;
	CamPos.y = 0.0f;
	CamPos.z = 0.0f;

	CamRot.x = 0.0f;
	CamRot.y = 0.0f;
	CamRot.z = 0.0f;

	PreX = 0.0f;
	PreY = 0.0f;
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
	float cameraX, cameraY, cameraZ;
	XMMATRIX baseViewMatrix;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);	// for chair
	
	//m_Camera->Render();
	//m_Camera->GetViewMatrix(baseViewMatrix);

	//// Set the initial position of the camera.
	//cameraX = 50.0f;
	//cameraY = 2.0f;
	//cameraZ = -7.0f;

	//m_Camera->SetPosition(cameraX, cameraY, cameraZ);

	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/poste_obj.obj", L"./data/metal.dds");
//	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/chair.obj", L"./data/chair_d.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Ground = new ModelClass;
	if (!m_Ground)
	{
		return false;
	}

	result = m_Ground->Ground(m_D3D->GetDevice(), L"./data/plane.obj", L"./data/ground.dds");
	//	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/chair.obj", L"./data/chair_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	/*result = m_Ground->Ground(m_D3D->GetDevice(), L"./data/ground.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}*/


	//// Create the texture shader object.
	//m_TextureShader = new TextureShaderClass;
	//if (!m_TextureShader)
	//{
	//	return false;
	//}

	//// Initialize the texture shader object.
	//result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	//m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light->SetAmbientColor(-1.0f, -1.0f, -1.0f, -1.0f);
	
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light->SetDiffuseColor(-1.0f, -1.0f, -1.0f, -1.0f);
	//m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);

//	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
//	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
//	m_Light->SetDirection(1.0f, 0.0f, 0.0f);
	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	//m_Light->SetSpecularColor(-1.0f, -1.0f, -1.0f, -1.0f);


	m_Light->SetSpecularPower(16.0f);
	//m_Light->SetSpecularPower(-1.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if (m_Ground)
	{
		m_Ground->Shutdown();
		delete m_Ground;
		m_Ground = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// m_TextureShader °´Ã¼ ¹İÈ¯
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
	
	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}



	return true;
}

void GraphicsClass::onoffAmbientLight()
{
	if (isAmbient) {
		m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 0.0f);
		isAmbient = false;
	}
	else {
		m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		isAmbient = true;
	}

}

void GraphicsClass::onoffDiffuseLight()
{
	if (isDiffuse) {
		m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);
		isDiffuse = false;
	}
	else {
		m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
		isDiffuse = true;
	}

}

void GraphicsClass::onoffSpecularLight()
{
	if (isSpecular) {
		m_Light->SetSpecularColor(0.0f, 0.0f, 0.0f, 0.0f);;
		m_Light->SetSpecularPower(10000.0f);
		isSpecular = false;
	}
	else {
		m_Light->SetSpecularColor(0.0f, 0.0f, 0.0f, 0.0f);;
		m_Light->SetSpecularPower(16.0f);
		isSpecular = true;
	}
}

void GraphicsClass::MoveForward()
{
	m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z + 0.00001f);
}

void GraphicsClass::MoveBack()
{
	m_Camera->SetPosition(m_Camera->GetPosition().x - 0.00001f, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
}

void GraphicsClass::Moveleft()
{
	m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z - 0.00001f);
}

void GraphicsClass::MoveRight()
{
	m_Camera->SetPosition(m_Camera->GetPosition().x + 0.00001f, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
}

bool GraphicsClass::InitializeTime()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (m_frequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every millisecond.
	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;

}

void GraphicsClass::TimeFrame()
{
	int currentTime;
	float timeDifference;


	// Query the current time.
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	// Calculate the difference in time since the last time we queried for the current time.
	timeDifference = (float)(currentTime - m_startTime);

	// Calculate the frame time by the time difference over the timer speed resolution.
	m_frameTime = timeDifference / m_ticksPerMs;

	// Restart the timer.
	m_startTime = currentTime;

	return;
}

float GraphicsClass::GetTime()
{
	return m_frameTime;
}


bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix, ScaleMatrix;

	bool result;
	
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//worldMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(0.0f, -1.0f, 0.0f);
	//ScaleMatrix = XMMatrixScaling(0.002f, 0.002f, 0.002f);
	ScaleMatrix = XMMatrixScaling(0.007f, 0.007f, 0.007f);
	worldMatrix = ScaleMatrix * worldMatrix * translateMatrix;

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), 
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	
	if(!result)
	{
		return false;
	}

	worldMatrix = XMMatrixRotationX(0.0f);
	//worldMatrix = XMMatrixRotationX(-0.5f);
	//worldMatrix = XMMatrixRotationY(rotation);
	translateMatrix = XMMatrixTranslation(49.5f, 48.0f, -1.35f);
	//ScaleMatrix = XMMatrixScaling(5.0f, 1.0f, 10.0f);
	ScaleMatrix = XMMatrixScaling(5.0f, 1.0f, 30.0f);
	//ScaleMatrix = XMMatrixScaling(100.0f, 100.0f, 100.0f);
	worldMatrix = translateMatrix * ScaleMatrix * worldMatrix;

	m_Ground->Render(m_D3D->GetDeviceContext());

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Ground->GetVertexCount(), m_Ground->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix,
		m_Ground->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	//Render the model using the texture shader.
	/*result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Ground->GetIndexCount(), m_Model->GetInstanceCount(),
		worldMatrix, viewMatrix, projectionMatrix, m_Ground->GetTexture());
	if (!result)
	{
		return false;
	}*/


	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}