// -*- C++ -*-

// =========================================================================
/**
 *  @file   AMH_Response_Handler.h
 *
 *  $Id$
 *
 *  @author Mayur Deshpande <mayur@ics.uci.edu>
 *
 */
// =========================================================================

#ifndef TAO_AMH_RESPONSE_HANDLER_H
#define TAO_AMH_RESPONSE_HANDLER_H

#include "tao/Service_Context.h"
#include "ace/Synch_T.h"

#include "portableserver_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class TAO_Transport;
class TAO_Pluggable_Messaging;
class TAO_Output_CDR;
class TAO_ORB_Core;
class TAO_ServerRequest;

/**
 * @class TAO_AMH_Response_Handler
 *
 * @brief Class representing an Asynchronous-Method-Handling (AMH)
 * ResponseHandler (RH) object.
 *
 * Class encapsulates state required to send a response back to the
 * client independent of the thread that originally created the state
 * on the activation-record.  Thus the required state (copied from
 * TAO_Server_Request) is 'stored' on the heap.
 *
 * One RH is created for every client request and the RH can be used
 * only once i.e.,  the asynchronous method can be called only once.
 * This class also encapsulates various initialisation and
 * response-sending functionality that is common to all RHs (generated
 * by the IDL compiler). Thus the IDL-compiler has to generate less
 * code which in turn reduces the overall code size for an
 * application.
 */
class TAO_PortableServer_Export TAO_AMH_Response_Handler
{
public:

  /// Constructor
  /**
   * Stores necessary information from a TAO_Server_Request onto the heap
   */
  TAO_AMH_Response_Handler (TAO_ServerRequest &server_request);

  /// Destructor
  /**
   * Releases the transport and in case of an error, sends the appropriate
   * exception back to the client
   */
  virtual ~TAO_AMH_Response_Handler (void);

protected:

  /// Sets up the various paramters in anticipation of returning a reply
  /// to the client. return/OUT/INOUT arguments are marshalled into the
  /// Output stream after this method has been called.
  void _tao_rh_init_reply (void);

  /// Sends the marshalled reply back to the client.
  void _tao_rh_send_reply (void);

  /// Send back an exception to the client.
  void _tao_rh_send_exception (CORBA::Exception &ex
                               ACE_ENV_ARG_DECL);

protected:

  /// The outgoing CDR stream
  /**
   * The IDL-generated ResponseHandler implementations used this field
   * to marshal the response.
   * Making it a field instead of a public accessor makes the code in
   * the generated ResponseHandler implementation a lot more readable.
   */
  TAO_OutputCDR _tao_out;

private:

  // Private and undefined, standard C++ idiom to prohibit copying.
  ACE_UNIMPLEMENTED_FUNC (TAO_AMH_Response_Handler (const TAO_AMH_Response_Handler&))
  ACE_UNIMPLEMENTED_FUNC (TAO_AMH_Response_Handler& operator= (const TAO_AMH_Response_Handler&))

private:
  /// Pointer to the original message-base
  TAO_Pluggable_Messaging *mesg_base_;

  /// Copy of the request-id of the original Server-Request
  CORBA::ULong request_id_;

  /// For AMH, this seems a little redundant
  // @@ Mayur: it is *NOT* oneways need to be supported via AMH too,
  //    only sometimes they do not return anything!
  //  CORBA::Boolean response_expected_;

  /// Handle to transport through which the reply will be sent
  /// Copy of transport in original Server_Request
  TAO_Transport *transport_;

  /// A pointer to the ORB Core for the context where the request was
  /// created.
  TAO_ORB_Core *orb_core_;

  /// The reply service context
  TAO_Service_Context reply_service_context_;

  /// Alwyas set to true (we always have soemthing to return to the
  /// client
  // @@ Mayur: I think not!  This is used to generate padding in GIOP
  //    1.2 messages (where the payload must start on an 8-byte
  //    boundary.  But some replys have no payload (only header), in
  //    those cases you cannot insert the padding.  We need the
  //    ResponseHandler to set this field correctly!
  CORBA::Boolean argument_flag_;

  //  TAO_GIOP_ReplyStatusType exception_type_;
  /// Exception type (will be NO_EXCEPTION in the majority of the
  /// cases).
  // @@ Mayur: I do not think we need this one, we can deduce the type
  //    of reply depending on the _tao_rh_*() method called.
  CORBA::ULong exception_type_;

  /**
   * Various states the ResponseHnadler can be in.
   *
   * These states represent various states the RH can be in and
   * the states are used not only in implementing the 'once-only semantics of
   * RHs, but in making sure well the call thread-safe as well.
   */
  enum Reply_Status
    {
      TAO_RS_UNINITIALIZED,
      TAO_RS_INITIALIZED,
      TAO_RS_SENDING,
      TAO_RS_SENT
    };
  Reply_Status reply_status_;
  // I would use the "state pattern"..
  // Carlos, Isn't that an overkill?
  // @@ Mayur: it depends on what form of the "State Pattern" you
  //    use.  The more generic form, as described in GoF, uses a class
  //    for each state, super-elegant but indeed a bit heavy handed.
  //    The lighter-weight form (using a state variable  

  /// Mutex to ensure the AMH-RH method call is thread-safe.
  TAO_SYNCH_MUTEX mutex_;
};

#endif /* TAO_AMH_RESPONSE_HANDLER_H */
