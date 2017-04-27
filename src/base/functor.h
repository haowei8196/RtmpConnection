
#ifndef SESSION_FUNCTOR_H
#define SESSION_FUNCTOR_H
#include "event.h"
using namespace session;


class Functor
{
public:
	virtual void operator()() = 0;
	virtual ~Functor() {}
	virtual void Wait() {}	//Shouldn't Call This Function in Functor, Only called in SyncFunctor
	virtual void Signal() {}  //Shouldn't Call This Function in Functor, Only called in SyncFunctor
	virtual bool SyncMode() { return false; }
};

class SyncFunctor : public Functor
{
public:
	SyncFunctor() :_event(0,0){  }
	virtual ~SyncFunctor() {  }
	virtual void Wait() { _event.Wait(CEvent::kForever); }
	virtual void Signal() { _event.Set(); }
	virtual bool SyncMode() { return true; }
private:
	CEvent  _event;
};

// -------------------------------
//
// MemberFunctor[0-5]
//
// -------------------------------
template<class ObjPtr, class ObjFunPtr>
class MemberFunctor0 : public Functor
{
public:
	MemberFunctor0(const ObjPtr& obj, const ObjFunPtr& objfn)
		: _obj(obj), _objfn(objfn)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)();
	}
private:
	ObjPtr    _obj;
	ObjFunPtr _objfn;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1>
	class MemberFunctor1 : public Functor
{
public:
	MemberFunctor1(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1)
		: _obj(obj), _objfn(objfn), _p1(p1)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1);
	}
private:
	ObjPtr    _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2>
	class MemberFunctor2 : public Functor
{
public:
	MemberFunctor2(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2, class Param3>
	class MemberFunctor3 : public Functor
{
public:
	MemberFunctor3(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2, Param3 p3)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2), _p3(p3)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2, _p3);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
	Param3    _p3;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2, class Param3, class Param4>
	class MemberFunctor4 : public Functor
{
public:
	MemberFunctor4(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2, Param3 p3, Param4 p4)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2), _p3(p3), _p4(p4)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2, _p3, _p4);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
	Param3    _p3;
	Param4    _p4;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2, class Param3, class Param4, class Param5>
	class MemberFunctor5 : public Functor
{
public:
	MemberFunctor5(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p5(p5)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2, _p3, _p4, _p5);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
	Param3    _p3;
	Param4    _p4;
	Param5    _p5;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
	class MemberFunctor6 : public Functor
{
public:
	MemberFunctor6(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p5(p5), _p6(p6)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2, _p3, _p4, _p5, _p6);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
	Param3    _p3;
	Param4    _p4;
	Param5    _p5;
	Param6    _p6;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7>
	class MemberFunctor7 : public Functor
{
public:
	MemberFunctor7(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p5(p5), _p6(p6), _p7(p7)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
	Param3    _p3;
	Param4    _p4;
	Param5    _p5;
	Param6    _p6;
	Param7    _p7;
};


// -------------------------------
//
// StaticFunctor[0-5]
//
// -------------------------------
template<class FnPtr>
class StaticFunctor0 : public Functor
{
public:
	StaticFunctor0(const FnPtr& fn)
		: _fn(fn)
	{}

	virtual void operator()()
	{
		_fn();
	}
private:
	FnPtr _fn;
};

template<class FnPtr, class Param1>
class StaticFunctor1 : public Functor
{
public:
	StaticFunctor1(const FnPtr& fn, Param1 p1)
		: _fn(fn), _p1(p1)
	{}

