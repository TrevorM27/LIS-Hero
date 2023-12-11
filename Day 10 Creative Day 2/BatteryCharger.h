// BatteryChargingUnit.h

#ifndef _BATTERYCHARGER_h
#define _BATTERYCHARGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Battery.h"
#include "SolarPanel.h"
#include "SimpleLed.h"
#include "TriColourLed.h"

class BatteryCharger
{
	public:

		static const byte MAX_BATTERIES		= 4;
		static const byte MAX_SOLAR_PANELS	= 2;
	
		BatteryCharger
			(	SimpleLed*		pLedChargingRate,
				TriColourLed*	pLedBatteryCharge);

		byte
		AddBattery
			(	Battery* pBattery);

		Battery*
		RemoveBattery
			(	byte batteryId);

		byte
		AddSolarPanel
			(	SolarPanel* pSolarPanel);

		SolarPanel*
		RemoveSolarPanel
			(	byte batteryId);

		void
		TimerTick
			(	unsigned int tickPeriodMillis);

#pragma region protected

	protected:

#pragma endregion

#pragma region private

	private:

		const unsigned int MONITOR_PERIOD = 1000U;	// One second.

		byte m_countBatteries;
		byte m_countSolarPanels;

		Battery*		m_batteries		[MAX_BATTERIES];
		SolarPanel*		m_solarPanels	[MAX_SOLAR_PANELS];
		SimpleLed*		m_pLedChargingRate;
		TriColourLed*	m_pLedBatteryCharge;

		unsigned int m_periodCharging;
		unsigned int m_periodChargingLedOn;

		byte
		BatteryPercentageCharge ();

		unsigned int
		TotalSolarCharge ();

		void
		SetBatteryLed
			(	unsigned int percentage);

#pragma endregion
};


#endif

