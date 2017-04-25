#include "stdafx.h"

ClientApp::ClientApp()
{
}

void ClientApp::OnWebKitInitialized()
{
	std::string app_code =
		"var app;"
		"if (!app)"
		"    app = {};"
		"(function() {"
		"    app.ExitGame = function() {"
		"        native function ExitGame();"
		"        return ExitGame();"
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