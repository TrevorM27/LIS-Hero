// 
// 
// 

#include "BatteryCharger.h"


BatteryCharger::BatteryCharger
	(	SimpleLed*		pLedChargingRate,
		TriColourLed*	pLedBatteryCharge)
{
	m_countBatteries	= 0;
	m_countSolarPanels	= 0;
	m_periodCharging	= MONITOR_PERIOD;
	m_pLedChargingRate	= pLedChargingRate;
	m_pLedBatteryCharge	= pLedBatteryCharge;

	for (byte batteryIndex = 0; batteryIndex < MAX_BATTERIES; batteryIndex++)
		m_batteries [batteryIndex] = NULL;

	for (byte solarPanelIndex = 0; solarPanelIndex < MAX_SOLAR_PANELS; solarPanelIndex++)
		m_solarPanels [solarPanelIndex] = NULL;
}

byte
BatteryCharger::AddBattery
	(	Battery* pBattery)
{
	byte batteryId = MAX_BATTERIES;

	for (byte i = 0; i < MAX_BATTERIES; i++)
	{
		if (m_batteries [i] == NULL)
		{
			m_batteries [i] = pBattery;
			m_countBatteries++;
			batteryId = i;
			break;
		}
	}

	return (batteryId);
}

Battery*
BatteryCharger::RemoveBattery
	(	byte batteryId)
{
	Battery* pBattery = NULL;

	if (batteryId < MAX_BATTERIES)
	{
		pBattery = (Battery*) m_batteries [batteryId];
		m_batteries [batteryId] = NULL;
		m_countBatteries--;
	}

	return (pBattery);
}

byte
BatteryCharger::AddSolarPanel
	(	SolarPanel*	pSolarPanel)
{
	byte solarPanelId = MAX_SOLAR_PANELS;

	for (byte i = 0; i < MAX_SOLAR_PANELS; i++)
	{
		if (m_solarPanels [i] == NULL)
		{
			m_solarPanels [i] = pSolarPanel;
			m_countSolarPanels++;
			solarPanelId = i;
			break;
		}
	}

	return (solarPanelId);
}

SolarPanel*
BatteryCharger::RemoveSolarPanel
	(	byte solarPanelId)
{
	SolarPanel*	pSolarPanel = NULL;

	if (solarPanelId < MAX_SOLAR_PANELS)
	{
		pSolarPanel = (SolarPanel*) m_solarPanels [solarPanelId];
		m_solarPanels [solarPanelId] = NULL;
		m_countSolarPanels--;
	}

	return (pSolarPanel);
}

void
BatteryCharger::TimerTick
	(	unsigned int tickPeriodMillis)
{
	const unsigned int BATTERY_DRAIN = 280U;

	if (m_periodCharging > tickPeriodMillis)
	{
		m_periodCharging -= tickPeriodMillis;

		if (m_periodChargingLedOn > tickPeriodMillis)
		{
			m_periodChargingLedOn -= tickPeriodMillis;
		}
		else
		if (m_periodChargingLedOn > 0)
		{
			m_periodChargingLedOn = 0;

			m_pLedChargingRate->Set (SimpleLed::LED_STATES::OFF);
		}
	}
	else
	{
		unsigned int totalSolarCharge	= TotalSolarCharge ();
		unsigned int perBatteryDrain	= BATTERY_DRAIN / m_countBatteries;
		unsigned int perBatteryCharge	= totalSolarCharge / m_countBatteries;

		for (byte i = 0; i < MAX_BATTERIES; i++)
		{
			if (m_batteries [i] != NULL)
			{
				m_batteries [i]->DrainCharge (perBatteryDrain);
				m_batteries [i]->AddCharge (perBatteryCharge);
			}
		}

		byte batteryPercentageCharge = BatteryPercentageCharge ();

		SetBatteryLed (batteryPercentageCharge);

		m_periodCharging = MONITOR_PERIOD;

		m_periodChargingLedOn = map (totalSolarCharge, 0L, 1023L * MAX_SOLAR_PANELS, 0L, MONITOR_PERIOD);

		m_pLedChargingRate->Set (SimpleLed::LED_STATES::ON);
	}
}

byte
BatteryCharger::BatteryPercentageCharge ()
{
	unsigned long currentCharge = 0;

	for (byte i = 0; i < MAX_BATTERIES; i++)
		if (m_batteries [i] != NULL)
			currentCharge += m_batteries [i]->CurrentCharge ();

	byte percentageCharge = (currentCharge * 100) / (Battery::MAX_CHARGE * m_countBatteries);

	return (percentageCharge);
}

unsigned int
BatteryCharger::TotalSolarCharge ()
{
	unsigned int solarCharge = 0;

	for (byte i = 0; i < MAX_SOLAR_PANELS; i++)
		if (m_solarPanels [i] != NULL)
			solarCharge += m_solarPanels [i]->Charge ();

	return (solarCharge);
}

void
BatteryCharger::SetBatteryLed
	(	unsigned int percentage)
{
	const unsigned int	THRESHOLD_RED		= 5;
	const unsigned int	THRESHOLD_YELLOW	= 50;
	const unsigned int	THRESHOLD_GREEN		= 95;

	byte ledIntensities [TriColourLed::LED_COLOURS::TOTAL];

	if (percentage < THRESHOLD_RED)
	{
		//	All off.
		ledIntensities [TriColourLed::LED_COLOURS::RED]		= 0;
		ledIntensities [TriColourLed::LED_COLOURS::GREEN]	= 0;
		ledIntensities [TriColourLed::LED_COLOURS::BLUE]	= 0;
	}
	else
	if (percentage < THRESHOLD_YELLOW)
	{
		//	Red LED on.
		ledIntensities [TriColourLed::LED_COLOURS::RED]		= 64;
		ledIntensities [TriColourLed::LED_COLOURS::GREEN]	= 0;
		ledIntensities [TriColourLed::LED_COLOURS::BLUE]	= 0;
	}
	else
	if (percentage < THRESHOLD_GREEN)
	{
		//	Yellow LED on.
		ledIntensities [TriColourLed::LED_COLOURS::RED]		= 255;
		ledIntensities [TriColourLed::LED_COLOURS::GREEN]	= 16;
		ledIntensities [TriColourLed::LED_COLOURS::BLUE]	= 0;
	}
	else
	{
		//	Green LED on.
		ledIntensities [TriColourLed::LED_COLOURS::RED]		= 0;
		ledIntensities [TriColourLed::LED_COLOURS::GREEN]	= 64;
		ledIntensities [TriColourLed::LED_COLOURS::BLUE]	= 0;
	}

	m_pLedBatteryCharge->SetAll (ledIntensities);
}
