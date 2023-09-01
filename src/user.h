#pragma once
struct User
{
	int userID;
	char* username;
};

int getLoggedInUser(User* user);