#pragma once
#include <orbis/NetCtl.h>
#include <string.h>

int getNetworkSSID(char* ssid)
{
	OrbisNetCtlInfo networkInfo;

	int retValue = sceNetCtlInit();

	if (retValue != 0)
		return retValue;

	retValue = sceNetCtlGetInfo(ORBIS_NET_CTL_INFO_SSID, &networkInfo);

	if (retValue == 0)
		strcpy(ssid, networkInfo.ssid);

	sceNetCtlTerm();

	return retValue;
}