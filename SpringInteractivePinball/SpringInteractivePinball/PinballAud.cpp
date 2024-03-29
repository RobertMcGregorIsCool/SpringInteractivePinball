/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>
#include "PinballAud.h"
#include <iostream>

/// <summary>
/// Loads content and preps for play
/// </summary>
PinballAud::PinballAud()
{
	if (!m_bufFlipperHit01.loadFromFile("ASSETS\\AUDIO\\EFFECTS\\FlipperHit01.wav")) std::cout << "Load fail FlipperHit01.wav\n";
	if (!m_bufFlipperReset01.loadFromFile("ASSETS\\AUDIO\\EFFECTS\\FlipperReset01.wav")) std::cout << "Load fail FlipperReset01.wav\n";
	m_sndFlipperHit01.setBuffer(m_bufFlipperHit01);
	m_sndFlipperReset01.setBuffer(m_bufFlipperReset01);

	if (!m_bufPlungerLaunch01.loadFromFile("ASSETS\\AUDIO\\EFFECTS\\PlungerLaunch01.wav")) std::cout << "Load fail PlungerLaunch01.wav\n";
	m_sndPlungerLaunch01.setBuffer(m_bufPlungerLaunch01);

	if (!m_bufRattle01.loadFromFile("ASSETS\\AUDIO\\EFFECTS\\Rattle01.wav")) std::cout << "Load fail Rattle01.wav\n";
	m_sndRattle.setBuffer(m_bufRattle01);

	if (!m_bufBallRoll01.loadFromFile("ASSETS\\AUDIO\\EFFECTS\\BallRoll01.wav")) std::cout << "Load fail BallRoll01.wav\n";
	m_sndBallRoll.setBuffer(m_bufBallRoll01);

	if (!m_bufBell01.loadFromFile("ASSETS\\AUDIO\\EFFECTS\\BELLS\\Bell01.wav")) std::cout << "Load fail Bell01.wav\n";
	m_sndBellShort.setBuffer(m_bufBell01);

	if (!m_bufBumperHit01.loadFromFile("ASSETS\\AUDIO\\EFFECTS\\BUMPERS\\BumperHit01.wav")) std::cout << "Load fail BumperHit01.wav\n";
	m_sndBumper.setBuffer(m_bufBumperHit01);

	if (!m_bufTrenchBall01.loadFromFile("ASSETS\\AUDIO\\EFFECTS\\LOSE\\TrenchBall01.wav")) std::cout << "Load fail TrenchBall01.wav\n";
	m_sndLose.setBuffer(m_bufTrenchBall01);

	if (!m_musArcadeAmbience01.openFromFile("ASSETS\\AUDIO\\EFFECTS\\LOOPS\\ArcadeAmbience01.wav")) std::cout << "Load fail ArcadeAmbience01.wav\n";
	if (!m_musBackgroundHum01.openFromFile("ASSETS\\AUDIO\\EFFECTS\\LOOPS\\BackgroundHum01.wav")) std::cout << "Load fail BackgroundHum01.wav\n";

	if (!m_musHardRock.openFromFile("ASSETS\\AUDIO\\MUSIC\\2.Hard Rock_loop.wav")) std::cout << "Fail load 2.Hard Rock_loop.wav\n";
	if (!m_musDontStop.openFromFile("ASSETS\\AUDIO\\MUSIC\\Don't stop_looped.wav")) std::cout << "Fail load Don't stop_looped.wav\n";

	m_musArcadeAmbience01.setLoop(true);
	m_musArcadeAmbience01.setVolume(60);
	m_musArcadeAmbience01.play();
	m_musHardRock.setLoop(true);
	m_musHardRock.setVolume(20);
	m_musHardRock.play();
}

PinballAud::~PinballAud()
{
}
