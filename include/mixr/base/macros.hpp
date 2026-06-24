#pragma once

//------------------------------------------------------------------------------
// Object class macros:
//
//    DECLARE_SUBCLASS(ThisType, BaseType)
//       Macro to declare all of the required member functions and member
//       variables for the class 'ThisType', which is derived from class 'BaseType'.
//       Defines the type 'BaseClass', which can be used by the member functions as an
//       alias for the base class.  The copy constructor is declared by this macro, but
//       the user is required to declare any additional constructors including the
//       standard constructor (i.e., no arguments; Foo()).
//
//    IMPLEMENT_SUBCLASS(ThisType, "factoryName")
//       Macro to implement a standard set of required member functions
//       and member variables for the class 'ThisType', and to set its factory name to
//       'factoryName'.  The user is required to implement the copyData() and deleteData()
//       functions, the slot table, and any constructors that the user
//       has declared.
//
//    IMPLEMENT_ABSTRACT_SUBCLASS(ThisType, "factoryName")
//       Macro to implement an abstract class.  Same as IMPLEMENT_SUBCLASS()
//       except that the clone function always returns a null pointer.
//
//    IMPLEMENT_PARTIAL_SUBCLASS(ThisType, "factoryName")
//       Same as IMPLEMENT_SUBCLASS() except that the copy constructor,
//       the destructor, the copy operator and the clone function are
//       left to the user to define (i.e., some time you just need to do
//       this yourself).
//
//    STANDARD_CONSTRUCTOR()
//       Common constructor tasks. This macro required in every constructor.
//
//    STANDARD_DESTRUCTOR()
//       Common destructor tasks. This macro required in every destructor.
//
//    BEGIN_SLOTTABLE(ThisType) and END_SLOTTABLE(ThisType)
//       These macros are used to define a slot table (see Object.hpp)
//       for the class 'ThisType'.
//
//    BEGIN_SLOT_MAP(ThisType) and END_SLOT_MAP()
//       These macros, along with the ON_SLOT() macro, define a slot
//       dispatch table, which maps local slot numbers and argument
//       types to "set slot" member functions that handle the setting of
//       slot argument values.  These macros are actually implementing
//       the setSlotByIndex() function for class 'ThisType'.
//
//    ON_SLOT(idx, setSlotFunc, ObjType)
//       Maps a local slot index number, 'idx', and slot argument type,
//       'ObjType', to a member function, 'setSlotFunc', that will
//       process the slot.
//
//    EMPTY_SLOTTABLE(ThisType)
//       Implements an empty slotTable for the class 'ThisType'
//
//    EMPTY_CONSTRUCTOR(ThisType)
//       Implements an empty default constructor for the class 'ThisType' (e.g., Foo())
//
//    EMPTY_COPYDATA(ThisType)
//       Implements an empty copy data function for the class 'ThisType'
//
//    EMPTY_DELETEDATA(ThisType)
//       Implements an empty delete data function for the class 'ThisType'
//
//    IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(ThisType, "factoryName")
//       Combines the IMPLEMENT_SUBCLASS() and EMPTY_SLOTTABLE() macros
//        for the class 'ThisType'
//
//
// Component class macros:
//
//    BEGIN_EVENT_HANDLER(ThisType) and END_EVENT_HANDLER()
//       These macros, along with the ON_EVENT() and ON_ANYKEY() macros
//       below, implement an event dispatch table, which is actually the
//       event() function for class 'ThisType'.
//
//       Typically "on event" functions are used to process the events.  The
//       "on event" function will return a true if the event is processed or
//       false if not.  Events that are not mapped or processed are passed
//       to the base class; up to and including the Component class, and 'Key'
//       events (see eventTokens.hpp) that are not mapped or processed by the
//       Component class are passed to the container class.
//
//    ON_EVENT(token,onEvent)  (see eventTokens.hpp)
//       Maps an event token, 'token', to the "on event" member function, 'onEvent'.
//
//    ON_EVENT_OBJ(token,onEvent,ObjType)
//       Maps an event token, 'token', with an argument of type 'ObjType' to the
//       "on event" member function, 'onEvent'.
//
//    ON_ANYKEY(onEvent)
//       Maps any event token to the "on event" member function, 'onEvent'.
//
//    ON_ANYKEY_OBJ(onEvent, ObjType)
//       Maps any event token with an argument of type 'ObjType' to the "on event"
//       member function, 'onEvent'.
//
//
// StateMachine class macros:
//
//    BEGIN_STATE_TABLE(ThisType) and END_STATE_TABLE()
//       These macros, along with the macros  below, implement a state dispatch
//       table, which is actually the stateTable() function for class 'ThisType'.
//
//    STATE_FUNC(state,stateFunc)
//       Maps a state number, 'state', to the member function, 'stateFunc', which
//       implements the state.
//
//    STATE_MACH(state,"name")
//       Maps a state number, 'state', to the name of child state machine that
//       implements the state.  The child state machines are defined for this
//       state machine using the 'stateMachines' slot.
//
//    ANY_STATE_FUNC(stateFunc)
//       Maps any state number to the member function, 'stateFunc'.
//
//------------------------------------------------------------------------------

