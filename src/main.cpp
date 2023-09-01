#include <sstream>
#include <iostream>

#include "graphics.h"
#include "log.h"
#include "user.h"
#include "network.h"
#include "notification.h"

// Dimensions
#define FRAME_WIDTH     1920
#define FRAME_HEIGHT    1080
#define FRAME_DEPTH        4

// Font information
#define FONT_SIZE   	   42

// Font faces
FT_Face fontTxt;

// Background and foreground colors
Color bgColor;
Color fgColor;

// Logging
std::stringstream debugLogStream;

int frameID = 0;

int main()
{
	// No buffering
	setvbuf(stdout, NULL, _IONBF, 0);

	DEBUGLOG << "Creating a scene";

	auto scene = new Scene2D(FRAME_WIDTH, FRAME_HEIGHT, FRAME_DEPTH);

	if (!scene->Init(0xC000000, 2))
	{
		DEBUGLOG << "Failed to initialize 2D scene";
		while (1);
	}

	// Set colors
	bgColor = { 0, 0, 0 };
	fgColor = { 255, 255, 255 };

	const char* font = "/app0/assets/fonts/Gontserrat-Regular.ttf";

	DEBUGLOG << "Initializing font (" << font << ")";

	if (!scene->InitFont(&fontTxt, font, FONT_SIZE))
	{
		DEBUGLOG << "Failed to initialize font '" << font << "'";
		while (1);
	}

	User loggedInUser;

	if (getLoggedInUser(&loggedInUser) != 0)
	{
		DEBUGLOG << "Failed to get logged user!";
		return -1;
	}

	std::stringstream loggedUserTextStream;
	loggedUserTextStream << "Logged into: " << loggedInUser.username << " (ID: 0x" << std::hex << loggedInUser.userID << ")";

	std::stringstream networkInfoTextStream;
	char networkSSID[64];

	if (getNetworkSSID(networkSSID) == 0)
		networkInfoTextStream << "Network: " << networkSSID;
	else
		networkInfoTextStream << "Network: Unknown";

	notification("cxml://psnotification/tex_default_icon_notification", "Welcome %s", loggedInUser.username);

	DEBUGLOG << "Entering draw loop...";

	// Draw loop
	while (1)
	{
		scene->DrawText((char*)loggedUserTextStream.str().c_str(), fontTxt, 26, 42, bgColor, fgColor);

		scene->DrawText((char*)networkInfoTextStream.str().c_str(), fontTxt, 26, 84, bgColor, fgColor);

		// Submit the frame buffer
		scene->SubmitFlip(frameID);
		scene->FrameWait(frameID);

		// Swap to the next buffer
		scene->FrameBufferSwap();
		frameID++;
	}

	return 0;
}