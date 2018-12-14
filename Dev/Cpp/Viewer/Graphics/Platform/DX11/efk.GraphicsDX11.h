
#pragma once

#include <Effekseer.h>
#include <EffekseerRendererDX11/EffekseerRenderer/EffekseerRendererDX11.Renderer.h>
#include <EffekseerRendererDX11/EffekseerRenderer/EffekseerRendererDX11.RendererImplemented.h>

#include "../../efk.Graphics.h"

namespace efk
{
	class RenderTextureDX11
		: public RenderTexture
	{
	private:
		Graphics* graphics = nullptr;
		int32_t width = 0;
		int32_t height = 0;

		ID3D11Texture2D*			texture = nullptr;
		ID3D11ShaderResourceView*	textureSRV = nullptr;
		ID3D11RenderTargetView*		textureRTV = nullptr;

	public:
		RenderTextureDX11(Graphics* graphics);
		virtual ~RenderTextureDX11();
		bool Initialize(int32_t width, int32_t height);

		int32_t GetWidth() { return width; }
		int32_t GetHeight() { return height; }

		ID3D11RenderTargetView* GetRenderTargetView() const { return textureRTV; }

		ID3D11ShaderResourceView* GetShaderResourceView() const { return textureSRV; }

		uint64_t GetViewID() override { return (uint64_t)textureSRV; }
	};

	class DepthTextureDX11
		: public DepthTexture
	{
	private:
		Graphics* graphics = nullptr;
		int32_t width = 0;
		int32_t height = 0;

		ID3D11Texture2D*			depthBuffer = nullptr;
		ID3D11DepthStencilView*		depthStencilView = nullptr;
		ID3D11ShaderResourceView*	depthSRV = nullptr;

	public:
		DepthTextureDX11(Graphics* graphics);
		virtual ~DepthTextureDX11();
		bool Initialize(int32_t width, int32_t height);

		ID3D11DepthStencilView* GetDepthStencilView() const { return depthStencilView; }

		ID3D11ShaderResourceView* GetShaderResourceView() const { return depthSRV; }
	};


	class GraphicsDX11
		: public Graphics
	{
	private:
		void*	windowHandle = nullptr;
		int32_t	windowWidth = 0;
		int32_t	windowHeight = 0;
		bool				isSRGBMode = false;

		ID3D11Device*			device = nullptr;
		ID3D11DeviceContext*	context = nullptr;
		IDXGIDevice1*			dxgiDevice = nullptr;
		IDXGIAdapter*			adapter = nullptr;
		IDXGIFactory*			dxgiFactory = nullptr;
		IDXGISwapChain*			swapChain = nullptr;

		ID3D11Texture2D*		defaultRenderTarget = nullptr;
		ID3D11Texture2D*		defaultDepthStencil = nullptr;
		ID3D11RenderTargetView*	renderTargetView = nullptr;
		ID3D11DepthStencilView*	depthStencilView = nullptr;

		ID3D11Texture2D*		backTexture = nullptr;
		ID3D11ShaderResourceView*	backTextureSRV = nullptr;

		ID3D11Texture2D*			recordingTexture = nullptr;
		ID3D11RenderTargetView*		recordingTextureRTV = nullptr;
		ID3D11Texture2D*			recordingDepthStencil = nullptr;
		ID3D11DepthStencilView*		recordingDepthStencilView = nullptr;
		int32_t				recordingWidth = 0;
		int32_t				recordingHeight = 0;

		ID3D11RenderTargetView*	currentRenderTargetView = nullptr;
		ID3D11DepthStencilView*	currentDepthStencilView = nullptr;

		ID3D11RenderTargetView*	backupRenderTargetView = nullptr;
		ID3D11DepthStencilView*	backupDepthStencilView = nullptr;

		/*
		LPDIRECT3D9			d3d = nullptr;
		LPDIRECT3DDEVICE9	d3d_device = nullptr;
		
		IDirect3DSurface9*	renderDefaultTarget = nullptr;
		IDirect3DSurface9*	renderDefaultDepth = nullptr;

		IDirect3DSurface9*	backTarget = nullptr;
		IDirect3DTexture9*	backTargetTexture = nullptr;
		*/

		EffekseerRendererDX11::Renderer*	renderer = nullptr;

	public:
		GraphicsDX11();
		virtual ~GraphicsDX11();

		bool Initialize(void* windowHandle, int32_t windowWidth, int32_t windowHeight, bool isSRGBMode, int32_t spriteCount) override;

		void CopyToBackground() override;

		void Resize(int32_t width, int32_t height) override;

		bool Present() override;

		void BeginScene() override;

		void EndScene() override;

		void SetRenderTarget(RenderTexture* renderTexture, DepthTexture* depthTexture) override;

		void BeginRecord(int32_t width, int32_t height) override;

		void EndRecord(std::vector<Effekseer::Color>& pixels) override;

		void Clear(Effekseer::Color color) override;

		void ResetDevice() override;

		void* GetBack() override;

		EffekseerRenderer::Renderer* GetRenderer() override;

		DeviceType GetDeviceType() const override { return DeviceType::DirectX11; }
	};
}
