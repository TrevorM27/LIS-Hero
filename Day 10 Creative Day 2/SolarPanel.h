// Solar.h

#ifndef _SOLARPANEL_h
#define _SOLARPANEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SolarPanel
{
	public:

		SolarPanel
			(	byte	monitorPin);

		unsigned int
		Charge ();

#pragma region protected

	protected:

#pragma endregion

#pragma region private

	private:

		byte m_monitorPin;

#pragma endregion
};



#endif

