/*
    Name:       Day 10 Creative Day 2.ino
    Created:	10/12/2023 17:07:54
    Author:     DESKTOP-STUDY\trevo
*/

// Define User Types below here or use a .h file
//

#include "SimpleLed.h"
#include "TriColourLed.h"
#include "Battery.h"
#include "SolarPanel.h"
#include "BatteryCharger.h"

//	Battery Charge TriLED definitions.

const byte	BATTERY_CHARGE_LED_RED		= 9;
const byte	BATTERY_CHARGE_LED_GREEN	= 10;
const byte	BATTERY_CHARGE_LED_BLUE		= 11;

const byte batteryLedPins [TriColourLed::LED_COLOURS::TOTAL] = 
	{BATTERY_CHARGE_LED_RED, BATTERY_CHARGE_LED_GREEN, BATTERY_CHARGE_LED_BLUE};


//	Charging Rate LED definitions.

const byte	CHARGING_RATE_LED = 12;


//	Battery definitions.

byte batteryIds [BatteryCharger::MAX_BATTERIES];


//	Solar Panel definitions.

const byte SOLAR_POWER_MONITOR_0 = A0;
const byte SOLAR_POWER_MONITOR_1 = A1;

const byte solarPanelMonitorPins [BatteryCharger::MAX_SOLAR_PANELS] =
	{SOLAR_POWER_MONITOR_0, SOLAR_POWER_MONITOR_1};

byte solarPanelIds [BatteryCharger::MAX_SOLAR_PANELS];


//	Battery Charging Unit definitions.

BatteryCharger*	pBatteryCharger = NULL;


void setup ()
{
	Serial.begin (9600);

	//	Create the Charging Unit.

	pBatteryCharger = new BatteryCharger
		(new SimpleLed (CHARGING_RATE_LED), new TriColourLed (batteryLedPins));

	//	Create and add batteries to the Charging Unit.

	Battery* pBattery;
	
	for (byte batteryIndex = 0; batteryIndex < BatteryCharger::MAX_BATTERIES; batteryIndex++)
	{
		pBattery = new Battery (Battery::MAX_CHARGE / 20);	// 5% inital charge.

		batteryIds [batteryIndex] = pBatteryCharger->AddBattery (pBattery);
	}

	//	Create and add solar panels to the Charging Unit.

	SolarPanel*	pSolarPanel;
		
	for (byte solarPanelIndex = 0; solarPanelIndex < BatteryCharger::MAX_SOLAR_PANELS; solarPanelIndex++)
	{
		pSolarPanel = new SolarPanel (solarPanelMonitorPins [solarPanelIndex]);

		solarPanelIds [solarPanelIndex] = pBatteryCharger->AddSolarPanel (pSolarPanel);
	}
}

void loop ()
{
	const unsigned long PERIOD_TIMER_TICK = 20UL;

	delay (PERIOD_TIMER_TICK);

	pBatteryCharger->TimerTick (PERIOD_TIMER_TICK);
}