	virtual void operator()()
	{
		_fn(_p1);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
};


template<class FnPtr, class Param1, class Param2>
class StaticFunctor2 : public Functor
{
public:
	StaticFunctor2(const FnPtr& fn, Param1 p1, Param2 p2)
		: _fn(fn), _p1(p1), _p2(p2)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
};

template<class FnPtr, class Param1, class Param2, class Param3>
class StaticFunctor3 : public Functor
{
public:
	StaticFunctor3(const FnPtr& fn, Param1 p1, Param2 p2, Param3 p3)
		: _fn(fn), _p1(p1), _p2(p2), _p3(p3)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2, _p3);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
	Param3 _p3;
};

template<class FnPtr, class Param1, class Param2, class Param3,
	class Param4>
	class StaticFunctor4 : public Functor
{
public:
	StaticFunctor4(const FnPtr& fn, Param1 p1, Param2 p2, Param3 p3,
		Param4 p4)
		: _fn(fn), _p1(p1), _p2(p2), _p3(p3), _p4(p4)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2, _p3, _p4);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
	Param3 _p3;
	Param4 _p4;
};

template<class FnPtr, class Param1, class Param2, class Param3,
	class Param4, class Param5>
	class StaticFunctor5 : public Functor
{
public:
	StaticFunctor5(const FnPtr& fn, Param1 p1, Param2 p2, Param3 p3,
		Param4 p4, Param5 p5)
		: _fn(fn), _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p5(p5)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2, _p3, _p4, _p5);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
	Param3 _p3;
	Param4 _p4;
	Param5 _p5;
};

template<class FnPtr, class Param1, class Param2, class Param3,
	class Param4, class Param5, class Param6>
	class StaticFunctor6 : public Functor
{
public:
	StaticFunctor6(const FnPtr& fn, Param1 p1, Param2 p2, Param3 p3,
		Param4 p4, Param5 p5, Param6 p6)
		: _fn(fn), _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p5(p5), _p6(p6)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2, _p3, _p4, _p5, _p6);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
	Param3 _p3;
	Param4 _p4;
	Param5 _p5;
	Param6 _p6;
};


template<class FnPtr, class Param1, class Param2, class Param3,
	class Param4, class Param5, class Param6, class Param7>
	class StaticFunctor7 : public Functor
{
public:
	StaticFunctor7(const FnPtr& fn, Param1 p1, Param2 p2, Param3 p3,
		Param4 p4, Param5 p5, Param6 p6, Param7 p7)
		: _fn(fn), _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p5(p5), _p6(p6), _p7(p7)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
	Param3 _p3;
	Param4 _p4;
	Param5 _p5;
	Param6 _p6;
	Param7 _p7;
};

// -------------------------------
//
// Wrap -- static functions/methods
//
// -------------------------------
template<class FunRet>
inline Functor* wrap(FunRet(*fn)())
{
	return new StaticFunctor0
		<FunRet(*)()>
		(fn);
}

template<class FunRet,
	class Type1, class Param1>
	inline Functor* wrap(FunRet(*fn)(Type1),
		const Param1& p1)
{
	return new StaticFunctor1
		<FunRet(*)(Type1), Param1>
		(fn, p1);
}


template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2>
	inline Functor* wrap(FunRet(*fn)(Type1, Type2),
		const Param1& p1, const Param2& p2)
{
	return new StaticFunctor2
		<FunRet(*)(Type1, Type2), Param1, Param2>
		(fn, p1, p2);
}


template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3>
	inline Functor* wrap(FunRet(*fn)(Type1, Type2, Type3),
		const Param1& p1, const Param2& p2,
		const Param3& p3)
{
	return new StaticFunctor3
		<FunRet(*)(Type1, Type2, Type3), Param1, Param2, Param3>
		(fn, p1, p2, p3);
}



template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4>
	inline Functor* wrap(FunRet(*fn)(Type1, Type2, Type3, Type4),
		const Param1& p1, const Param2& p2,
		const Param3& p3, const Param4& p4)
{
	return new StaticFunctor4
		<FunRet(*)(Type1, Type2, Type3, Type4),
		Param1, Param2, Param3, Param4>
		(fn, p1, p2, p3, p4);
}


