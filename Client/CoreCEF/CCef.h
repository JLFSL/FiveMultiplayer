#pragma once

class CCef
{
private:
	void *SandboxInfo;

public:
	CCef();
	~CCef();

	bool Initialize(HINSTANCE hInstance);
	bool Close();
	void Pulse();

	bool CreateNewWindow();
	
};

class CCefApp : public CefApp, public CefRenderProcessHandler
{
public:
	CCefApp() {}
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; };

	virtual void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node) override
	{
		
	}

	virtual void OnRegisterCustomSchemes(CefRefPtr < CefSchemeRegistrar > registrar) override
	{
		
	}


	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) override
	{
		
	}

	static void Javascript_triggerEvent(CefRefPtr<CefFrame> frame, const CefV8ValueList& arguments)
	{
		
	}

public:
	IMPLEMENT_REFCOUNTING(CCefApp);

private:
	bool m_bHasInputFocus = false;
};