// Caution: often many users new to the framework want to learn the internals of how these
// macros work.  Although a glorious endeavor, experience as proven that it's best
// to treat these macros, at least initially, as 'black boxes'.

#include <cstring>
#include <iostream>
#include <typeinfo>

#define DECLARE_SUBCLASS(ThisType, BaseType)                                                       \
    typedef BaseType BaseClass;                                                                    \
                                                                                                   \
public:                                                                                            \
    virtual ~ThisType() = default;                                                                           \
                                                                                                   \
public:                                                                                            \
    std::shared_ptr<ThisType> clone() const;                                                       \
                                                                                                   \
public:                                                                                            \
    ThisType& operator=(const ThisType& org) = default;                                            \
                                                                                                   \
public:                                                                                            \
    bool isClassType(const std::type_info& type) const override;                                   \
                                                                                                   \
protected:                                                                                           \
    static const std::shared_ptr<const ::mixr::base::MetaObject> metaObject;                       \
                                                                                                   \
public:                                                                                            \
    virtual const std::shared_ptr<const ::mixr::base::MetaObject>& getMetaObject() const override;                 \
                                                                                                   \
public:                                                                                            \
    static const std::string& getFactoryName();                                                    \
                                                                                                   \
public:                                                                                            \
    bool isFactoryName(const std::string& name) const override;                                    \
                                                                                                   \
protected:                                                                                         \
    bool setSlotByIndex(const int slotindex, ::mixr::base::Element obj) override;  \
    ::mixr::base::Element getSlotByIndex(const int slotindex) const override;  \
                                                                                                   \
public:                                                                                            \
    virtual const std::shared_ptr<const ::mixr::base::SlotTable>& getSlotTable() const override;                   \
                                                                                                   \
protected:                                                                                         \
    static const std::shared_ptr<const ::mixr::base::SlotTable> slotTable;                         \
                                                                                                   \
private:


#define IMPLEMENT_SUBCLASS(ThisType, FACTORYNAME)                                                  \
    const std::shared_ptr<const ::mixr::base::MetaObject> ThisType::metaObject =                   \
        std::make_shared<const ::mixr::base::MetaObject>(typeid(ThisType).name(), FACTORYNAME,     \
                                                         BaseClass::metaObject);              \
    const std::shared_ptr<const ::mixr::base::MetaObject>& ThisType::getMetaObject() const              \
    {                                                                                              \
        return ThisType::metaObject;                                                               \
    }                                                                                              \
    const std::string& ThisType::getFactoryName() { return metaObject->getFactoryName(); }         \
    bool ThisType::isFactoryName(const std::string& name) const                                    \
    {                                                                                              \
        if (name.empty())                                                                          \
            return false;                                                                          \
        if (metaObject->getFactoryName() == name)                                                  \
            return true;                                                                           \
        else                                                                                       \
            return ThisType::BaseClass::isFactoryName(name);                                       \
    }                                                                                              \
    const std::shared_ptr<const ::mixr::base::SlotTable>& ThisType::getSlotTable() const           \
    {                                                                                              \
        return ThisType::slotTable;                                                                \
    }                                                                                              \
    bool ThisType::isClassType(const std::type_info& type) const                                   \
    {                                                                                              \
        if (type == typeid(ThisType))                                                              \
            return true;                                                                           \
        else                                                                                       \
            return ThisType::BaseClass::isClassType(type);                                         \
    }                                                                                              \
    std::shared_ptr<ThisType> ThisType::clone() const                                              \
    {                                                                                              \
        return std::make_shared<ThisType>(*this);                                                  \
    }


