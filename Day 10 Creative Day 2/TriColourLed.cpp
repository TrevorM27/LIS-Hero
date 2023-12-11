// 
// 
// 

#include "TriColourLed.h"

TriColourLed::TriColourLed 
	(	const byte (&ledPins) [LED_COLOURS::TOTAL])
{
	for (byte colour = LED_COLOURS::FIRST; colour <= LED_COLOURS::LAST; colour++)
	{
		m_ledPins		[colour] = ledPins [colour];
		m_intensities	[colour] = 0;

		pinMode	(m_ledPins [colour], OUTPUT);

		analogWrite	(m_ledPins [colour], m_intensities [colour]);
	}
}

void
TriColourLed::SetOne
	(	LED_COLOURS	colour,
		byte		intensity)
{
	SetLed (colour, intensity);
}

void
TriColourLed::SetAll
	(	const byte (&intensities) [LED_COLOURS::TOTAL])
{
	for (byte colour = LED_COLOURS::FIRST; colour <= LED_COLOURS::LAST; colour++)
		SetLed (colour, intensities [colour]);
}

void
TriColourLed::GetOne
	(	LED_COLOURS	colour,
		byte&		intensity)
{
	intensity = m_intensities [colour];
}

void
TriColourLed::GetAll
	(	byte (&intensities) [LED_COLOURS::TOTAL])
{
	for (byte colour = LED_COLOURS::FIRST; colour <= LED_COLOURS::LAST; colour++)
		intensities [colour] = m_intensities [colour];
}

void
TriColourLed::SetLed
	(	byte colourIndex,
		byte intensity)
{
	if (m_intensities [colourIndex] != intensity)
	{
		m_intensities [colourIndex] = intensity;

		analogWrite	(m_ledPins [colourIndex], m_intensities [colourIndex]);
	}
}




