#ifndef BASE_AUTOPTR_H
#define BASE_AUTOPTR_H


	/** 
	* \ingroup SmartPointer
	Template simulates a "smart" pointer which deletes the item it is
	pointing to when no more references to the item exist.  Warning:
	circular references will produce memory leaks. 

	<P>Note that only one CAutoPtr should be constructed from the original
	ptr -- CAutoPtr will free twice (and cause havoc) if it is misused like so:
	<P>
	<B> WRONG: </B>
	<PRE>
	T* obj = new T();
	CAutoPtr<T> p;
	CAutoPtr<T> q;
	p = obj;
	q = obj;  
	<I>now both p and q think they are the only ones who will free the 
	memory, so you will get an error.</i>
	</PRE>

	*/
#include "mutex.h"

namespace xbase {
template < class T >
class CAutoPtr
{
private:
	mutable  T* ptr;

	mutable int* count;

	mutable CMutex* mutex;

	/// increment the reference count.


    void increment()
    {
        if (ptr)
        {
            if (!count)
            {
                count = new int();
            }
            if (!mutex)
            {
                mutex = new CMutex();
            }
            CAutoLock lock(mutex);
            (*count)++;
        }
    }

    void decrement()
    {
        if (ptr && count)
        {
            bool countIsZero;
            {
                CAutoLock lock(mutex);
                (*count)--;
                countIsZero = (*count == 0);
            }
            if (countIsZero)
            {
                delete ptr;
                delete count;
                delete mutex;
            }
        }
        ptr = 0;
        count = 0;
        mutex = 0;
    };

public:
	/** conversion operator converts pointers of this class to
	* class CAutoPtr< T2 >., where T2 is a different base class.  This
	* is most often used when attempting to call a method of the
	* base class through a derived class pointer.
	*/
	template < class T2 >
		operator CAutoPtr<T2 > () 
	{
		return CAutoPtr < T2 > (ptr, count, mutex);
	}

	/** conversion operator converts pointers of this const class
	* to class const CAutoPtr< T2 >., where T2 is a different base
	* class.  This is most often used when attempting to call a
	* const method of the base class through a derived class
	* pointer.
	*/
	template < class T2 >
		operator const CAutoPtr<T2 > () const
	{
		return CAutoPtr < T2 > (ptr, count, mutex);
	}

	/// default constructor.  points to NULL.

	CAutoPtr() : ptr(0), count(0), mutex(0)
	{
	}
	;

	/** constructor used most often as the constructor from a
	* plain pointer.  Do not use this to convert a single pointer
	* to a smart pointer multiple times -- this will result in an
	* error (see class introduction for details).
	*/

	CAutoPtr(T* original, int* myCount = 0, CMutex* myMutex = 0)
		: ptr(original), count(myCount), mutex(myMutex)
	{
		if (ptr)
		{
			increment();
		}
	};

	/** conversion constructor -- this converts Sptrs of one type to
	*  another, but is ONLY used in working around the missing
	*  template conversion operators in Visual C++.
	*/ 
	template <class T2>
		CAutoPtr(const CAutoPtr<T2>& x)
			: ptr((x.getPtr())), count(x.getCount()), mutex(x.getMutex())
	{
		increment();
	};

	/** copy constructor
	*/

	CAutoPtr(const CAutoPtr& x)
		: ptr(x.getPtr()), count(x.getCount()), mutex(x.getMutex())
	{
		increment();
	};

	/// destructor

	~CAutoPtr()
	{
		{
			decrement();
		}
	}

	/// dereference operator

	T& operator*() const
	{
		return *ptr;
	}

	/// ! operator .  Returns true if ptr == 0, false otherwise.

	int operator!() const
	{
		if (ptr)
		{
			return (ptr == 0);
		}
		else
			return true;
	}

	/// pointer operator.

	T* operator->() const
	{			
		return ptr;
	}

	/** dynamicCast works similarly to the actual dynamic_cast()
	* operator, like so:

	<PRE>
	class A {
	...
	};
	class B : public A {
	...
	};
	class C {
	...
	};
	...
	int main()
	{
	CAutoPtr< A > a;
	CAutoPtr< B > b;
	CAutoPtr< C > c;

	a = new B;

	b.dynamicCast(a);
	// now, b points to the same thing as a

	c.dynamicCast(a);
	// now, c is the NULL pointer.
	}
	</PRE>
	*/

	template < class T2 > 
	CAutoPtr& dynamicCast(const CAutoPtr < T2 > & x)
	{
		if (ptr == x.getPtr()) return *this;
		decrement();
		if(T* p = dynamic_cast < T* > (x.getPtr()))
		{
			count = x.getCount();
			mutex = x.getMutex();
			ptr = p;
			increment();
		}
		return *this;
	}
		

	/** assignment operator -- this is most often used to assign
	* from a smart pointer to a derived type to a smart pointer
	* of the base type.
	*/
	template < class T2 >
		CAutoPtr& operator=(const CAutoPtr < T2 > & x)
	{
		if (ptr == x.getPtr()) return * this;
		decrement();
		ptr = x.getPtr();
		count = x.getCount();
		mutex = x.getMutex();
		increment();
		return *this;
	}


	/** assignment operator from plain pointer.  Do not use this
	* to convert a single pointer to a smart pointer multiple
	* times -- this will result in an error (see class
	* introduction for details).
	*/

	CAutoPtr& operator=(T* original)
	{
		if (ptr == original) return * this;
		decrement();
		ptr = original;
		increment();
		return *this;
	};

	/// assignment operator

	CAutoPtr& operator=(const CAutoPtr& x)
	{
		if (ptr == x.getPtr()) return * this;
		decrement();
		ptr = x.getPtr();
		count = x.getCount();
		mutex = x.getMutex();
		increment();
		return *this;
	}

	/// compare whether a pointer and a smart pointer point to different things

	friend bool operator!=(const void* y, const CAutoPtr& x)
	{
		if (x.getPtr() != y)
			return true;
		else
			return false;
	}

	/// compare whether a smart pointer and a pointer point to different things

	friend bool operator!=(const CAutoPtr& x, const void* y)
	{
		if (x.getPtr() != y)
			return true;
		else
			return false;
	}

	/// compare whether a pointer and a smart pointer point to the same thing

	friend bool operator==(const void* y, const CAutoPtr& x)
	{
		if (x.getPtr() == y)
			return true;
		else
			return false;
	}

	/// compare whether a smart pointer and a pointer point to the same thing

	friend bool operator==(const CAutoPtr& x, const void* y)
	{
		if (x.getPtr() == y)
			return true;
		else
			return false;
	}

	/// compare whether two smart pointers point to the same thing

	bool operator==(const CAutoPtr& x) const
	{
		if (x.getPtr() == ptr)
			return true;
		else
			return false;
	}

	/// compare whether two smart pointers point to different things

	bool operator!=(const CAutoPtr& x) const
	{
		if (x.getPtr() != ptr)
			return true;
		else
			return false;
	}

	/**
	this interface is here because it may sometimes be
	necessary.  DO NOT USE unless you must use it.
	get the actual mutex of the smart pointer.
	*/

	CMutex* getMutex() const
	{
		return mutex;
	}

	/**
	this interface is here because it may sometimes be
	necessary.  DO NOT USE unless you must use it.
	get the value of the reference count of the smart pointer.
	*/

	int* getCount() const
	{
		return count;
	}

	/**
	this interface is here because it may sometimes be
	necessary.  DO NOT USE unless you must use it.
	get the pointer to which the smart pointer points.
	*/

	T* getPtr() const
	{
		return ptr;
	}

};
}
#endif