#define IMPLEMENT_PARTIAL_SUBCLASS(ThisType, FACTORYNAME)                                          \
    const std::shared_ptr<const ::mixr::base::MetaObject> ThisType::metaObject =                   \
        std::make_shared<const ::mixr::base::MetaObject>(typeid(ThisType).name(), FACTORYNAME,     \
                                                         BaseClass::getMetaObject());              \
    const std::shared_ptr<const ::mixr::base::MetaObject>& ThisType::getMetaObject()               \
    {                                                                                              \
        return metaObject;                                                                         \
    }                                                                                              \
    const std::string& ThisType::getFactoryName() { return metaObject->getFactoryName(); }         \
    bool ThisType::isFactoryName(const std::string& name) const                                    \
    {                                                                                              \
        if (name.empty())                                                                          \
            return false;                                                                          \
        if (metaObject->getFactoryName() == name)                                                  \
            return true;                                                                           \
        else                                                                                       \
            return ThisType::BaseClass::isFactoryName(name);                                       \
    }                                                                                              \
    const std::shared_ptr<const ::mixr::base::SlotTable>& ThisType::getSlotTable()                 \
    {                                                                                              \
        return ThisType::slotTable;                                                                \
    }                                                                                              \
    bool ThisType::isClassType(const std::type_info& type) const                                   \
    {                                                                                              \
        if (type == typeid(ThisType))                                                              \
            return true;                                                                           \
        else                                                                                       \
            return ThisType::BaseClass::isClassType(type);                                         \
    }


#define IMPLEMENT_ABSTRACT_SUBCLASS(ThisType, FACTORYNAME)                                         \
    const std::shared_ptr<const ::mixr::base::MetaObject> ThisType::metaObject =                   \
        std::make_shared<const ::mixr::base::MetaObject>(typeid(ThisType).name(), FACTORYNAME,     \
                                                         BaseClass::metaObject);              \
    const std::shared_ptr<const ::mixr::base::MetaObject>& ThisType::getMetaObject()               \
    {                                                                                              \
        return ThisType::metaObject;                                                                         \
    }                                                                                              \
    const std::string& ThisType::getFactoryName() { return metaObject->getFactoryName(); }         \
    bool ThisType::isFactoryName(const std::string& name) const                                    \
    {                                                                                              \
        if (name.empty())                                                                          \
            return false;                                                                          \
        if (metaObject->getFactoryName() == name)                                                  \
            return true;                                                                           \
        else                                                                                       \
            return ThisType::BaseClass::isFactoryName(name);                                       \
    }                                                                                              \
    const std::shared_ptr<const ::mixr::base::SlotTable>& ThisType::getSlotTable()                 \
    {                                                                                              \
        return ThisType::slotTable;                                                                \
    }                                                                                              \
    bool ThisType::isClassType(const std::type_info& type) const                                   \
    {                                                                                              \
        if (type == typeid(ThisType))                                                              \
            return true;                                                                           \
        else                                                                                       \
            return ThisType::BaseClass::isClassType(type);                                         \
    }                                                                                              \
    std::shared_ptr<ThisType> ThisType::clone() const \
    {                                                                                              \
        return nullptr;                                                                            \
    }


#define EMPTY_SLOTTABLE(ThisType)                                                                  \
    const std::shared_ptr<const ::mixr::base::SlotTable> ThisType::slotTable =                     \
        std::make_shared<::mixr::base::SlotTable>(std::vector<std::string>{},                      \
                                                  ThisType::BaseClass::slotTable);                  \
    bool ThisType::setSlotByIndex(const int si, ::mixr::base::Element obj)                          \
    {                                                                                              \
        return BaseClass::setSlotByIndex(si, obj);                                                 \
    }                                                                                               \
    ::mixr::base::Element ThisType::getSlotByIndex(const int si) const                       \
    {                                                                                              \
        return BaseClass::getSlotByIndex(si);                                                 \
    }

