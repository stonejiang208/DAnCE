// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

#ifndef _TAO_IDL_DYNAMICC_H_
#define _TAO_IDL_DYNAMICC_H_

#include "ace/pre.h"

#include "tao/corbafwd.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/Any.h"
#include "tao/Sequence.h"

#if defined (TAO_EXPORT_MACRO)
#undef TAO_EXPORT_MACRO
#endif
#define TAO_EXPORT_MACRO TAO_Export

#if defined (TAO_EXPORT_NESTED_CLASSES)
#  if defined (TAO_EXPORT_NESTED_MACRO)
#    undef TAO_EXPORT_NESTED_MACRO
#  endif /* defined (TAO_EXPORT_NESTED_MACRO) */
#  define TAO_EXPORT_NESTED_MACRO TAO_Export
#endif /* TAO_EXPORT_NESTED_CLASSES */

#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */

TAO_NAMESPACE  Dynamic
{
  enum ParameterMode
  {
        PARAM_IN,
        PARAM_OUT,
        PARAM_INOUT
  };
  typedef ParameterMode &ParameterMode_out;
  TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_ParameterMode;

  struct Parameter;
  class Parameter_var;

  struct TAO_Export Parameter
  {

#if !defined(__GNUC__) || !defined (ACE_HAS_GNUG_PRE_2_8)
    typedef Parameter_var _var_type;
#endif /* ! __GNUC__ || g++ >= 2.8 */

    static void _tao_any_destructor (void*);

    CORBA::Any argument;
    ACE_NESTED_CLASS (Dynamic, ParameterMode) mode;
  };

  class TAO_Export Parameter_var
  {
  public:
    Parameter_var (void); // default constructor
    Parameter_var (Parameter *);
    Parameter_var (const Parameter_var &); // copy constructor
    ~Parameter_var (void); // destructor

    Parameter_var &operator= (Parameter *);
    Parameter_var &operator= (const Parameter_var &);
    Parameter *operator-> (void);
    const Parameter *operator-> (void) const;

    operator const Parameter &() const;
    operator Parameter &();
    operator Parameter &() const;
    operator Parameter *&(); // variable-size types only

    // in, inout, out, _retn
    const Parameter &in (void) const;
    Parameter &inout (void);
    Parameter *&out (void);
    Parameter *_retn (void);
    Parameter *ptr (void) const;

  private:
    Parameter *ptr_;
  };

  class TAO_Export Parameter_out
  {
  public:
    Parameter_out (Parameter *&);
    Parameter_out (Parameter_var &);
    Parameter_out (const Parameter_out &);
    Parameter_out &operator= (const Parameter_out &);
    Parameter_out &operator= (Parameter *);
    operator Parameter *&();
    Parameter *&ptr (void);
    Parameter *operator-> (void);

  private:
    Parameter *&ptr_;
    // assignment from T_var not allowed
    void operator= (const Parameter_var &);
  };

  TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_Parameter;


#if !defined (TAO_USE_SEQUENCE_TEMPLATES)

#if !defined (__TAO_UNBOUNDED_SEQUENCE_DYNAMIC_PARAMETERLIST_CH_)
#define __TAO_UNBOUNDED_SEQUENCE_DYNAMIC_PARAMETERLIST_CH_

    class TAO_EXPORT_NESTED_MACRO _TAO_Unbounded_Sequence_Dynamic_ParameterList : public TAO_Unbounded_Base_Sequence
    {
    public:
      // = Initialization and termination methods.

      _TAO_Unbounded_Sequence_Dynamic_ParameterList (void); // Default constructor.
      _TAO_Unbounded_Sequence_Dynamic_ParameterList (CORBA::ULong maximum);
      _TAO_Unbounded_Sequence_Dynamic_ParameterList (CORBA::ULong maximum,
        CORBA::ULong length,
        Parameter *data,
        CORBA::Boolean release = 0);
      _TAO_Unbounded_Sequence_Dynamic_ParameterList (const _TAO_Unbounded_Sequence_Dynamic_ParameterList &rhs);
      _TAO_Unbounded_Sequence_Dynamic_ParameterList &operator= (const _TAO_Unbounded_Sequence_Dynamic_ParameterList &rhs);
      virtual ~_TAO_Unbounded_Sequence_Dynamic_ParameterList (void); // Dtor.
      // = Accessors.
      Parameter &operator[] (CORBA::ULong i);
      const Parameter &operator[] (CORBA::ULong i) const;
      // = Static operations.
      static Parameter *allocbuf (CORBA::ULong size);
      static void freebuf (Parameter *buffer);
      virtual void _allocate_buffer (CORBA::ULong length);
      virtual void _deallocate_buffer (void);
      // Implement the TAO_Base_Sequence methods (see Sequence.h)

      Parameter *get_buffer (CORBA::Boolean orphan = 0);
      const Parameter *get_buffer (void) const;
      void replace (CORBA::ULong max,
        CORBA::ULong length,
        Parameter *data,
        CORBA::Boolean release);
    };

#endif /* end #if !defined */


#endif /* !TAO_USE_SEQUENCE_TEMPLATES */

#if !defined (_DYNAMIC_PARAMETERLIST_CH_)
#define _DYNAMIC_PARAMETERLIST_CH_

  class ParameterList;
  class ParameterList_var;

  // *************************************************************
  // ParameterList
  // *************************************************************

  class TAO_Export ParameterList : public
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
    _TAO_Unbounded_Sequence_Dynamic_ParameterList
#else /* TAO_USE_SEQUENCE_TEMPLATES */
    TAO_Unbounded_Sequence<Parameter>
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */
  {
  public:
    ParameterList (void); // default ctor
    ParameterList (CORBA::ULong max); // uses max size
    ParameterList (
      CORBA::ULong max,
      CORBA::ULong length,
      Parameter *buffer,
      CORBA::Boolean release = 0
    );
    ParameterList (const ParameterList &); // copy ctor
    ~ParameterList (void);
    static void _tao_any_destructor (void*);

#if !defined(__GNUC__) || !defined (ACE_HAS_GNUG_PRE_2_8)
    typedef ParameterList_var _var_type;
#endif /* ! __GNUC__ || g++ >= 2.8 */

  };

#endif /* end #if !defined */


#if !defined (_DYNAMIC_PARAMETERLIST___VAR_CH_)
#define _DYNAMIC_PARAMETERLIST___VAR_CH_

  // *************************************************************
  // class Dynamic::ParameterList_var
  // *************************************************************

  class TAO_Export ParameterList_var
  {
  public:
    ParameterList_var (void); // default constructor
    ParameterList_var (ParameterList *);
    ParameterList_var (const ParameterList_var &); // copy constructor
    ~ParameterList_var (void); // destructor

    ParameterList_var &operator= (ParameterList *);
    ParameterList_var &operator= (const ParameterList_var &);
    ParameterList *operator-> (void);
    const ParameterList *operator-> (void) const;

    operator const ParameterList &() const;
    operator ParameterList &();
    operator ParameterList &() const;
    operator ParameterList *&(); // variable-size base types only

    Parameter & operator[] (CORBA::ULong index);
    const Parameter & operator[] (CORBA::ULong index) const;

    // in, inout, out, _retn
    const ParameterList &in (void) const;
    ParameterList &inout (void);
    ParameterList *&out (void);
    ParameterList *_retn (void);
    ParameterList *ptr (void) const;

  private:
    ParameterList *ptr_;
  };


#endif /* end #if !defined */


#if !defined (_DYNAMIC_PARAMETERLIST___OUT_CH_)
#define _DYNAMIC_PARAMETERLIST___OUT_CH_

  class TAO_Export ParameterList_out
  {
  public:
    ParameterList_out (ParameterList *&);
    ParameterList_out (ParameterList_var &);
    ParameterList_out (const ParameterList_out &);
    ParameterList_out &operator= (const ParameterList_out &);
    ParameterList_out &operator= (ParameterList *);
    operator ParameterList *&();
    ParameterList *&ptr (void);
    ParameterList *operator-> (void);
    Parameter & operator[] (CORBA::ULong index);

  private:
    ParameterList *&ptr_;
    // assignment from T_var not allowed
    void operator= (const ParameterList_var &);
  };


#endif /* end #if !defined */

  TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_ParameterList;

  typedef CORBA::StringSeq ContextList;
  typedef CORBA::StringSeq_var ContextList_var;
  typedef CORBA::StringSeq_out ContextList_out;
    TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_ContextList;

  typedef CORBA::TypeCode TypeCode;
  typedef CORBA::TypeCode_ptr TypeCode_ptr;
  typedef CORBA::TypeCode_var TypeCode_var;
  typedef CORBA::TypeCode_out TypeCode_out;
    TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_TypeCode;


#if !defined (TAO_USE_SEQUENCE_TEMPLATES)

#if !defined (__TAO_UNBOUNDED_OBJECT_SEQUENCE_DYNAMIC_EXCEPTIONLIST_CH_)
#define __TAO_UNBOUNDED_OBJECT_SEQUENCE_DYNAMIC_EXCEPTIONLIST_CH_

    class _TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList : public TAO_Unbounded_Base_Sequence
    {
    public:
      // = Initialization and termination methods.

      _TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList (void);
      _TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList (CORBA::ULong maximum);
      _TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList (CORBA::ULong maximum,
        CORBA::ULong length,
        CORBA::TypeCode* *value,
        CORBA::Boolean release = 0);
      _TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList(const _TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList &rhs);
      virtual ~_TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList (void);
      _TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList &operator= (const _TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList &rhs);
      TAO_Pseudo_Object_Manager<Dynamic::TypeCode,Dynamic::TypeCode_var> operator[] (CORBA::ULong index) const;
      static CORBA::TypeCode **allocbuf (CORBA::ULong nelems);
      static void freebuf (CORBA::TypeCode **buffer);
      // The Base_Sequence functions, please see tao/Sequence.h
      virtual void _allocate_buffer (CORBA::ULong length);
      virtual void _deallocate_buffer (void);
      CORBA::TypeCode* *get_buffer (CORBA::Boolean orphan = 0);
      const CORBA::TypeCode* *get_buffer (void) const;
      virtual void _shrink_buffer (CORBA::ULong nl, CORBA::ULong ol);

    };

#endif /* end #if !defined */


#endif /* !TAO_USE_SEQUENCE_TEMPLATES */

#if !defined (_DYNAMIC_EXCEPTIONLIST_CH_)
#define _DYNAMIC_EXCEPTIONLIST_CH_

  class ExceptionList;
  class ExceptionList_var;

  // *************************************************************
  // ExceptionList
  // *************************************************************

  class TAO_Export ExceptionList : public
#if !defined (TAO_USE_SEQUENCE_TEMPLATES)
    _TAO_Unbounded_Object_Sequence_Dynamic_ExceptionList
#else /* TAO_USE_SEQUENCE_TEMPLATES */
    TAO_Unbounded_Pseudo_Sequence<CORBA::TypeCode,CORBA::TypeCode_var>
#endif /* !TAO_USE_SEQUENCE_TEMPLATES */
  {
  public:
    ExceptionList (void); // default ctor
    ExceptionList (CORBA::ULong max); // uses max size
    ExceptionList (
      CORBA::ULong max,
      CORBA::ULong length,
      CORBA::TypeCode_ptr *buffer,
      CORBA::Boolean release = 0
    );
    ExceptionList (const ExceptionList &); // copy ctor
    ~ExceptionList (void);
    static void _tao_any_destructor (void*);

#if !defined(__GNUC__) || !defined (ACE_HAS_GNUG_PRE_2_8)
    typedef ExceptionList_var _var_type;
#endif /* ! __GNUC__ || g++ >= 2.8 */

  };

#endif /* end #if !defined */


#if !defined (_DYNAMIC_EXCEPTIONLIST___VAR_CH_)
#define _DYNAMIC_EXCEPTIONLIST___VAR_CH_

  // *************************************************************
  // class Dynamic::ExceptionList_var
  // *************************************************************

  class TAO_Export ExceptionList_var
  {
  public:
    ExceptionList_var (void); // default constructor
    ExceptionList_var (ExceptionList *);
    ExceptionList_var (const ExceptionList_var &); // copy constructor
    ~ExceptionList_var (void); // destructor

    ExceptionList_var &operator= (ExceptionList *);
    ExceptionList_var &operator= (const ExceptionList_var &);
    ExceptionList *operator-> (void);
    const ExceptionList *operator-> (void) const;

    operator const ExceptionList &() const;
    operator ExceptionList &();
    operator ExceptionList &() const;
    operator ExceptionList *&(); // variable-size base types only

    TAO_Pseudo_Object_Manager<TypeCode,TypeCode_var> operator[] (CORBA::ULong index);

    // in, inout, out, _retn
    const ExceptionList &in (void) const;
    ExceptionList &inout (void);
    ExceptionList *&out (void);
    ExceptionList *_retn (void);
    ExceptionList *ptr (void) const;

  private:
    ExceptionList *ptr_;
  };


#endif /* end #if !defined */


#if !defined (_DYNAMIC_EXCEPTIONLIST___OUT_CH_)
#define _DYNAMIC_EXCEPTIONLIST___OUT_CH_

  class TAO_Export ExceptionList_out
  {
  public:
    ExceptionList_out (ExceptionList *&);
    ExceptionList_out (ExceptionList_var &);
    ExceptionList_out (const ExceptionList_out &);
    ExceptionList_out &operator= (const ExceptionList_out &);
    ExceptionList_out &operator= (ExceptionList *);
    operator ExceptionList *&();
    ExceptionList *&ptr (void);
    ExceptionList *operator-> (void);
    TAO_Pseudo_Object_Manager<TypeCode,TypeCode_var> operator[] (CORBA::ULong index);

  private:
    ExceptionList *&ptr_;
    // assignment from T_var not allowed
    void operator= (const ExceptionList_var &);
  };


#endif /* end #if !defined */

  TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_ExceptionList;

  typedef CORBA::StringSeq RequestContext;
  typedef CORBA::StringSeq_var RequestContext_var;
  typedef CORBA::StringSeq_out RequestContext_out;
    TAO_NAMESPACE_STORAGE_CLASS CORBA::TypeCode_ptr _tc_RequestContext;


}
TAO_NAMESPACE_CLOSE // module Dynamic

