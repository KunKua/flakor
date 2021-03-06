/**********************************************************
 * Copyright (c) 2013-2015 Steve Hsu  All Rights Reserved.
 *********************************************************/

#include "base/lang/Ref.h"

FLAKOR_NS_BEGIN

Ref::Ref() :
_refCount(new RefCount())
{
    // Hold a weak ref to self to avoid possible double delete of the refcount
    (_refCount->_weakRefs)++;
}

Ref::~Ref()
{
    FKAssert(_refCount,"refcount cant be null");
    FKAssert(_refCount->_refs == 0,"refcount cant be 0");
    FKAssert(_refCount->_weakRefs > 0,"refcount cant be 0");
    
    // Mark object as expired, release the self weak ref and delete the refcount if no other weak refs exist
    _refCount->_refs = -1;
    (_refCount->_weakRefs)--;
    if (!_refCount->_weakRefs)
        delete _refCount;
    
    _refCount = 0;
}

void Ref::addRef()
{
    FKAssert(_refCount->_refs >= 0,"refcount cant be less than 0");
    (_refCount->_refs)++;
}

void Ref::releaseRef()
{
    FKAssert(_refCount->_refs > 0,"refcount must be greater than 0");
    (_refCount->_refs)--;
    if (!_refCount->_refs)
        delete this;
}

int Ref::getRefs() const
{
    return _refCount->_refs;
}

int Ref::getWeakRefs() const
{
    // Subtract one to not return the internally held reference
    return _refCount->_weakRefs - 1;
}

FLAKOR_NS_END
