#ifndef __APICALLCEF_H__
#define __APICALLCEF_H__
namespace API
{
	namespace Cef
	{
		void OnCefFinishLoad(void *Instance, const int entity);
		void OnCefSendData(void *Instance, const int entity, const std::string data);
	}
}
#endif