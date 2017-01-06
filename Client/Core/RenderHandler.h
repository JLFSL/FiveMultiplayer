#pragma once

class CWebApp : public CefApp, public CefSchemeHandlerFactory
{
public:
	virtual void OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) override;
	virtual void OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) override;

	// CefSchemeHandlerFactory methods
	virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) override;

	IMPLEMENT_REFCOUNTING(CWebApp);
};
