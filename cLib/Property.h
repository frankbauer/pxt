#ifndef __PROPERTY__
#define __PROPERTY__

template<class PropertyType, class ParentObject>
class Property
{
    typedef PropertyType (ParentObject::* propertyGetter)() const;

    ParentObject& m_objInstance;
    propertyGetter     getterMethod;

public:
    Property(ParentObject& objInstance, propertyGetter pGet)
    :  m_objInstance(objInstance), getterMethod(pGet)
    {}
    operator PropertyType() { return (m_objInstance.*getterMethod)(); }
};

#endif