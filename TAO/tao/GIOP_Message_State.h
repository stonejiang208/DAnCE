// -*- C++ -*-

//=============================================================================
/**
 *  @file     GIOP_Message_State.h
 *
 *  $Id$
 *
 *   GIOP utility definitions
 *
 *
 *  @author  Chris Cleeland <cleeland@cs.wustl.edu>
 *  @author  Carlos O' Ryan <coryan@uci.edu>
 */
//=============================================================================


#ifndef TAO_GIOP_MESSAGE_STATE_H
#define TAO_GIOP_MESSAGE_STATE_H
#include "ace/pre.h"
#include "tao/TAO_Export.h"


#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/corbafwd.h"
#include "tao/CDR.h"

class TAO_ORB_Core;

/**
 * @class TAO_GIOP_Version
 *
 * @brief Major and Minor version number of the Inter-ORB Protocol.
 */
class TAO_Export TAO_GIOP_Version
{
public:
  /// Major version number
  CORBA::Octet major;

  /// Minor version number
  CORBA::Octet minor;

  /// Copy constructor
  TAO_GIOP_Version (const TAO_GIOP_Version &src);

  /// Default constructor.
  TAO_GIOP_Version (CORBA::Octet maj = TAO_DEF_GIOP_MAJOR,
                    CORBA::Octet min = TAO_DEF_GIOP_MINOR);

  /// Destructor.
  ~TAO_GIOP_Version (void);

  /// Explicitly set the major and minor version.
  void set_version (CORBA::Octet maj, CORBA::Octet min);

  /// Copy operator.
  TAO_GIOP_Version &operator= (const TAO_GIOP_Version &src);

  /// Equality operator
  int operator== (const TAO_GIOP_Version &src);
  int operator!= (const TAO_GIOP_Version &src);
};


/**
 * @class TAO_GIOP_Message_State
 *
 * @brief Generic definitions for Message States.
 *
 * This  represents the state of the incoming GIOP message
 * As the ORB processes incoming messages it needs to keep track of
 * how much of the message has been read, if there are any
 * fragments following this message etc.
 */
class TAO_Export TAO_GIOP_Message_State
{

public:
  /// Ctor
  TAO_GIOP_Message_State (TAO_ORB_Core *orb_core);

  /// Dtor
  ~TAO_GIOP_Message_State (void);

  ///Reset the message header state and prepare it to receive the next
  /// event.
  void reset (int reset_contents = 1);

  /// Has the header been received?
  CORBA::Boolean  header_received (void) const;

  /// Check if the current message is complete, adjusting the fragments
  /// if required...
  int is_complete (void);

  /// Version info
  TAO_GIOP_Version giop_version;

  /// 0 = big, 1 = little
  CORBA::Octet byte_order;

  /// (Requests and Replys)
  CORBA::Octet more_fragments;

  /// MsgType above
  CORBA::Octet message_type;

  /// in byte_order!
  CORBA::ULong message_size;

  /// How much of the payload has been received
  CORBA::ULong current_offset;

  /// This is the InputCDR that will be used to decode the message.
  TAO_InputCDR cdr;

  /**
   * The fragments are collected in a chain of message blocks (using
   * the cont() field).  When the complete message is received the
   * chain is reassembled into <cdr>
   */
  ACE_Message_Block* fragments_begin;
  ACE_Message_Block* fragments_end;

  /**
   * The byte order for the the first fragment
   * @@ The current implementation cannot handle fragments with
   *    different byte orders, this should not be a major problem
   *    because:
   *    1) It is unlikely that we are going to receive fragments.
   *    2) The spec *seems* to allow different byte_orders, but it is
   *       unlikely that any ORB will do that.
   *    3) Even if we allowed that at this layer the CDR classes are
   *       not prepared to handle that.
   */
  CORBA::Octet first_fragment_byte_order;

  /// The GIOP version for the first fragment
  /// @@ Same as above, all GIOP versions must match.
  TAO_GIOP_Version first_fragment_giop_version;

  /**
   * If the messages are chained this represents the message type for
   * the *complete* message (remember that the last message will be
   * fragment and the upper level needs to know if it is a request,
   * locate request or what).
   */
  CORBA::Octet first_fragment_message_type;


private:
  /// Append <current> to the list of fragments
  /// Also resets the state, because the current message was consumed.
  int append_fragment (ACE_Message_Block* current);

};



#if defined (__ACE_INLINE__)
# include "tao/GIOP_Message_State.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /*TAO_GIOP_MESSAGE_STATE_H*/
