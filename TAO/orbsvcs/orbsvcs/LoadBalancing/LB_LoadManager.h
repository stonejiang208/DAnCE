// -*- C++ -*-

//=============================================================================
/**
 * @file   LB_LoadManager.h
 *
 * $Id$
 *
 * @author Ossama Othman <ossama@uci.edu>
 */
//=============================================================================


#ifndef TAO_LB_LOAD_MANAGER_H
#define TAO_LB_LOAD_MANAGER_H

#include "ace/pre.h"

#include "orbsvcs/CosLoadBalancingS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "LB_LoadAlertMap.h"
#include "LB_MonitorMap.h"
#include "LB_LoadListMap.h"
#include "LB_Pull_Handler.h"

#include "orbsvcs/PortableGroupC.h"

#include "orbsvcs/PortableGroup/PG_PropertyManager.h"
#include "orbsvcs/PortableGroup/PG_GenericFactory.h"
#include "orbsvcs/PortableGroup/PG_ObjectGroupManager.h"


/// Forward declarations
class TAO_LB_RoundRobin;
class TAO_LB_Random;
class TAO_LB_LeastLoaded;


class TAO_LoadBalancing_Export TAO_LB_LoadManager
  : public virtual POA_CosLoadBalancing::LoadManager,
    public virtual PortableServer::RefCountServantBase
{
public:

  /// Constructor.
  TAO_LB_LoadManager (void);

  /**
   * @name CosLoadBalancing::LoadManager Methods
   *
   * Methods required by the CosLoadBalancing::LoadManager interface.
   */
  //@{

  /// For the PUSH load monitoring style.
  virtual void push_loads (const PortableGroup::Location & the_location,
                           const CosLoadBalancing::LoadList & loads
                           ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Return the raw loads at the given location.
  virtual CosLoadBalancing::LoadList * get_loads (
      const PortableGroup::Location & the_location
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosLoadBalancing::LocationNotFound));

  /// Inform member at given location of load alert condition.
  virtual void enable_alert (PortableGroup::ObjectGroup_ptr object_group,
                             const PortableGroup::Location & the_location
                             ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((PortableGroup::ObjectGroupNotFound,
                     CosLoadBalancing::LoadAlertNotFound));

  /// Inform member at given location that load alert condition has
  /// passed.
  virtual void disable_alert (PortableGroup::ObjectGroup_ptr object_group,
                              const PortableGroup::Location & the_location
                              ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((PortableGroup::ObjectGroupNotFound,
                     CosLoadBalancing::LoadAlertNotFound));

  /// Register a LoadAlert object for the member at the given
  /// location.
  virtual void register_load_alert (
      PortableGroup::ObjectGroup_ptr object_group,
      const PortableGroup::Location & the_location,
      CosLoadBalancing::LoadAlert_ptr load_alert
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound,
                     CosLoadBalancing::LoadAlertAlreadyPresent,
                     CosLoadBalancing::LoadAlertNotAdded));

  /// Retrieve the LoadAlert object for the member at the given
  /// location.
  virtual CosLoadBalancing::LoadAlert_ptr get_load_alert (
      PortableGroup::ObjectGroup_ptr object_group,
      const PortableGroup::Location & the_location
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound,
                     CosLoadBalancing::LoadAlertNotFound));

  /// Remove (de-register) the LoadAlert object for the member at the
  /// given location.
  virtual void remove_load_alert (PortableGroup::ObjectGroup_ptr object_group,
                                  const PortableGroup::Location & the_location
                                  ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound,
                     CosLoadBalancing::LoadAlertNotFound));

  /// Register a load monitor with the load balancer.
  virtual void register_load_monitor (
      CosLoadBalancing::LoadMonitor_ptr load_monitor,
      const PortableGroup::Location & the_location
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosLoadBalancing::MonitorAlreadyPresent));

  /// Return a reference to the load monitor at the given location.
  virtual CosLoadBalancing::LoadMonitor_ptr get_load_monitor (
      const PortableGroup::Location & the_location
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosLoadBalancing::LocationNotFound));

  /// Remove a load monitor at the given location from the load
  /// balancer.
  virtual void remove_load_monitor (
      const PortableGroup::Location & the_location
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     CosLoadBalancing::LocationNotFound));

  //@}

  /**
   * @name PortableGroup::PropertyManager Methods
   *
   * Methods required by the PortableGroup::PropertyManager interface.
   */
  //@{

  /// Set the default properties to be used by all object groups.
  virtual void set_default_properties (
      const PortableGroup::Properties & props
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::InvalidProperty,
                     PortableGroup::UnsupportedProperty));

  /// Get the default properties used by all object groups.
  virtual PortableGroup::Properties * get_default_properties (
      ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Remove default properties.
  virtual void remove_default_properties (
      const PortableGroup::Properties & props
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::InvalidProperty,
                     PortableGroup::UnsupportedProperty));

  /// Set properties associated with a given Replica type.  These
  /// properties override the default properties.
  virtual void set_type_properties (
      const char * type_id,
      const PortableGroup::Properties & overrides
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::InvalidProperty,
                     PortableGroup::UnsupportedProperty));

  /**
   * Return the properties associated with a give Replica type.  These
   * properties include the type-specific properties in use, in
   * addition to the default properties that were not overridden.
   */
  virtual PortableGroup::Properties * get_type_properties (
      const char * type_id
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Remove the given properties associated with the Replica type ID.
  virtual void remove_type_properties (
      const char * type_id,
      const PortableGroup::Properties & props
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::InvalidProperty,
                     PortableGroup::UnsupportedProperty));

  /**
   * Dynamically set the properties associated with a given object
   * group as the load balancer and replicas are being executed.
   * These properties override the type-specific and default
   * properties.
   */
  virtual void set_properties_dynamically (
      PortableGroup::ObjectGroup_ptr object_group,
      const PortableGroup::Properties & overrides
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound,
                     PortableGroup::InvalidProperty,
                     PortableGroup::UnsupportedProperty));

  /**
   * Return the properties currently in use by the given object
   * group.  These properties include those that were set dynamically,
   * type-specific properties that weren't overridden, properties that
   * were used when the Replica was created, and default properties
   * that weren't overridden.
   */
  virtual PortableGroup::Properties * get_properties (
      PortableGroup::ObjectGroup_ptr object_group
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound));

  //@}

  /**
   * @name PortableGroup::ObjectGroupManager methods
   *
   * Methods required by the PortableGroup::ObjectGroupManager
   * interface.
   */
  //@{

  /// Create a member using the load balancer ObjectGroupManager, and
  /// add the created object to the ObjectGroup.
  virtual PortableGroup::ObjectGroup_ptr create_member (
      PortableGroup::ObjectGroup_ptr object_group,
      const PortableGroup::Location & the_location,
      const char * type_id,
      const PortableGroup::Criteria & the_criteria
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound,
                     PortableGroup::MemberAlreadyPresent,
                     PortableGroup::NoFactory,
                     PortableGroup::ObjectNotCreated,
                     PortableGroup::InvalidCriteria,
                     PortableGroup::CannotMeetCriteria));

  /// Add an existing object to the ObjectGroup.
  virtual PortableGroup::ObjectGroup_ptr add_member (
      PortableGroup::ObjectGroup_ptr object_group,
      const PortableGroup::Location & the_location,
      CORBA::Object_ptr member
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound,
                     PortableGroup::MemberAlreadyPresent,
                     PortableGroup::ObjectNotAdded));

  /**
   * Remove an object at a specific location from the given
   * ObjectGroup.  Deletion of application created objects must be
   * deleted by the application.  Objects created by the
   * infrastructure (load balancer) will be deleted by the
   * infrastructure.
   */
  virtual PortableGroup::ObjectGroup_ptr remove_member (
      PortableGroup::ObjectGroup_ptr object_group,
      const PortableGroup::Location & the_location
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound,
                     PortableGroup::MemberNotFound));

  /// Return the locations of the members in the given ObjectGroup.
  virtual PortableGroup::Locations * locations_of_members (
      PortableGroup::ObjectGroup_ptr object_group
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound));

  /// Return the ObjectGroupId for the given ObjectGroup.
  virtual PortableGroup::ObjectGroupId get_object_group_id (
      PortableGroup::ObjectGroup_ptr object_group
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound));

  /// @note Does this method make sense for load balanced objects?
  virtual PortableGroup::ObjectGroup_ptr get_object_group_ref (
      PortableGroup::ObjectGroup_ptr object_group
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound));

  /// Return the reference corresponding to the Replica of a given
  /// ObjectGroup at the given location.
  virtual CORBA::Object_ptr get_member_ref (
      PortableGroup::ObjectGroup_ptr object_group,
      const PortableGroup::Location & loc
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectGroupNotFound,
                     PortableGroup::MemberNotFound));

  //@}

  /**
   * @name PortableGroup::GenericFactory methods
   *
   * Methods required by the PortableGroup::GenericFactory interface.
   */
  //@{

  /**
   * Create an object of the specified type that adheres to the
   * restrictions defined by the provided Criteria.  The out
   * FactoryCreationId parameter may be passed to the delete_object()
   * method to delete the object.
   */
  virtual CORBA::Object_ptr create_object (
      const char * type_id,
      const PortableGroup::Criteria & the_criteria,
      PortableGroup::GenericFactory::FactoryCreationId_out
        factory_creation_id
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::NoFactory,
                     PortableGroup::ObjectNotCreated,
                     PortableGroup::InvalidCriteria,
                     PortableGroup::InvalidProperty,
                     PortableGroup::CannotMeetCriteria));

  /**
   * Delete the object corresponding to the provided
   * FactoryCreationId.  If the object is actually an ObjectGroup,
   * then all members within the ObjectGroup will be deleted.
   * Afterward, the ObjectGroup itself will be deleted.
   */
  virtual void delete_object (
      const PortableGroup::GenericFactory::FactoryCreationId &
        factory_creation_id
      ACE_ENV_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     PortableGroup::ObjectNotFound));

  //@}

  /// Return the next member to which client requests will be
  /// forwarded.
  /**
   * Select the next member of the object group corresponding to the
   * given ObjectId.  The object group's load balancing strategy
   * will be queried for that member.
   */
  CORBA::Object_ptr next_member (const PortableServer::ObjectId & oid
                                 ACE_ENV_ARG_DECL);

