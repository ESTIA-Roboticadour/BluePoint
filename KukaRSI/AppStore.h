#pragma once
class AppStore
{
public:
	static void setIsInEdition(bool isInEdition);
	static bool isInEdition();

private:
	static bool s_isInEdition;
};