TAO_Export void operator<<= (CORBA::Any &, Dynamic::ParameterMode);
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, Dynamic::ParameterMode &);
TAO_Export void operator<<= (CORBA::Any &, const Dynamic::Parameter &); // copying version
TAO_Export void operator<<= (CORBA::Any &, Dynamic::Parameter*); // noncopying version
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, Dynamic::Parameter *&); // deprecated
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, const Dynamic::Parameter *&);
TAO_Export void operator<<= (CORBA::Any &, const Dynamic::ParameterList &); // copying version
TAO_Export void operator<<= (CORBA::Any &, Dynamic::ParameterList*); // noncopying version
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, Dynamic::ParameterList *&); // deprecated
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, const Dynamic::ParameterList *&);
TAO_Export void operator<<= (CORBA::Any &, const Dynamic::ExceptionList &); // copying version
TAO_Export void operator<<= (CORBA::Any &, Dynamic::ExceptionList*); // noncopying version
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, Dynamic::ExceptionList *&); // deprecated
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, const Dynamic::ExceptionList *&);

#ifndef __ACE_INLINE__

TAO_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const Dynamic::ParameterMode &); //
TAO_Export CORBA::Boolean operator>> (TAO_InputCDR &, Dynamic::ParameterMode &);
TAO_Export CORBA::Boolean operator<< (TAO_OutputCDR &, const Dynamic::Parameter &);
TAO_Export CORBA::Boolean operator>> (TAO_InputCDR &, Dynamic::Parameter &);

#if !defined _TAO_CDR_OP_Dynamic_ParameterList_H_
#define _TAO_CDR_OP_Dynamic_ParameterList_H_

TAO_Export CORBA::Boolean operator<< (
    TAO_OutputCDR &,
    const Dynamic::ParameterList &
  );
TAO_Export CORBA::Boolean operator>> (
    TAO_InputCDR &,
    Dynamic::ParameterList &
  );

#endif /* _TAO_CDR_OP_Dynamic_ParameterList_H_ */


#if !defined _TAO_CDR_OP_Dynamic_ExceptionList_H_
#define _TAO_CDR_OP_Dynamic_ExceptionList_H_

TAO_Export CORBA::Boolean operator<< (
    TAO_OutputCDR &,
    const Dynamic::ExceptionList &
  );
TAO_Export CORBA::Boolean operator>> (
    TAO_InputCDR &,
    Dynamic::ExceptionList &
  );

#endif /* _TAO_CDR_OP_Dynamic_ExceptionList_H_ */


#endif /* __ACE_INLINE__ */


#if defined (__ACE_INLINE__)
#include "DynamicC.i"
#endif /* defined INLINE */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"
#endif /* ifndef */
