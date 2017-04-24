#pragma once

struct CefHandlerV8 : public CefV8Handler {
	CefHandlerV8(CefRefPtr<CefApp> app);

	bool Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments, CefRefPtr<CefV8Value> &retval, CefString &exception) OVERRIDE;

private:
	CefRefPtr<CefApp> app;

	IMPLEMENT_REFCOUNTING(CefHandlerV8);
};
