#pragma once
#include <string>
#include <stdarg.h>
#include <orbis/libkernel.h>

inline static void notification(const char* iconURI, const char* format, ...)
{
	OrbisNotificationRequest Buffer;

	va_list args;
	va_start(args, format);
	vsprintf(Buffer.message, format, args);
	va_end(args);

	Buffer.type = OrbisNotificationRequestType::NotificationRequest;
	Buffer.unk3 = 0;
	Buffer.useIconImageUri = 1;
	Buffer.targetId = -1;

	// Maximum size to move is destination size - 1 to allow for null terminator
	if (iconURI != NULL && strnlen(iconURI, sizeof(Buffer.iconUri)) + 1 < sizeof(Buffer.iconUri))
		strncpy(Buffer.iconUri, iconURI, strnlen(iconURI, sizeof(Buffer.iconUri) - 1));
	else
		Buffer.useIconImageUri = 0;

	sceKernelSendNotificationRequest(0, &Buffer, 3120, 0);
}