public:

  /// Initialize the load balancer.  This will cause a child POA to be
  /// created with the appropriate policies to support ServantLocators
  /// (i.e. for the MemberLocator).
  void init (ACE_Reactor * reactor,
             CORBA::ORB_ptr orb,
             PortableServer::POA_ptr root_poa
             ACE_ENV_ARG_DECL);

protected:

  /// Destructor.
  /**
   * Destructor is protected to enforce correct memory management
   * through reference counting.
   */
  ~TAO_LB_LoadManager (void);

private:

  /// Extract the value of the InitialNumberReplicas property from
  /// the_criteria.
  int get_initial_number_replicas (
    const char * type_id,
    const PortableGroup::Criteria & the_criteria,
    CORBA::UShort & initial_number_replicas) const;

  /// Extract the value of the Factories property from the_criteria.
  /**
   * This method ensures that the locations in the returned
   * FactoryInfos are unique.  This is necessary to ensure that only
   * one replica of a given type is created by the load balancer at a
   * given location.
   */
  int get_factory_infos (
    const char * type_id,
    const PortableGroup::Criteria & the_criteria,
    PortableGroup::FactoryInfos & factory_infos) const;

  /// Return a reference to the built-in load balancing strategy named
  /// "strategy."
  CosLoadBalancing::Strategy_ptr built_in_strategy (const char * strategy);

  /// Check validity of Strategy or CustomStrategy property.
  /**
   * If a "LeastLoaded" Strategy is found in the property list, the
   * LeastLoaded Strategy implementation will be initialized with the
   * provided LeastLoaded-specific properties.
   */
  void check_strategy_prop (const PortableGroup::Properties & props
                            ACE_ENV_ARG_DECL);

  /// Initialize the built-in LeastLoaded Strategy with the given
  /// LeastLoaded properties.
  void init_least_loaded (const PortableGroup::Properties & props
                        ACE_ENV_ARG_DECL);

  /// Utility method to extract a CORBA::Float value from the given
  /// property.
  /**
   * @note This method is really only used when initializing the
   *       LeastLoaded built-in Strategy.
   */
  void extract_float_property (const PortableGroup::Property & property,
                               CORBA::Float & value
                               ACE_ENV_ARG_DECL);