#define IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(ThisType, FACTORYNAME)                                  \
    IMPLEMENT_SUBCLASS(ThisType, FACTORYNAME)                                                      \
    EMPTY_SLOTTABLE(ThisType)

/**
 * Slot table macros.
 */

#define BEGIN_SLOTTABLE(ThisType)                                                                  \
    const std::shared_ptr<const ::mixr::base::SlotTable> ThisType::slotTable =                \
    std::make_shared<::mixr::base::SlotTable>(std::vector<std::string> {


#define END_SLOTTABLE(ThisType)                                                                    \
    }, ThisType::BaseClass::slotTable);


/**
 * Getters using slots
 */

#define BEGIN_SLOT_GETTER_MAP(ThisType)                                                         \
    ::mixr::base::Element ThisType::getSlotByIndex(const int slotindex) const                   \
    {                                                                                           \
        const int _n{BaseClass::getSlotTable()->n()};                                           \
        if (slotindex <= _n)                                                                    \
        {                                                                                       \
            return BaseClass::getSlotByIndex(slotindex);                                        \
        }                                                                                       \
        int _n1{slotindex - _n};

#define GET_SLOT(idx, getFunc)                                                                  \
        if (idx == _n1)                                                                         \
        {                                                                                       \
            return getFunc();                                                                   \
        }

#define END_SLOT_GETTER_MAP()                                                                   \
        return nullptr;                                                                         \
    }

/**
 * Setters using slots
 */

#define BEGIN_SLOT_SETTER_MAP(ThisType)                                                        \
    bool ThisType::setSlotByIndex(const int slotindex, ::mixr::base::Element obj)               \
    {                                                                                           \
        const int _n{BaseClass::getSlotTable()->n()};                                           \
        if (slotindex <= _n)                                                                    \
        {                                                                                       \
            return BaseClass::setSlotByIndex(slotindex, obj);                                   \
        }                                                                                       \
        bool _ok{};                                                                             \
        int _n1{slotindex - _n};


#define END_SLOT_SETTER_MAP()                                                                  \
        return _ok;                                                                             \
    }

#define ON_SLOT_BOOL(idx, setFunc)                                                             \
if (!_ok && std::holds_alternative<std::shared_ptr<bool>>(obj))                                \
{                                                                                              \
    const std::shared_ptr<bool> _msg = std::get<std::shared_ptr<bool>>(obj);                   \
    if (idx == _n1 && _msg != nullptr)                                                         \
    {                                                                                          \
        _ok = setFunc(_msg);                                                                   \
    }                                                                                          \
}

#define ON_SLOT_REAL(idx, setFunc)                                                             \
if (!_ok && std::holds_alternative<std::shared_ptr<double>>(obj))                                \
{                                                                                              \
    const std::shared_ptr<double> _msg = std::get<std::shared_ptr<double>>(obj);                   \
    if (idx == _n1 && _msg != nullptr)                                                         \
    {                                                                                          \
        _ok = setFunc(_msg);                                                                   \
    }                                                                                          \
}

#define ON_SLOT_STRING(idx, setFunc)                                                             \
if (!_ok && std::holds_alternative<std::shared_ptr<std::string>>(obj))                           \
{                                                                                              \
    const std::shared_ptr<std::string> _msg = std::get<std::shared_ptr<std::string>>(obj);        \
    if (idx == _n1 && _msg != nullptr)                                                         \
    {                                                                                          \
        _ok = setFunc(_msg);                                                                   \
    }                                                                                          \
}

#define ON_SLOT_OBJECT(idx, setFunc, ObjType)                                                             \
    if (!_ok && std::holds_alternative<std::shared_ptr<ObjType>>(obj))                                                                                      \
    {                                                                                              \
        const std::shared_ptr<ObjType> _msg = std::dynamic_pointer_cast<ObjType>(std::get<std::shared_ptr<::mixr::base::Object>>(obj));             \
        if (idx == _n1 && _msg != nullptr)                                                         \
        {                                                                                          \
            _ok = setFunc(_msg);                                                                   \
        }                                                                                          \
    }


