#include "TestGame.h"

TestGame::TestGame(std::string title, sf::Vector2u windowSize) : m_window(title, windowSize,"keys.cfg"){
	rightPaddle.setSize(sf::Vector2f(15, 100));
	rightPaddle.setPosition(sf::Vector2f(800 - 15, 0));
	rightPaddle.setFillColor(sf::Color::Red);
	rightPaddle.setOutlineColor(sf::Color::Black);
	rightPaddle.setOutlineThickness(1.f);

	leftPaddle.setSize(sf::Vector2f(15, 100));
	leftPaddle.setPosition(sf::Vector2f(0, 0));
	leftPaddle.setFillColor(sf::Color::Red);
	leftPaddle.setOutlineColor(sf::Color::Black);
	leftPaddle.setOutlineThickness(1.f);

	ball.setRadius(10.f);
	ball.setOrigin(sf::Vector2f(10 / 2, 10 / 2));
	ball.setPosition(sf::Vector2f(800 / 2, 600 / 2));
	ball.setFillColor(sf::Color::Blue);
	ball.setOutlineThickness(1.f);
	ball.setOutlineColor(sf::Color::Black);

	m_window.GetEventManager()->AddCallback("LeftPaddle_move_up", &TestGame::LeftPaddleMove, this);
	m_window.GetEventManager()->AddCallback("LeftPaddle_move_down", &TestGame::LeftPaddleMove, this);
	m_window.GetEventManager()->AddCallback("RightPaddle_move_up", &TestGame::RightPaddleMove, this);
	m_window.GetEventManager()->AddCallback("RightPaddle_move_down", &TestGame::RightPaddleMove, this);
	//m_window.GetEventManager()->AddCallback("Debug", &TestGame::Debug, this);
	vel = sf::Vector2f(130, 130);
	c = 0;
	r = 1;
	g = 254;
	b = 254;
	redUp = 1;
	blueUp = 1;
	greenUp = 1;
}

TestGame::~TestGame(){

}


void TestGame::Update(){
	this->m_window.Update();
	ballUpdate();
	rightPaddleUpdate();
	leftPaddleUpdate();
	c++;
	if (c == 5){
		sf::CircleShape s(10);
		s.setOrigin(sf::Vector2f(5, 5));
		s.setFillColor(sf::Color(0, 0, 0, 0));
		s.setOutlineThickness(1.f);
		s.setOutlineColor(sf::Color(r, g, b));
		s.setPosition(ball.getPosition());
		trail.push_back(s);
		c = 0;

		/*if (r == 255 || r == 0){
			redUp *= -1;
		}

		if (g == 255 || g == 0){
			blueUp *= -1;
		}
		 
		if (g == 255 || g == 0){
			greenUp *= -1;
		}
		
		r += redUp;
		b += blueUp;
		g += greenUp;*/
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
		
	}
}

void TestGame::Render(){
	m_window.BeginDraw();
	for (int i = 0; i < trail.size(); i++){
		m_window.Draw(trail[i]);
	}
	m_window.Draw(rightPaddle);
	m_window.Draw(leftPaddle);
	m_window.Draw(ball);
	m_window.EndDraw();
}



void TestGame::RightPaddleMove(SFGE::EventDetails* l_details){
	float dt = GetElapsed();
	if (l_details->m_name == "RightPaddle_move_up" && rightPaddle.getPosition().y > 0){
		//std::cout << "right paddle up\n";
		rightPaddle.move(sf::Vector2f(0, -150 * dt));
	}
	else if (l_details->m_name == "RightPaddle_move_down" && rightPaddle.getPosition().y < 600 - 100){
		//std::cout << "right paddle down\n";
		rightPaddle.move(sf::Vector2f(0, 150 * dt));
	}
}

void TestGame::LeftPaddleMove(SFGE::EventDetails* l_details){
	float dt = GetElapsed();
	if (l_details->m_name == "LeftPaddle_move_up" && leftPaddle.getPosition().y >0){
		//std::cout << "left paddle up\n";
		leftPaddle.move(sf::Vector2f(0, -150 * dt));
	}
	else if (l_details->m_name == "LeftPaddle_move_down" && leftPaddle.getPosition().y < 600 - 100){
		//std::cout << "left paddle down\n";
		leftPaddle.move(sf::Vector2f(0, 150 * dt));
	}
}

void TestGame::Debug(SFGE::EventDetails* l_details){

}

void TestGame::ballUpdate(){
	float x = ball.getPosition().x;
	float y = ball.getPosition().y;
	if (x < 784 && x > 16){
		if (y < 5){
			vel.y *= -1;
		}
		else if (y > 595){
			vel.y *= -1;
		}
	}
	else{
		ball.setPosition(800 / 2, 600 / 2);
	}

	if (ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds())){
		vel.x *= -1;
	}

	ball.move(vel * GetElapsed());
}

void TestGame::rightPaddleUpdate(){
	if (ball.getPosition().y < rightPaddle.getPosition().y + 50){
		SFGE::EventDetails details("RightPaddle_move_up");
		RightPaddleMove(&details);
	}
	else if (ball.getPosition().y > rightPaddle.getPosition().y+ 50){
		SFGE::EventDetails details("RightPaddle_move_down");
		RightPaddleMove(&details);
	}
}

void TestGame::leftPaddleUpdate(){
	if (ball.getPosition().y < leftPaddle.getPosition().y + 50){
		SFGE::EventDetails details("LeftPaddle_move_up");
		LeftPaddleMove(&details);
	}
	else if (ball.getPosition().y > leftPaddle.getPosition().y + 50){
		SFGE::EventDetails details("LeftPaddle_move_down");
		LeftPaddleMove(&details);
	}
}

void TestGame::Run(){
	this->RestartClock();
	while (!this->GetWindow()->IsDone()){
		this->Update();
		this->Render();
		this->RestartClock();
	}
}