/* -*- C++ -*- */
/**
 *  @file Property_T.h
 *
 *  $Id$
 *
 *  @author Pradeep Gore <pradeep@oomworks.com>
 *
 *
 */

#ifndef TAO_NS_PROPERTY_T_H
#define TAO_NS_PROPERTY_T_H
#include "ace/pre.h"

#include "notify_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/SString.h"
#include "orbsvcs/CosNotificationC.h"

class TAO_NS_PropertySeq;

/**
 * @class TAO_NS_PropertyBase_T
 *
 * @brief
 *
 */
template <class TYPE>
class TAO_NS_PropertyBase_T
{
public:
  /// Constuctor
  TAO_NS_PropertyBase_T (const char* name, const TYPE& initial);

  /// Constuctor
  TAO_NS_PropertyBase_T (const char* name);

  /// Copy Constuctor
  TAO_NS_PropertyBase_T (const TAO_NS_PropertyBase_T &rhs);

  /// Destructor
  ~TAO_NS_PropertyBase_T ();

  /// Assignment from TAO_NS_PropertyBase_T
  // TAO_NS_PropertyBase_T& operator= (const TAO_NS_PropertyBase_T& rhs);

  /// Assignment from TYPE
  TAO_NS_PropertyBase_T& operator= (const TYPE& rhs);

  /// Equality comparison operator.
  int operator== (const TYPE &rhs) const;

  /// Inequality comparison operator.
  int operator!= (const TYPE &rhs) const;

  /// Populate the Property Sequence with this valid value.
  void get (CosNotification::PropertySeq& prop_seq);

  /// Return the value.
  const TYPE& value (void) const;

  /// Is the current value valid
  CORBA::Boolean is_valid (void) const;

  /// Invalidate this property's value.
  void invalidate (void);

protected:
  /// The Property name.
  const char* name_;

  /// The value
  TYPE value_;

  /// Is the value valid
  CORBA::Boolean valid_;

private:
  ACE_UNIMPLEMENTED_FUNC (TAO_NS_PropertyBase_T& operator= (const TAO_NS_PropertyBase_T& rhs))
};


/*******************************************************************************/
/**
 * @class TAO_NS_Property_T
 *
 * @brief
 *
 */
template <class TYPE>
class TAO_NS_Property_T : public TAO_NS_PropertyBase_T<TYPE>
{
public:
  /// Constuctor
  TAO_NS_Property_T (const char* name, const TYPE& initial);

  /// Constuctor
  TAO_NS_Property_T (const char* name);

  /// Assignment from TYPE
  TAO_NS_Property_T& operator= (const TYPE& rhs);

  /// Init this Property from the sequence.
  /// Returns 0 on success, -1 on error
  int set (const TAO_NS_PropertySeq& property_seq);

  /// Init this Property from the CosNotification::PropertyValue
  /// Returns 0 on success, -1 on error
  int set (const CosNotification::PropertyValue &value);
};

/*******************************************************************************/
/**
 * @class TAO_NS_StructProperty_T
 *
 * @brief
 *
 */
template <class TYPE>
class TAO_NS_StructProperty_T
{
public:
  /// Constuctor
  TAO_NS_StructProperty_T (const char* name, const TYPE& initial);

  /// Constuctor
  TAO_NS_StructProperty_T (const char* name);

  /// Init this Property from the sequence.
  /// Returns 0 on success, -1 on error
  int set (const TAO_NS_PropertySeq& property_seq);

  /// Return the value.
  const TYPE& value (void) const;

  /// Is the current value valid
  CORBA::Boolean is_valid (void) const;

protected:
  /// The Property name.
  const char* name_;

  /// The value
  TYPE value_;

  /// Is the value valid
  CORBA::Boolean valid_;
};

#if defined (__ACE_INLINE__)
#include "Property_T.inl"
#endif /* __ACE_INLINE__ */

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "Property_T.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Property_T.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#include "ace/post.h"
#endif /* TAO_NS_PROPERTY_T_H */
