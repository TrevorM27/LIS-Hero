// Battery.h

#ifndef _Battery_h
#define _Battery_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class Battery
{
	public:

		static const unsigned long MAX_CHARGE = 50000UL;

		Battery
			(	unsigned long initialCharge = 0UL);

		unsigned long
		CurrentCharge ();

		void
		AddCharge
			(	unsigned long charge);

		void
		DrainCharge
			(	unsigned long charge);

#pragma region protected

	protected:

#pragma endregion

#pragma region private

	private:

		unsigned long m_currentCharge;

#pragma endregion
};

#endif

