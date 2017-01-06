#include "stdafx.h"

void CWebApp::OnRegisterCustomSchemes(CefRefPtr < CefSchemeRegistrar > registrar)
{
	
}

void CWebApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{
	command_line->AppendSwitch("disable-gpu-compositing");
	command_line->AppendSwitch("disable-gpu");
	//command_line->AppendSwitch("disable-d3d11");
	command_line->AppendSwitch("enable-begin-frame-scheduling");
}

CefRefPtr<CefResourceHandler> CWebApp::Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request)
{
	
	return nullptr;
}
