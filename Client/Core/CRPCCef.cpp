#include "stdafx.h"

void CRPCCef::LoadURL(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	std::cout << "CRPCCef::LoadURL" << std::endl;
	RakString url, appcode;
	bool remote;

	bitStream->Read(url);
	bitStream->Read(appcode);
	bitStream->Read(remote);

	/*if (!remote)
	{
		char buffer[MAX_PATH];
		GetCurrentDirectoryA(sizeof(buffer), buffer);

		char urlbuffer[MAX_PATH];
		sprintf(urlbuffer, "%s%s", buffer, url);

		std::cout << urlbuffer << std::endl;
		CefRenderer::getBrowser()->GetMainFrame()->LoadURL(CefString(urlbuffer));
	}
	else
	{
		std::cout << url << std::endl;
		CefRenderer::getBrowser()->GetMainFrame()->LoadURL(CefString(url));
	}*/
}

void CRPCCef::JavaScriptCall(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	std::cout << "CRPCCef::JavaScriptCall" << std::endl;
	RakString call;

	bitStream->Read(call);

	/*CefRefPtr<CefFrame> frame = CefRenderer::getBrowser()->GetMainFrame();
	frame->ExecuteJavaScript(CefString(call), frame->GetURL(), 0);*/
}
