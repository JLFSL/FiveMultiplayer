#include "stdafx.h"

RenderHandler::RenderHandler()
{
}

RenderHandler::~RenderHandler()
{
}

void RenderHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	//AutoLock lock_scope(this);
	// keep browser reference
	m_browser = browser;
}

bool doLoop = true;

void RenderHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	//AutoLock lock_scope(this);

	// quit message loop
	doLoop = false;

	m_browser = NULL;
}

void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height)
{
	
}