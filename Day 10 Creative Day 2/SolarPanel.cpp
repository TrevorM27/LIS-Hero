// 
// 
// 

#include "SolarPanel.h"


SolarPanel::SolarPanel
	(	byte	monitorPin)
{
	m_monitorPin = monitorPin;

	pinMode (m_monitorPin, INPUT);
}

unsigned int
SolarPanel::Charge ()
{
	unsigned int charge = analogRead (m_monitorPin);

	return (charge);
}



