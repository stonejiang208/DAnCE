// This may look like C, but it's really -*- C++ -*-


//=============================================================================
/**
 *  @file    IIOP_Acceptor.h
 *
 *  $Id$
 *
 *  IIOP specific acceptor processing
 *
 *
 *  @author Fred Kuhns <fredk@cs.wustl.edu>
 *  @author Ossama Othman <ossama@uci.edu>
 */
//=============================================================================


#ifndef TAO_IIOP_ACCEPTOR_H
#define TAO_IIOP_ACCEPTOR_H
#include "ace/pre.h"

#include "tao/Pluggable.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/IIOP_Connection_Handler.h"
#include "tao/Acceptor_Impl.h"

#include "ace/Acceptor.h"
#include "ace/SOCK_Acceptor.h"
#include "tao/GIOP_Message_State.h"

// TAO IIOP_Acceptor concrete call defination

/**
 * @class TAO_IIOP_Acceptor
 *
 * @brief TAO_IIOP_Acceptor
 *
 * The IIOP-specific bridge class for the concrete acceptor.
 */
class TAO_Export TAO_IIOP_Acceptor : public TAO_Acceptor
{
public:
  /// Constructor.
  TAO_IIOP_Acceptor (CORBA::Boolean flag = 0);

  /// Destructor.
  ~TAO_IIOP_Acceptor (void);

  /// @@ Helper method for the implementation repository, should go
  ///    away
  const ACE_INET_Addr& address (void) const;

  typedef ACE_Strategy_Acceptor<TAO_IIOP_Connection_Handler, ACE_SOCK_ACCEPTOR> TAO_IIOP_BASE_ACCEPTOR;
  typedef TAO_Creation_Strategy<TAO_IIOP_Connection_Handler> TAO_IIOP_CREATION_STRATEGY;
  typedef TAO_Concurrency_Strategy<TAO_IIOP_Connection_Handler> TAO_IIOP_CONCURRENCY_STRATEGY;
  typedef TAO_Accept_Strategy<TAO_IIOP_Connection_Handler, ACE_SOCK_ACCEPTOR> TAO_IIOP_ACCEPT_STRATEGY;

  // = The TAO_Acceptor methods, check the documentation in
  //   Pluggable.h for details.
  virtual int open (TAO_ORB_Core *orb_core,
                    int version_major,
                    int version_minor,
                    const char *address,
                    const char *options = 0);
  virtual int open_default (TAO_ORB_Core *orb_core,
                            int version_major,
                            int version_minor,
                            const char *options = 0);
  virtual int close (void);
  virtual int create_mprofile (const TAO_ObjectKey &object_key,
                               TAO_MProfile &mprofile);
  virtual int is_collocated (const TAO_Endpoint *endpoint);
  virtual CORBA::ULong endpoint_count (void);

  virtual int object_key (IOP::TaggedProfile &profile,
                          TAO_ObjectKey &key);

protected:

  /**
   * Implement the common part of the open*() methods.  This method is
   * virtual to allow a derived class implementation to be invoked
   * instead.
   */
  virtual int open_i (const ACE_INET_Addr &addr);

  /// Set the host name for the given addr.
  int hostname (TAO_ORB_Core *orb_core,
                ACE_INET_Addr &addr,
                char *&host);

  /**
   * Probe the system for available network interfaces, and initialize
   * the <addrs_> array with an ACE_INET_Addr for each network
   * interface.  The port for each initialized ACE_INET_Addr will be
   * set in the open_i() method.  This method only gets invoked when
   * no explicit hostname is provided in the specified endpoint.
   */
  int probe_interfaces (TAO_ORB_Core *orb_core);

  /// Parse protocol specific options.
  virtual int parse_options (const char *options);

  /// Obtain tcp properties that must be used by this acceptor, i.e.,
  /// initialize <tcp_properties_>.
  int init_tcp_properties (void);

  /**
   * Rather than creating a separate profile for each endpoint, this
   * version of <create_mprofile> method adds all endpoints to a
   * single IIOP profile, i.e., <mprofile> will not contain more than
   * one IIOP_Profile, no matter how many acceptors there are.
   */
  int create_rt_mprofile (const TAO_ObjectKey &object_key,
                          TAO_MProfile &mprofile);

protected:

  /// Array of ACE_INET_Addr instances, each one corresponding to a
  /// given network interface.
  ACE_INET_Addr *addrs_;

  /**
   * Cache the information about the endpoints serviced by this
   * acceptor.
   * There may in fact be multiple hostnames for this endpoint. For
   * example, if the IP address is INADDR_ANY (0.0.0.0) then there
   * will be possibly a different hostname for each interface.
   */
  char **hosts_;

  /// The number of host names cached in the hosts_ array (equivalent
  /// to the number of endpoints opened by this Acceptor).
  size_t endpoint_count_;

  /**
   * The GIOP version for this endpoint
   * @@ Theoretically they shouldn't be here!! We need to look at a
   * way to move this out
   */
  TAO_GIOP_Version version_;

  /// ORB Core.
  TAO_ORB_Core *orb_core_;

  /// TCP configuration properties to be used for all
  /// connections opened by this acceptor.
  TAO_IIOP_Properties tcp_properties_;

  /// Should we use GIOP lite??
  CORBA::Boolean lite_flag_;

private:

  /// the concrete acceptor, as a pointer to it's base class.
  TAO_IIOP_BASE_ACCEPTOR base_acceptor_;

  /// Acceptor strategies.
  TAO_IIOP_CREATION_STRATEGY *creation_strategy_;
  TAO_IIOP_CONCURRENCY_STRATEGY *concurrency_strategy_;
  TAO_IIOP_ACCEPT_STRATEGY *accept_strategy_;

};

#if defined(__ACE_INLINE__)
#include "tao/IIOP_Acceptor.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif  /* TAO_IIOP_ACCEPTOR_H */
