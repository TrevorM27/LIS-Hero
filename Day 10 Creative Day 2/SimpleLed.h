// LedControl.h

#ifndef _SimpleLed_h
#define _SimpleLed_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SimpleLed
{
	public:

		enum LED_STATES : byte
		{
			OFF, ON
		};

		SimpleLed 
			(	byte	ledPin);

		void
		Set	(	LED_STATES	ledState);

		LED_STATES
		Get ();


#pragma region protected

	protected:

#pragma endregion

#pragma region private

	private:

		LED_STATES	m_ledState;
		byte		m_ledPin;

#pragma endregion
};

#endif
