// 
// 
// 

#include "Battery.h"

Battery::Battery
	(	unsigned long	initialCharge)
{
	m_currentCharge	= initialCharge;
}

unsigned long
Battery::CurrentCharge ()
{
	return (m_currentCharge);
}

void
Battery::AddCharge
	(	unsigned long	charge)
{
	if ((MAX_CHARGE - charge) > m_currentCharge)
		m_currentCharge += charge;
	else
		m_currentCharge = MAX_CHARGE;
}

void
Battery::DrainCharge
	(	unsigned long	charge)
{
	if (m_currentCharge > charge)
		m_currentCharge -= charge;
	else
		m_currentCharge = 0;
}


