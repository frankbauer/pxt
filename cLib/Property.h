#ifndef __PROPERTY__
#define __PROPERTY__

template<class PropertyType, class ParentObject>
class ConstProperty
{
protected:
    typedef PropertyType (ParentObject::* propertyGetter)() const;

    ParentObject&      parentObject;
    propertyGetter     getterMethod;

public:
    ConstProperty(ParentObject& objInstance, propertyGetter pGet)
    :  parentObject(objInstance), getterMethod(pGet)
    {}
    operator PropertyType() { return (parentObject.*getterMethod)(); }
};

template<class PropertyType, class ParentObject>
class Property : public ConstProperty<PropertyType, ParentObject>
{
    using typename ConstProperty<PropertyType, ParentObject>::propertyGetter;
protected:
    typedef void (ParentObject::* propertySetter)(PropertyType);

    propertySetter     setterMethod;
public:
    Property(ParentObject& objInstance, propertyGetter pGet, propertySetter pSet)
    :  ConstProperty<PropertyType, ParentObject>(objInstance, pGet), setterMethod(pSet)
    {}
    void operator =(PropertyType value) { (ConstProperty<PropertyType, ParentObject>::parentObject.*setterMethod)(value); }
};

#endif