
#include "efk.LineRendererDX11.h"

namespace efk
{
	namespace Standard_VS
	{
		static
#include <EffekseerRendererDX11/EffekseerRenderer/Shader/EffekseerRenderer.Standard_VS.h>
	}

	namespace Standard_PS
	{
		static
#include <EffekseerRendererDX11/EffekseerRenderer/Shader/EffekseerRenderer.Standard_PS.h>
	}

	namespace StandardNoTexture_PS
	{
		static
#include <EffekseerRendererDX11/EffekseerRenderer/Shader/EffekseerRenderer.StandardNoTexture_PS.h>
	}

	LineRendererDX11::LineRendererDX11(EffekseerRenderer::Renderer* renderer)
		: LineRenderer(renderer)
	{
		this->renderer = (EffekseerRendererDX11::RendererImplemented*)renderer;


		// Position(3) Color(1) UV(2)
		D3D11_INPUT_ELEMENT_DESC decl[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		shader = EffekseerRendererDX11::Shader::Create(
			this->renderer,
			Standard_VS::g_VS,
			sizeof(Standard_VS::g_VS),
			StandardNoTexture_PS::g_PS,
			sizeof(StandardNoTexture_PS::g_PS),
			"StandardRenderer No Texture", decl, 3);

		shader->SetVertexConstantBufferSize(sizeof(Effekseer::Matrix44) * 2);
		((EffekseerRendererDX11::Shader*)shader)->SetVertexRegisterCount(8);
	}

	LineRendererDX11::~LineRendererDX11()
	{
		auto shader_ = (EffekseerRendererDX11::Shader*)shader;
		ES_SAFE_DELETE(shader_);
		shader = nullptr;
	}

	void LineRendererDX11::DrawLine(const Effekseer::Vector3D& p1, const Effekseer::Vector3D& p2, const Effekseer::Color& c)
	{
		EffekseerRendererDX11::Vertex v0;
		v0.Pos = p1;
		v0.SetColor(c);

		EffekseerRendererDX11::Vertex v1;
		v1.Pos = p2;
		v1.SetColor(c);

		vertexies.push_back(v0);
		vertexies.push_back(v1);
	}

	void LineRendererDX11::Render()
	{
		if (vertexies.size() == 0) return;

		renderer->GetVertexBuffer()->Lock();

		auto vs = (EffekseerRendererDX11::Vertex*)renderer->GetVertexBuffer()->GetBufferDirect(sizeof(EffekseerRendererDX11::Vertex) * vertexies.size());

		memcpy(vs, vertexies.data(), sizeof(EffekseerRendererDX11::Vertex) * vertexies.size());

		renderer->GetVertexBuffer()->Unlock();

		auto& state = renderer->GetRenderState()->Push();
		state.AlphaBlend = ::Effekseer::AlphaBlendType::Blend;
		state.DepthWrite = true;
		state.DepthTest = true;
		state.CullingType = Effekseer::CullingType::Double;

		renderer->SetRenderMode(Effekseer::RenderMode::Normal);
		renderer->BeginShader((EffekseerRendererDX11::Shader*)shader);

		((Effekseer::Matrix44*)(shader->GetVertexConstantBuffer()))[0] = renderer->GetCameraMatrix();
		((Effekseer::Matrix44*)(shader->GetVertexConstantBuffer()))[1] = renderer->GetProjectionMatrix();

		shader->SetConstantBuffer();

		renderer->GetRenderState()->Update(false);

		renderer->SetLayout((EffekseerRendererDX11::Shader*)shader);
		
		{
			ID3D11Buffer* vBuf = renderer->GetVertexBuffer()->GetInterface();
			uint32_t vertexSize = sizeof(EffekseerRendererDX11::Vertex);
			uint32_t offset = 0;
			renderer->GetContext()->IASetVertexBuffers(0, 1, &vBuf, &vertexSize, &offset);
		}

		renderer->GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R16_UINT, 0);

		renderer->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		renderer->GetContext()->Draw(
			vertexies.size(),
			0);


		renderer->EndShader((EffekseerRendererDX11::Shader*)shader);

		renderer->GetRenderState()->Pop();
	}


	void LineRendererDX11::ClearCache()
	{
		vertexies.clear();
	}

	void LineRendererDX11::OnLostDevice()
	{
		auto shader_ = (EffekseerRendererDX11::Shader*)shader;
		shader_->OnLostDevice();
	}

	void LineRendererDX11::OnResetDevice()
	{
		auto shader_ = (EffekseerRendererDX11::Shader*)shader;
		shader_->OnResetDevice();
	}
}
