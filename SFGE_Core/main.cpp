
#include <iostream> 
#include "TestGame.h"
int main()
{
	TestGame game("Test",sf::Vector2u(800,600));
	while (!game.GetWindow()->IsDone()){
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}
	return 0;
}

