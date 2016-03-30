#include "Leaderboard.h"


Leaderboard::Leaderboard(sf::Vector2u l_windSize)
{
	if (m_font.loadFromFile("CubicCoreMono.ttf")){

	}
	m_textColor = sf::Color(23, 87, 100);
	m_title.setFont(m_font);
	m_title.setCharacterSize(100);
	m_title.setString("Leaderboards:");
	m_title.setColor(m_textColor);
	sf::FloatRect titleTextRect = m_title.getLocalBounds();
	m_title.setOrigin(sf::Vector2f(titleTextRect.width / 2, titleTextRect.height / 2));
	m_title.setPosition(sf::Vector2f(l_windSize.x / 2, 0));
	std::vector<std::string> scoresAsStrings;
	std::vector<int> scoresAsInts;

	std::ifstream leaderBoardsFileIn;
	leaderBoardsFileIn.open("leader_boards.txt");
	std::string lines;
	while (std::getline(leaderBoardsFileIn, lines)){
		scoresAsStrings.push_back(lines);
	}
	for (int i = 0; i < scoresAsStrings.size(); i++){
		scoresAsInts.push_back(std::stoi(scoresAsStrings[i]));
	}
	if (scoresAsInts.size() < 5){
		for (int i = scoresAsInts.size() - 1; i < 5; i++){
			scoresAsInts.push_back(0);
		}
	}
	leaderBoardsFileIn.close();
	std::sort(scoresAsInts.begin(), scoresAsInts.end()); 

	for (int i = 0; i < 5; i++){
		m_leaderBoards.push_back(sf::Text(std::to_string(i+1) + ": " + std::to_string(scoresAsInts[(scoresAsInts.size() - 1) - i]), m_font, 70));
		sf::FloatRect textRect = m_leaderBoards[i].getLocalBounds();
		m_leaderBoards[i].setOrigin(textRect.width / 2, textRect.height / 2);
		m_leaderBoards[i].setPosition(l_windSize.x / 2, (l_windSize.y / 3) + (m_leaderBoards[i].getCharacterSize() * i));
		m_leaderBoards[i].setColor(m_textColor);
	}
	for (int i = 0; i < 5; i++){
		std::cout << scoresAsInts[(scoresAsInts.size() - 1) - i] << "\n";
	}

}


Leaderboard::~Leaderboard()
{

}

void Leaderboard::Update(){
	std::vector<std::string> scoresAsStrings;
	std::vector<int> scoresAsInts;

	std::ifstream leaderBoardsFileIn;
	leaderBoardsFileIn.open("leader_boards.txt");
	std::string lines;
	while (std::getline(leaderBoardsFileIn, lines)){
		scoresAsStrings.push_back(lines);
	}
	for (int i = 0; i < scoresAsStrings.size(); i++){
		scoresAsInts.push_back(std::stoi(scoresAsStrings[i]));
	}
	if (scoresAsInts.size() < 5){
		for (int i = scoresAsInts.size() - 1; i < 5; i++){
			scoresAsInts.push_back(0);
		}
	}
	leaderBoardsFileIn.close();
	std::sort(scoresAsInts.begin(), scoresAsInts.end());

	for (int i = 0; i < 5; i++){
		m_leaderBoards[i].setString(std::to_string(i + 1) + ": " + std::to_string(scoresAsInts[(scoresAsInts.size() - 1) - i]));
	}
	for (int i = 0; i < 5; i++){
		std::cout << scoresAsInts[(scoresAsInts.size() -1 ) - i] << "\n";
	}
}

void Leaderboard::Render(sf::RenderWindow& l_window){
	l_window.draw(m_title);
	for (int i = 0; i < m_leaderBoards.size(); i++){
		l_window.draw(m_leaderBoards[i]);
	}
}