private:

  /// Reactor used when pulling loads from registered load monitors.
  ACE_Reactor * reactor_;

  /// The POA that dispatches requests to the ReplicaLocator.
  PortableServer::POA_var poa_;

  /// Mutex that provides synchronization for the LoadMonitor map.
  TAO_SYNCH_MUTEX monitor_lock_;

  /// Mutex that provides synchronization for the LoadMap table.
  TAO_SYNCH_MUTEX load_lock_;

  /// Mutex that provides synchronization for the LoadAlert table.
  TAO_SYNCH_MUTEX load_alert_lock_;

  /// Mutex that provides synchronization for the LoadManager's
  /// state.
  TAO_SYNCH_MUTEX lock_;

  /// Table that maps PortableGroup::Location to load monitor at that
  /// location.
  TAO_LB_MonitorMap monitor_map_;

  /// Table that maps location to load list.
  TAO_LB_LoadListMap load_map_;

  /// Table that maps object group and location to LoadAlert object.
  TAO_LB_LoadAlertMap load_alert_map_;

  /// The ObjectGroupManager that implements the functionality
  /// necessary for application-controlled object group membership.
  TAO_PG_ObjectGroupManager object_group_manager_;

  /// The PropertyManager that is reponsible for parsing all criteria,
  /// and keeping track of property-type_id associations.
  TAO_PG_PropertyManager property_manager_;

  /// The GenericFactory responsible for creating all object groups.
  TAO_PG_GenericFactory generic_factory_;

  /// The event handler that performs "pull monitoring" on all
  /// registered load monitors.
  TAO_LB_Pull_Handler pull_handler_;

  /// Timer ID corresponding to the timer that fires off the "pull
  /// monitoring" event handler.
  long timer_id_;

  /// Cached object reference that points to this servant.
  CosLoadBalancing::LoadManager_var lm_ref_;

  /// Cached object reference that points to the AMI handler for all
  /// LoadAlert objects.
  CosLoadBalancing::AMI_LoadAlertHandler_var load_alert_handler_;

  /**
   * @name Built-in load balancing strategy implementations
   *
   * "Built-in" load balancing strategies defined by the load
   * balancing specification.
   */
  //@{
  /// The "RoundRobin" load balancing strategy.
  TAO_LB_RoundRobin * round_robin_;

  /// The "Random" load balancing strategy.
  TAO_LB_Random * random_;

  /// The "LeastLoaded" load balancing strategy.
  TAO_LB_LeastLoaded * least_loaded_;
  //@}

  /// Cached instance of the Property name
  /// "org.omg.CosLoadBalancing.Strategy".
  PortableGroup::Name built_in_balancing_strategy_name_;

  /// Cached instance of the Property name
  /// "org.omg.CosLoadBalancing.CustomStrategy".
  PortableGroup::Name custom_balancing_strategy_name_;

};


#include "ace/post.h"

#endif  /* TAO_LB_LOAD_MANAGER_H */
