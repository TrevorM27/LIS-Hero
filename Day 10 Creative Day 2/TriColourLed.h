// TriLED.h

#ifndef _TRILCOLOURED_h
#define _TRILCOLOURED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TriColourLed
{
	public:

		enum LED_COLOURS : byte
		{
			FIRST	= 0,

			RED		= FIRST,
			GREEN,
			BLUE,
			
			LAST	= BLUE,
			TOTAL	= LAST + 1
		};

		TriColourLed 
			(	const byte (&ledPins) [LED_COLOURS::TOTAL]);

		void
		SetOne
			(	LED_COLOURS	colour,
				byte		intensity);

		void
		SetAll
			(	const byte (&intensities) [LED_COLOURS::TOTAL]);

		void
		GetOne
			(	LED_COLOURS	colour,
				byte&		intensity);

		void
		GetAll
			(	byte (&intensities) [LED_COLOURS::TOTAL]);

#pragma region protected

	protected:

#pragma endregion

#pragma region private

	private:

		byte m_ledPins		[LED_COLOURS::TOTAL];
		byte m_intensities	[LED_COLOURS::TOTAL];

		void
		SetLed
			(	byte colourIndex,
				byte intensity);

#pragma endregion
};


#endif

