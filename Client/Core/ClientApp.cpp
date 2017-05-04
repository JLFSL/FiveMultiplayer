#include "stdafx.h"

ClientApp::ClientApp()
{
}

void ClientApp::OnWebKitInitialized()
{
	std::string app_code =
		"var FiveMP;"
		"if (!FiveMP)"
		"    FiveMP = {};"
		"(function() {"
		"    FiveMP.PageLoaded = function() {"
		"        native function PageLoaded();"
		"        return PageLoaded();"
		"    };"
		""
		"	FiveMP.SendData = function(data) {"
		"        native function SendData(data);"
		"        return SendData(data);"
		"    };"
		"})();;";

	/*
	
	std::string app_code =
	"var app;"
	"if (!app)"
	"    app = {};"
	"(function() {"
	"    app.ChangeTextInJS = function(text) {"
	"        native function ChangeTextInJS();"
	"        return ChangeTextInJS(text);"
	"    };"
	"})();;";
	
	*/

	CefRegisterExtension("v8/app", app_code, new CefHandlerV8(this));
}