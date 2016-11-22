#include "stdafx.h"

CServer::CServer()
{
	m_ulFrameCount = 0;
	m_ulFramesPerSecond = 0;
	m_ulLastFPSUpdateTime = 0;
	m_ShowFPS = true;
	m_Active = true;

	cout << endl << "CServer Constructed" << endl;
}


CServer::~CServer()
{

	cout << endl << "CServer Deconstructed" << endl;
}

bool CServer::OnLoad(int argc, char * argv[])
{
	return false;
}

void CServer::OnUnload()
{
}

void CServer::Process()
{
}