template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5>
	inline Functor* wrap(FunRet(*fn)(Type1, Type2, Type3, Type4, Type5),
		const Param1& p1, const Param2& p2,
		const Param3& p3, const Param4& p4,
		const Param5& p5)
{
	return new StaticFunctor5
		<FunRet(*)(Type1, Type2, Type3, Type4, Type5),
		Param1, Param2, Param3, Param4, Param5>
		(fn, p1, p2, p3, p4, p5);
}


template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5,
	class Type6, class Param6>
	inline Functor* wrap(FunRet(*fn)(Type1, Type2, Type3, Type4, Type5, Type6),
		const Param1& p1, const Param2& p2,
		const Param3& p3, const Param4& p4,
		const Param5& p5, const Param6& p6)
{
	return new StaticFunctor6
		<FunRet(*)(Type1, Type2, Type3, Type4, Type5, Type6),
		Param1, Param2, Param3, Param4, Param5, Param6>
		(fn, p1, p2, p3, p4, p5, p6);
}



template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5,
	class Type6, class Param6,
	class Type7, class Param7>
	inline Functor* wrap(FunRet(*fn)(Type1, Type2, Type3, Type4, Type5, Type6, Type7),
		const Param1& p1, const Param2& p2,
		const Param3& p3, const Param4& p4,
		const Param5& p5, const Param6& p6,
		const Param7& p7)
{
	return new StaticFunctor7
		<FunRet(*)(Type1, Type2, Type3, Type4, Type5, Type6, Type7),
		Param1, Param2, Param3, Param4, Param5, Param6, Param7>
		(fn, p1, p2, p3, p4, p5, p6, p7);
}



// -------------------------------
//
// Wrap -- non-const, methods
//
// -------------------------------
template<class ObjPtr, class Obj, class ObjFunRet>
inline Functor* wrap(const ObjPtr& objptr, ObjFunRet(Obj::*objfn)())
{
	return new MemberFunctor0<ObjPtr, ObjFunRet(Obj::*)()>(objptr, objfn);
}

template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1>
	inline Functor* wrap(const ObjPtr& objptr, ObjFunRet(Obj::*objfn)(Type1),
		const Param1& p1)
{
	return new MemberFunctor1
		<ObjPtr, ObjFunRet(Obj::*)(Type1),
		Param1>
		(objptr, objfn, p1);
}


template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2>
	inline Functor* wrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2),
		const Param1& p1, const Param2& p2)
{
	return new MemberFunctor2
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2),
		Param1, Param2>
		(objptr, objfn, p1, p2);
}


template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3>
	inline Functor* wrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3)
{
	return new MemberFunctor3
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3),
		Param1, Param2, Param3>
		(objptr, objfn, p1, p2, p3);
}

template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4>
	inline Functor* wrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3, Type4),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4)
{
	return new MemberFunctor4
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3, Type4),
		Param1, Param2, Param3, Param4>
		(objptr, objfn, p1, p2, p3, p4);
}


template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5>
	inline Functor* wrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3, Type4, Type5),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4,
		const Param5& p5)
{
	return new MemberFunctor5
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3, Type4, Type5),
		Param1, Param2, Param3, Param4, Param5>
		(objptr, objfn, p1, p2, p3, p4, p5);
}

template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5,
	class Type6, class Param6>
	inline Functor* wrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3, Type4, Type5, Type6),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4,
		const Param5& p5,
		const Param6& p6)
{
	return new MemberFunctor6
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3, Type4, Type5, Type6),
		Param1, Param2, Param3, Param4, Param5, Param6>
		(objptr, objfn, p1, p2, p3, p4, p5, p6);
}

// -------------------------------
//
// Wrap -- const, methods
//
// -------------------------------
template<class ObjPtr, class Obj, class ObjFunRet>
inline Functor* wrap(const ObjPtr& objptr, ObjFunRet(Obj::*objfn)() const)
{
	return new MemberFunctor0<ObjPtr, ObjFunRet(Obj::*)() const >(objptr, objfn);
}



