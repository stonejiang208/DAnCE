/* -*- C++ -*- */

// ============================================================================
//
// = LIBRARY
//    ace
// 
// = FILENAME
//    Timer_Wheel.h
//
// = AUTHOR
//    Darrell Brunsch (brunsch@cs.wustl.edu)
// 
// ============================================================================

#if !defined (ACE_TIMER_WHEEL_H)
#define ACE_TIMER_WHEEL_H

#include "ace/Timer_Wheel_T.h"

// The following typedef are here for ease of use and backward
// compatibility.

typedef ACE_Timer_Wheel_T<ACE_Event_Handler *, 
                         ACE_Event_Handler_Handle_Timeout_Upcall<ACE_SYNCH_RECURSIVE_MUTEX>, 
                         ACE_SYNCH_RECURSIVE_MUTEX> 
	ACE_Timer_Wheel;

typedef ACE_Timer_Wheel_Iterator_T<ACE_Event_Handler *, 
                                   ACE_Event_Handler_Handle_Timeout_Upcall<ACE_SYNCH_RECURSIVE_MUTEX>, 
                                   ACE_SYNCH_RECURSIVE_MUTEX>  
	ACE_Timer_Wheel_Iterator;

#endif /* ACE_TIMER_WHEEL_H */
