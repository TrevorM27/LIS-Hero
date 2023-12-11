//
//

#include "SimpleLed.h"

SimpleLed::SimpleLed 
	(	byte	ledPin)
{
	m_ledPin	= ledPin;
	m_ledState	= LED_STATES::OFF;

	pinMode (m_ledPin, OUTPUT);

	digitalWrite (m_ledPin, LOW);
}

void
SimpleLed::Set
	(	LED_STATES	ledState)
{
	switch (ledState)
	{
		case LED_STATES::OFF :
			if (m_ledState != LED_STATES::OFF)
			{
				digitalWrite (m_ledPin, LOW);
				m_ledState = ledState;
			} break;

		case LED_STATES::ON :
			if (m_ledState != LED_STATES::ON)
			{
				digitalWrite (m_ledPin, HIGH);
				m_ledState = ledState;
			} break;
	}
}

SimpleLed::LED_STATES
SimpleLed::Get ()
{
	return (m_ledState);
}


