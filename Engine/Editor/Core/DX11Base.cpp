#include "DX11Base.h"
#include "CoreDefs.h"

CDX11Base::CDX11Base()
	: m_driverType(D3D_DRIVER_TYPE_NULL)
	, m_featureLevel(D3D_FEATURE_LEVEL_11_0)
	, m_d3dDevice(0)
	, m_d3dContext(0)
	, m_swapChain(0)
	, m_backBufferTarget(0)
{
}

bool CDX11Base::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	m_instance = hInstance;
	m_hwnd = hwnd;

	RECT dimensions;
	GetClientRect(hwnd, &dimensions);

	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions.bottom - dimensions.top;

	D3D_DRIVER_TYPE driverTypes[] = { D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE };
	unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
	unsigned int totalFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	unsigned int creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT result;
	unsigned int driver = 0;

	for (driver = 0; driver < totalDriverTypes; ++driver)
	{
		result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0, creationFlags, featureLevels, totalFeatureLevels, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_d3dDevice, &m_featureLevel, &m_d3dContext);

		if (SUCCEEDED(result))
		{
			m_driverType = driverTypes[driver];
			break;
		}
	}

	ERROR_HANDLE(result, "Failed to create the Direct3D device!")

	ID3D11Texture2D* backBufferTexture;
	result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);

	ERROR_HANDLE(result, "Failed to get the swap chain back buffer!")

	result = m_d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &m_backBufferTarget);

	if (backBufferTexture)
	{
		backBufferTexture->Release();
	}

	ERROR_HANDLE(result, "Failed to create the render target view!")

	m_d3dContext->OMSetRenderTargets(1, &m_backBufferTarget, 0);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	m_d3dContext->RSSetViewports(1, &viewport);

	return LoadContent();
}

CDX11Base::~CDX11Base()
{
	Shutdown();
}

bool CDX11Base::LoadContent()
{
	return true;
}

void CDX11Base::UnloadContent()
{
}

void CDX11Base::Shutdown()
{
	UnloadContent();

	if (m_backBufferTarget)
	{
		m_backBufferTarget->Release();
	}
	if (m_swapChain)
	{
		m_swapChain->Release();
	}
	if (m_d3dContext)
	{
		m_d3dContext->Release();
	}
	if (m_d3dDevice)
	{
		m_d3dDevice->Release();
	}

	m_d3dDevice = 0;
	m_d3dContext = 0;
	m_swapChain = 0;
	m_backBufferTarget = 0;
}