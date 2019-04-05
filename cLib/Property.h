#ifndef __PROPERTY__
#define __PROPERTY__

template<class _Prop_t,
         class _ObjClass_t>
class Property
{
    typedef _Prop_t (_ObjClass_t::* _pmGet_t)() const;

    _ObjClass_t& m_objInstance;
    _pmGet_t     m_pmGet;

public:
    Property(_ObjClass_t& objInstance, _pmGet_t pmGet)
    :  m_objInstance(objInstance), m_pmGet(pmGet)
    {}
    operator _Prop_t() { return (m_objInstance.*m_pmGet)(); }
};

#endif