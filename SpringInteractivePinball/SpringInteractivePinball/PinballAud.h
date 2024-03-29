#pragma once

#include <SFML/Audio.hpp>

class PinballAud
{
public:

	// EFFECTS
	sf::SoundBuffer m_bufFlipperHit01;
	sf::SoundBuffer m_bufFlipperReset01;
	sf::Sound m_sndFlipperHit01;
	sf::Sound m_sndFlipperReset01;


	sf::SoundBuffer m_bufPlungerLaunch01;
	sf::Sound m_sndPlungerLaunch01;
	
	sf::SoundBuffer m_bufRattle01;
	sf::SoundBuffer m_bufRattle02;
	sf::Sound m_sndRattle;

	sf::SoundBuffer m_bufBallRoll01;
	sf::SoundBuffer m_bufBallRoll02;
	sf::Sound m_sndBallRoll;

	// Bells
	sf::SoundBuffer m_bufBell01;
	sf::SoundBuffer m_bufBell02;
	sf::SoundBuffer m_bufBell03;
	sf::SoundBuffer m_bufBell04;
	sf::SoundBuffer m_bufBell05;
	sf::SoundBuffer m_bufChain01;
	sf::SoundBuffer m_bufBellLong01;
	sf::Sound m_sndBellShort;
	sf::Sound m_sndBellLong;

	// Bumpers
	sf::SoundBuffer m_bufBumperHit01;
	sf::SoundBuffer m_bufBumperHit02;
	sf::SoundBuffer m_bufBumperHit03;
	sf::SoundBuffer m_bufBumperHit04;
	sf::SoundBuffer m_bufBumperHit05;
	sf::Sound m_sndBumper;

	// Lose
	sf::SoundBuffer m_bufSadTrombone01;
	sf::SoundBuffer m_bufTrenchBall01;
	sf::SoundBuffer m_bufTrenchBall02;
	sf::Sound m_sndLose;

	// LOOPS
	sf::Music m_musArcadeAmbience01;
	sf::Music m_musBackgroundHum01;
	sf::Music m_musBackgroundHum02;

	// MUSIC
	sf::Music m_musHardRock;
	sf::Music m_musDontStop;

	PinballAud();

	~PinballAud();

private:
};