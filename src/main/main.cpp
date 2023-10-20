#include <iostream>
#include <App.h>

int main(int argc, char* argv[])
{
	App	app;

	if (app.InitApp() == false)
		return (-1);
	app.Run();
	return (0);
}