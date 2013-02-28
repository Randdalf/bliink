#ifndef BLIINK_ITEM_SPAWNER_H
#define BLIINK_ITEM_SPAWNER_H

#include "cbase.h"

#define MAX_ITEM

class CBliinkItemSpawner : public CLogicalEntity
{
public:
	DECLARE_CLASS( CBliinkItemSpawner , CLogicalEntity );
	DECLARE_DATADESC();

	// Constructor
	CBliinkItemSpawner( void );

	virtual void Think( void );

private:


};

LINK_ENTITY_TO_CLASS( my_logical_entity, CMyLogicalEntity  );

// Start of our data description for the class
BEGIN_DATADESC( CMyLogicalEntity  )
	
	// For save/load
	DEFINE_FIELD( m_nCounter, FIELD_INTEGER ),

	// Links our member variable to our keyvalue from Hammer
	DEFINE_KEYFIELD( m_nThreshold, FIELD_INTEGER, "threshold" ),

	// Links our input name from Hammer to our input member function
	DEFINE_INPUTFUNC( FIELD_VOID, "Tick", InputTick ),

	// Links our output member to the output name used by Hammer
	DEFINE_OUTPUT( m_OnThreshold, "OnThreshold" ),

END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: Handle a tick input from another entity
//-----------------------------------------------------------------------------
void CMyLogicalEntity ::InputTick( inputdata_t &inputData )
{
	// Increment our counter
	m_nCounter++;

	// See if we've met or crossed our threshold value
	if ( m_nCounter >= m_nThreshold )
	{
		// Fire an output event
		m_OnThreshold.FireOutput( inputData.pActivator, this );
		
		// Reset our counter
		m_nCounter = 0;
	}
}

#endif // BLIINK_ITEM_SPAWNER_H