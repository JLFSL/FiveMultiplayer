#include "stdafx.h"

OffscreenClient::OffscreenClient()
{
}

OffscreenClient::~OffscreenClient()
{
}

void OffscreenClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	//AutoLock lock_scope(this);
	// keep browser reference
	m_browser = browser;
}

bool doLoop = true;

void OffscreenClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	//AutoLock lock_scope(this);

	// quit message loop
	doLoop = false;

	m_browser = NULL;
}

void OffscreenClient::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height)
{
	std::cout << "hiya!" << std::endl;

	// We dont care about popup yet..
	if (type != PaintElementType::PET_VIEW) {
		return;
	}

	std::cout << "hiya2!" << std::endl;

	std::lock_guard<std::mutex> lock(DirectXRenderer::GetInstance()->paintMutex);
	DirectXRenderer::GetInstance()->drawData.push_back(std::make_unique<DrawData>(width, height, (const unsigned *)buffer, dirtyRects));
}
