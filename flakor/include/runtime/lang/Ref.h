/**********************************************************
 * Copyright (c) 2013-2015 Steve Hsu  All Rights Reserved.
 *********************************************************/
#pragma once

#include "macros.h"

FLAKOR_NS_BEGIN

///引用计数结构
/// Reference count structure.
struct RefCount
{
    /// Construct.
    RefCount() :
        _refs(0),
        _weakRefs(0)
    {
    }
    
    /// Destruct.
    ~RefCount()
    {
        // Set reference counts below zero to fire asserts if this object is still accessed
        _refs = -1;
        _weakRefs = -1;
    }
    
    /// Reference count. If below zero, the object has been destroyed.
    int _refs;
    /// Weak reference count.
    int _weakRefs;
};

class IRefCountedObject
{
public:
	virtual uint32 addRef() const = 0;
	virtual uint32 releaseRef() const = 0;
	virtual uint32 getRefs() const = 0;
}

/// Base class for intrusively reference-counted objects. These are noncopyable and non-assignable.
class Ref
{
public:
    /// Construct. Allocate the reference count structure and set an initial self weak reference.
    Ref();
    /// Destruct. Mark as expired and also delete the reference count structure if no outside weak references exist.
    virtual ~Ref();
    
    /// Increment reference count. Can also be called outside of a SharedPtr for traditional reference counting.
    void addRef();
    /// Decrement reference count and delete self if no more references. Can also be called outside of a SharedPtr for traditional reference counting.
    void releaseRef();
    /// Return reference count.
    int getRefs() const;
    /// Return weak reference count.
    int getWeakRefs() const;
    /// Return pointer to the reference count structure.
    RefCount* getRefCountPtr() { return _refCount; }
    
private:
    /// Prevent copy construction.
    Ref(const Ref& rhs);
    /// Prevent assignment.
    Ref& operator = (const Ref& rhs);
    
    /// Pointer to the reference count structure.
    RefCount* _refCount;
};

FLAKOR_NS_END