template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1>
	inline Functor* wrap(const ObjPtr& objptr, ObjFunRet(Obj::*objfn)(Type1) const,
		const Param1& p1)
{
	return new MemberFunctor1
		<ObjPtr, ObjFunRet(Obj::*)(Type1) const, Param1>
		(objptr, objfn, p1);
}



template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2>
	inline Functor* wrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2) const,
		const Param1& p1, const Param2& p2)
{
	return new MemberFunctor2
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2) const, Param1, Param2>
		(objptr, objfn, p1, p2);
}



template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3>
	inline Functor* wrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3) const,
		const Param1& p1,
		const Param2& p2,
		const Param3& p3)
{
	return new MemberFunctor3
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3) const,
		Param1, Param2, Param3>
		(objptr, objfn, p1, p2, p3);
}


template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4>
	inline Functor* wrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3, Type4) const,
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4)
{
	return new MemberFunctor4
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3, Type4) const,
		Param1, Param2, Param3, Param4>
		(objptr, objfn, p1, p2, p3, p4);
}



template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5>
	inline Functor* wrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3, Type4, Type5) const,
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4,
		const Param5& p5)
{
	return new MemberFunctor5
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3, Type4, Type5) const,
		Param1, Param2, Param3, Param4, Param5>
		(objptr, objfn, p1, p2, p3, p4, p5);
}

//////////////////////////////////////////////////////////////////////////
// Chris add 2004/4/22 For Functor Sync Call usage.

// -------------------------------
//
// SyncMemberSyncFunctor[0-5]
//
// -------------------------------
template<class ObjPtr, class ObjFunPtr>
class SyncMemberSyncFunctor0 : public SyncFunctor
{
public:
	SyncMemberSyncFunctor0(const ObjPtr& obj, const ObjFunPtr& objfn)
		: _obj(obj), _objfn(objfn)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)();
	}
private:
	ObjPtr    _obj;
	ObjFunPtr _objfn;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1>
	class SyncMemberSyncFunctor1 : public SyncFunctor
{
public:
	SyncMemberSyncFunctor1(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1)
		: _obj(obj), _objfn(objfn), _p1(p1)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1);
	}
private:
	ObjPtr    _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2>
	class SyncMemberSyncFunctor2 : public SyncFunctor
{
public:
	SyncMemberSyncFunctor2(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2, class Param3>
	class SyncMemberSyncFunctor3 : public SyncFunctor
{
public:
	SyncMemberSyncFunctor3(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2, Param3 p3)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2), _p3(p3)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2, _p3);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
	Param3    _p3;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2, class Param3, class Param4>
	class SyncMemberSyncFunctor4 : public SyncFunctor
{
public:
	SyncMemberSyncFunctor4(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2, Param3 p3, Param4 p4)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2), _p3(p3), _p4(p4)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2, _p3, _p4);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
	Param3    _p3;
	Param4    _p4;
};

template<class ObjPtr, class ObjFunPtr,
	class Param1, class Param2, class Param3, class Param4, class Param5>
	class SyncMemberSyncFunctor5 : public SyncFunctor
{
public:
	SyncMemberSyncFunctor5(const ObjPtr& obj, const ObjFunPtr& objfn,
		Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)
		: _obj(obj), _objfn(objfn), _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p5(p5)
	{}

	virtual void operator()()
	{
		((*_obj).*_objfn)(_p1, _p2, _p3, _p4, _p5);
	}
private:
	ObjPtr _obj;
	ObjFunPtr _objfn;
	Param1    _p1;
	Param2    _p2;
	Param3    _p3;
	Param4    _p4;
	Param5    _p5;
};


// -------------------------------
//
// SyncStaticSyncFunctor[0-5]
//
// -------------------------------
template<class FnPtr>
class SyncStaticSyncFunctor0 : public SyncFunctor
{
public:
	SyncStaticSyncFunctor0(const FnPtr& fn)
		: _fn(fn)
	{}

