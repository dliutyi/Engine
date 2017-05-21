#pragma once

#include <d3d11.h>

class CDX11Base
{
public:
	CDX11Base();
	~CDX11Base();

	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	void Shutdown();

	virtual bool LoadContent();
	virtual void UnloadContent();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

protected:
	HINSTANCE m_instance;
	HWND m_hwnd;

	D3D_DRIVER_TYPE m_driverType;
	D3D_FEATURE_LEVEL m_featureLevel;

	ID3D11Device* m_d3dDevice;
	ID3D11DeviceContext* m_d3dContext;
	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_backBufferTarget;
};