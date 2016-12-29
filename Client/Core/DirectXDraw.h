#pragma once

class DirectXDraw
{
public:
	void Initialize();

	void BeginScene();
	void DrawScene();
	void EndScene();

	static DirectXDraw* GetInstance();

private:
	DirectXDraw();
	~DirectXDraw();

	float _DrawText(ImFont* pFont, const std::string& text, const ImVec2& position, float size, uint32_t color, bool center = false);
	void DrawLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness = 1.0f);
	void DrawCircle(const ImVec2& position, float radius, uint32_t color, float thickness = 1.0f);
	void DrawCircleFilled(const ImVec2& position, float radius, uint32_t color);

	ImFont* m_pFont;

	static DirectXDraw* m_pInstance;
};