	virtual void operator()()
	{
		_fn();
	}
private:
	FnPtr _fn;
};

template<class FnPtr, class Param1>
class SyncStaticSyncFunctor1 : public SyncFunctor
{
public:
	SyncStaticSyncFunctor1(const FnPtr& fn, Param1 p1)
		: _fn(fn), _p1(p1)
	{}

	virtual void operator()()
	{
		_fn(_p1);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
};


template<class FnPtr, class Param1, class Param2>
class SyncStaticSyncFunctor2 : public SyncFunctor
{
public:
	SyncStaticSyncFunctor2(const FnPtr& fn, Param1 p1, Param2 p2)
		: _fn(fn), _p1(p1), _p2(p2)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
};

template<class FnPtr, class Param1, class Param2, class Param3>
class SyncStaticSyncFunctor3 : public SyncFunctor
{
public:
	SyncStaticSyncFunctor3(const FnPtr& fn, Param1 p1, Param2 p2, Param3 p3)
		: _fn(fn), _p1(p1), _p2(p2), _p3(p3)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2, _p3);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
	Param3 _p3;
};

template<class FnPtr, class Param1, class Param2, class Param3,
	class Param4>
	class SyncStaticSyncFunctor4 : public SyncFunctor
{
public:
	SyncStaticSyncFunctor4(const FnPtr& fn, Param1 p1, Param2 p2, Param3 p3,
		Param4 p4)
		: _fn(fn), _p1(p1), _p2(p2), _p3(p3), _p4(p4)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2, _p3, _p4);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
	Param3 _p3;
	Param4 _p4;
};

template<class FnPtr, class Param1, class Param2, class Param3,
	class Param4, class Param5>
	class SyncStaticSyncFunctor5 : public SyncFunctor
{
public:
	SyncStaticSyncFunctor5(const FnPtr& fn, Param1 p1, Param2 p2, Param3 p3,
		Param4 p4, Param5 p5)
		: _fn(fn), _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p5(p5)
	{}

	virtual void operator()()
	{
		_fn(_p1, _p2, _p3, _p4, _p5);
	}
private:
	FnPtr  _fn;
	Param1 _p1;
	Param2 _p2;
	Param3 _p3;
	Param4 _p4;
	Param5 _p5;
};


// -------------------------------
//
// syncwrap -- static functions/methods
//
// -------------------------------
template<class FunRet>
inline SyncFunctor* syncwrap(FunRet(*fn)())
{
	return new SyncStaticSyncFunctor0
		<FunRet(*)()>
		(fn);
}



template<class FunRet,
	class Type1, class Param1>
	inline SyncFunctor* syncwrap(FunRet(*fn)(Type1),
		const Param1& p1)
{
	return new SyncStaticSyncFunctor1
		<FunRet(*)(Type1), Param1>
		(fn, p1);
}



template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2>
	inline SyncFunctor* syncwrap(FunRet(*fn)(Type1, Type2),
		const Param1& p1, const Param2& p2)
{
	return new SyncStaticSyncFunctor2
		<FunRet(*)(Type1, Type2), Param1, Param2>
		(fn, p1, p2);
}



template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3>
	inline SyncFunctor* syncwrap(FunRet(*fn)(Type1, Type2, Type3),
		const Param1& p1, const Param2& p2,
		const Param3& p3)
{
	return new SyncStaticSyncFunctor3
		<FunRet(*)(Type1, Type2, Type3), Param1, Param2, Param3>
		(fn, p1, p2, p3);
}


template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4>
	inline SyncFunctor* syncwrap(FunRet(*fn)(Type1, Type2, Type3, Type4),
		const Param1& p1, const Param2& p2,
		const Param3& p3, const Param4& p4)
{
	return new SyncStaticSyncFunctor4
		<FunRet(*)(Type1, Type2, Type3, Type4),
		Param1, Param2, Param3, Param4>
		(fn, p1, p2, p3, p4);
}



