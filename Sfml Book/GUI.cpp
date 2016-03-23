#include "GUI.h"


GUI::GUI(Snake& l_player, sf::Vector2u l_windSize) : m_player(l_player)
{
	if (!m_font.loadFromFile("CubicCoreMono.ttf")){

	}

	m_textColor = sf::Color(23, 87, 100);

	m_playerLives = m_player.GetLives();
	m_playerScore = m_player.GetScore();
	m_playerInfo.push_back(sf::Text("Player Score: " + (std::to_string(m_playerScore)), m_font, 30));
	m_playerInfo.push_back(sf::Text("Player Lives: " + (std::to_string(m_playerLives)), m_font, 30));

	for (int i = 0; i < m_playerInfo.size(); i++){
		m_playerInfo[i].setPosition(16,16+(m_playerInfo[i].getCharacterSize()) * i);
		m_playerInfo[i].setColor(m_textColor);
	}


}

void GUI::Update(Snake& l_player){
	m_playerInfo[0].setString("Player Score: " + (std::to_string(l_player.GetScore())));
	m_playerInfo[1].setString("Player Lives: " + (std::to_string(l_player.GetLives())));
}

void GUI::Render(sf::RenderWindow& l_window){
	for (int i = 0; i < m_playerInfo.size(); i++){
		l_window.draw(m_playerInfo[i]);
	}
}


GUI::~GUI()
{
}