#define BEGIN_EVENT_HANDLER(ThisType)                                                              \
    bool ThisType::event(const int _event, std::shared_ptr<::mixr::base::Object> _obj)             \
    {                                                                                              \
        bool _used{};


#define END_EVENT_HANDLER()                                                                        \
    if (!_used)                                                                                    \
        _used = BaseClass::event(_event, _obj);                                                    \
    return _used;                                                                                  \
    }


#define ON_EVENT_OBJ(token, onEvent, ObjType)                                                      \
    if (!_used && token == _event && std::dynamic_pointer_cast<ObjType>(_obj) != nullptr)          \
    {                                                                                              \
        _used = onEvent(std::static_pointer_cast<ObjType>(_obj));                                  \
    }


#define ON_EVENT(token, onEvent)                                                                   \
    if (!_used && token == _event)                                                                 \
    {                                                                                              \
        _used = onEvent();                                                                         \
    }


#define ON_ANYKEY_OBJ(onEvent, ObjType)                                                            \
    if (!_used && _event <= MAX_KEY_EVENT && dynamic_cast<ObjType*>(_obj) != nullptr)              \
    {                                                                                              \
        _used = onEvent(_event, (static_cast<ObjType*>(_obj)));                                    \
    }


#define ON_ANYKEY(onEvent)                                                                         \
    if (!_used && _event <= MAX_KEY_EVENT)                                                         \
    {                                                                                              \
        _used = onEvent(_event);                                                                   \
    }


#define BEGIN_STATE_TABLE(ThisType)                                                                \
    unsigned short ThisType::stateTable(const unsigned short _cstate, const StateTableCode _code,  \
                                        const double _dt)                                          \
    {                                                                                              \
        unsigned short _next = INVALID_STATE;                                                      \
        bool _ok{};


#define END_STATE_TABLE()                                                                          \
    return _next;                                                                                  \
    }


#define STATE_FUNC(state, stateFunc)                                                               \
    if (state == _cstate)                                                                          \
    {                                                                                              \
        if (_code == StateTableCode::CURR_STATE)                                                   \
        {                                                                                          \
            setStMach(0, _code);                                                                   \
            stateFunc(_dt);                                                                        \
        }                                                                                          \
        else if (_code == StateTableCode::TEST_STATE)                                              \
            _next = state;                                                                         \
        _ok = true;                                                                                \
    }                                                                                              \
    else if (_code == StateTableCode::FIND_NEXT_STATE && _ok && _next == INVALID_STATE)            \
    {                                                                                              \
        _next = state;                                                                             \
    }


#define STATE_MACH(state, name)                                                                    \
    if (state == _cstate)                                                                          \
    {                                                                                              \
        _ok = setStMach(name, _code);                                                              \
        if (_ok && _code == StateTableCode::TEST_STATE)                                            \
            _next = state;                                                                         \
    }                                                                                              \
    else if (_code == StateTableCode::FIND_NEXT_STATE && _ok && _next == INVALID_STATE)            \
    {                                                                                              \
        _next = state;                                                                             \
    }


#define ANY_STATE_FUNC(stateFunc)                                                                  \
    if (_code == StateTableCode::CURR_STATE && !_ok)                                               \
    {                                                                                              \
        setStMach(0, _code);                                                                       \
        stateFunc(_dt);                                                                            \
        _ok = true;                                                                                \
    }                                                                                              \
    else if (_code == StateTableCode::TEST_STATE && !_ok)                                          \
    {                                                                                              \
        _next = _cstate;                                                                           \
        _ok = true;                                                                                \
    }                                                                                              \
    else if (_code == StateTableCode::FIND_NEXT_STATE && _next == INVALID_STATE)                   \
    {                                                                                              \
        _next = _cstate + 1; /* next is just one more! */                                          \
    }


#define DECLARE_SLOT(slot_name, slot_type)                                                         \
public:                                                                                            \
    bool set_slot_##slot_name(const std::shared_ptr<slot_type>&);                                  \
                                                                                                   \
public:                                                                                            \
    std::shared_ptr<slot_type> get_slot_##slot_name() const;