template<class FunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5>
	inline SyncFunctor* syncwrap(FunRet(*fn)(Type1, Type2, Type3, Type4, Type5),
		const Param1& p1, const Param2& p2,
		const Param3& p3, const Param4& p4,
		const Param5& p5)
{
	return new SyncStaticSyncFunctor5
		<FunRet(*)(Type1, Type2, Type3, Type4, Type5),
		Param1, Param2, Param3, Param4, Param5>
		(fn, p1, p2, p3, p4, p5);
}


// -------------------------------
//
// syncwrap -- non-const, methods
//
// -------------------------------
template<class ObjPtr, class Obj, class ObjFunRet>
inline SyncFunctor* syncwrap(const ObjPtr& objptr, ObjFunRet(Obj::*objfn)())
{
	return new SyncMemberSyncFunctor0<ObjPtr, ObjFunRet(Obj::*)()>(objptr, objfn);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet>
inline SyncFunctor* syncwrap(const ObjPtr& objptr, ObjFunRet(SESSIONAPI Obj::*objfn)())
{
	return new SyncMemberSyncFunctor0<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)()>(objptr, objfn);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr, ObjFunRet(Obj::*objfn)(Type1),
		const Param1& p1)
{
	return new SyncMemberSyncFunctor1
		<ObjPtr, ObjFunRet(Obj::*)(Type1),
		Param1>
		(objptr, objfn, p1);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr, ObjFunRet(SESSIONAPI Obj::*objfn)(Type1),
		const Param1& p1)
{
	return new SyncMemberSyncFunctor1
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1),
		Param1>
		(objptr, objfn, p1);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2),
		const Param1& p1, const Param2& p2)
{
	return new SyncMemberSyncFunctor2
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2),
		Param1, Param2>
		(objptr, objfn, p1, p2);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(SESSIONAPI Obj::*objfn)(Type1, Type2),
		const Param1& p1, const Param2& p2)
{
	return new SyncMemberSyncFunctor2
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1, Type2),
		Param1, Param2>
		(objptr, objfn, p1, p2);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3)
{
	return new SyncMemberSyncFunctor3
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3),
		Param1, Param2, Param3>
		(objptr, objfn, p1, p2, p3);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(SESSIONAPI Obj::*objfn)(Type1, Type2, Type3),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3)
{
	return new SyncMemberSyncFunctor3
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1, Type2, Type3),
		Param1, Param2, Param3>
		(objptr, objfn, p1, p2, p3);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3, Type4),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4)
{
	return new SyncMemberSyncFunctor4
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3, Type4),
		Param1, Param2, Param3, Param4>
		(objptr, objfn, p1, p2, p3, p4);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(SESSIONAPI Obj::*objfn)(Type1, Type2, Type3, Type4),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4)
{
	return new SyncMemberSyncFunctor4
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1, Type2, Type3, Type4),
		Param1, Param2, Param3, Param4>
		(objptr, objfn, p1, p2, p3, p4);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3, Type4, Type5),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4,
		const Param5& p5)
{
	return new SyncMemberSyncFunctor5
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3, Type4, Type5),
		Param1, Param2, Param3, Param4, Param5>
		(objptr, objfn, p1, p2, p3, p4, p5);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(SESSIONAPI Obj::*objfn)(Type1, Type2, Type3, Type4, Type5),
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4,
		const Param5& p5)
{
	return new SyncMemberSyncFunctor5
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1, Type2, Type3, Type4, Type5),
		Param1, Param2, Param3, Param4, Param5>
		(objptr, objfn, p1, p2, p3, p4, p5);
}
#endif
// -------------------------------
//
// syncwrap -- const, methods
//
// -------------------------------
template<class ObjPtr, class Obj, class ObjFunRet>
inline SyncFunctor* syncwrap(const ObjPtr& objptr, ObjFunRet(Obj::*objfn)() const)
{
	return new SyncMemberSyncFunctor0<ObjPtr, ObjFunRet(Obj::*)() const >(objptr, objfn);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet>
inline SyncFunctor* syncwrap(const ObjPtr& objptr, ObjFunRet(SESSIONAPI Obj::*objfn)() const)
{
	return new SyncMemberSyncFunctor0<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)() const >(objptr, objfn);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr, ObjFunRet(Obj::*objfn)(Type1) const,
		const Param1& p1)
{
	return new SyncMemberSyncFunctor1
		<ObjPtr, ObjFunRet(Obj::*)(Type1) const, Param1>
		(objptr, objfn, p1);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr, ObjFunRet(SESSIONAPI Obj::*objfn)(Type1) const,
		const Param1& p1)
{
	return new SyncMemberSyncFunctor1
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1) const, Param1>
		(objptr, objfn, p1);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2) const,
		const Param1& p1, const Param2& p2)
{
	return new SyncMemberSyncFunctor2
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2) const, Param1, Param2>
		(objptr, objfn, p1, p2);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(SESSIONAPI Obj::*objfn)(Type1, Type2) const,
		const Param1& p1, const Param2& p2)
{
	return new SyncMemberSyncFunctor2
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1, Type2) const, Param1, Param2>
		(objptr, objfn, p1, p2);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3) const,
		const Param1& p1,
		const Param2& p2,
		const Param3& p3)
{
	return new SyncMemberSyncFunctor3
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3) const,
		Param1, Param2, Param3>
		(objptr, objfn, p1, p2, p3);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(SESSIONAPI Obj::*objfn)(Type1, Type2, Type3) const,
		const Param1& p1,
		const Param2& p2,
		const Param3& p3)
{
	return new SyncMemberSyncFunctor3
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1, Type2, Type3) const,
		Param1, Param2, Param3>
		(objptr, objfn, p1, p2, p3);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3, Type4) const,
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4)
{
	return new SyncMemberSyncFunctor4
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3, Type4) const,
		Param1, Param2, Param3, Param4>
		(objptr, objfn, p1, p2, p3, p4);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(SESSIONAPI Obj::*objfn)(Type1, Type2, Type3, Type4) const,
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4)
{
	return new SyncMemberSyncFunctor4
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1, Type2, Type3, Type4) const,
		Param1, Param2, Param3, Param4>
		(objptr, objfn, p1, p2, p3, p4);
}
#endif
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(Obj::*objfn)(Type1, Type2, Type3, Type4, Type5) const,
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4,
		const Param5& p5)
{
	return new SyncMemberSyncFunctor5
		<ObjPtr, ObjFunRet(Obj::*)(Type1, Type2, Type3, Type4, Type5) const,
		Param1, Param2, Param3, Param4, Param5>
		(objptr, objfn, p1, p2, p3, p4, p5);
}
#ifdef SESSIONAPI
template<class ObjPtr, class Obj, class ObjFunRet,
	class Type1, class Param1,
	class Type2, class Param2,
	class Type3, class Param3,
	class Type4, class Param4,
	class Type5, class Param5>
	inline SyncFunctor* syncwrap(const ObjPtr& objptr,
		ObjFunRet(SESSIONAPI Obj::*objfn)(Type1, Type2, Type3, Type4, Type5) const,
		const Param1& p1,
		const Param2& p2,
		const Param3& p3,
		const Param4& p4,
		const Param5& p5)
{
	return new SyncMemberSyncFunctor5
		<ObjPtr, ObjFunRet(SESSIONAPI Obj::*)(Type1, Type2, Type3, Type4, Type5) const,
		Param1, Param2, Param3, Param4, Param5>
		(objptr, objfn, p1, p2, p3, p4, p5);
}
#endif
#endif
