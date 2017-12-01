// **********************************************************************
//
// Copyright (c) 2003-2017 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.6.4
//
// <auto-generated>
//
// Generated from file `processfile.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <processfile.h>
#include <IceUtil/PushDisableWarnings.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/Outgoing.h>
#include <Ice/OutgoingAsync.h>
#include <Ice/BasicStream.h>
#include <IceUtil/Iterator.h>
#include <IceUtil/PopDisableWarnings.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 306
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 4
#       error Ice patch level mismatch!
#   endif
#endif

namespace
{

const ::std::string __ProcessFile__ProcessFileManager__requestFile_name = "requestFile";

const ::std::string __ProcessFile__ProcessFileManager__sendFile_name = "sendFile";

}

namespace Ice
{
}
::IceProxy::Ice::Object* ::IceProxy::ProcessFile::upCast(::IceProxy::ProcessFile::ProcessFileManager* p) { return p; }

void
::IceProxy::ProcessFile::__read(::IceInternal::BasicStream* __is, ::IceInternal::ProxyHandle< ::IceProxy::ProcessFile::ProcessFileManager>& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::ProcessFile::ProcessFileManager;
        v->__copyFrom(proxy);
    }
}

::ProcessFile::FileContent
IceProxy::ProcessFile::ProcessFileManager::requestFile(const ::std::string& __p_title, ::Ice::Long __p_pos, const ::Ice::Context* __ctx)
{
    __checkTwowayOnly(__ProcessFile__ProcessFileManager__requestFile_name);
    ::IceInternal::Outgoing __og(this, __ProcessFile__ProcessFileManager__requestFile_name, ::Ice::Normal, __ctx);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_title);
        __os->write(__p_pos);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    if(!__og.invoke())
    {
        try
        {
            __og.throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
            throw __uue;
        }
    }
    ::ProcessFile::FileContent __ret;
    ::IceInternal::BasicStream* __is = __og.startReadParams();
    __is->read(__ret);
    __og.endReadParams();
    return __ret;
}

::Ice::AsyncResultPtr
IceProxy::ProcessFile::ProcessFileManager::begin_requestFile(const ::std::string& __p_title, ::Ice::Long __p_pos, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__ProcessFile__ProcessFileManager__requestFile_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __ProcessFile__ProcessFileManager__requestFile_name, __del, __cookie);
    try
    {
        __result->prepare(__ProcessFile__ProcessFileManager__requestFile_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_title);
        __os->write(__p_pos);
        __result->endWriteParams();
        __result->invoke();
    }
    catch(const ::Ice::Exception& __ex)
    {
        __result->abort(__ex);
    }
    return __result;
}

#ifdef ICE_CPP11

::Ice::AsyncResultPtr
IceProxy::ProcessFile::ProcessFileManager::__begin_requestFile(const ::std::string& __p_title, ::Ice::Long __p_pos, const ::Ice::Context* __ctx, const ::IceInternal::Function<void (const ::ProcessFile::FileContent&)>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception, const ::IceInternal::Function<void (bool)>& __sent)
{
    class Cpp11CB : public ::IceInternal::Cpp11FnCallbackNC
    {
    public:

        Cpp11CB(const ::std::function<void (const ::ProcessFile::FileContent&)>& responseFunc, const ::std::function<void (const ::Ice::Exception&)>& exceptionFunc, const ::std::function<void (bool)>& sentFunc) :
            ::IceInternal::Cpp11FnCallbackNC(exceptionFunc, sentFunc),
            _response(responseFunc)
        {
            CallbackBase::checkCallback(true, responseFunc || exceptionFunc != nullptr);
        }

        virtual void completed(const ::Ice::AsyncResultPtr& __result) const
        {
            ::ProcessFile::ProcessFileManagerPrx __proxy = ::ProcessFile::ProcessFileManagerPrx::uncheckedCast(__result->getProxy());
            ::ProcessFile::FileContent __ret;
            try
            {
                __ret = __proxy->end_requestFile(__result);
            }
            catch(const ::Ice::Exception& ex)
            {
                Cpp11FnCallbackNC::exception(__result, ex);
                return;
            }
            if(_response != nullptr)
            {
                _response(__ret);
            }
        }
    
    private:
        
        ::std::function<void (const ::ProcessFile::FileContent&)> _response;
    };
    return begin_requestFile(__p_title, __p_pos, __ctx, new Cpp11CB(__response, __exception, __sent));
}
#endif

::ProcessFile::FileContent
IceProxy::ProcessFile::ProcessFileManager::end_requestFile(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __ProcessFile__ProcessFileManager__requestFile_name);
    ::ProcessFile::FileContent __ret;
    if(!__result->__wait())
    {
        try
        {
            __result->__throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
        }
    }
    ::IceInternal::BasicStream* __is = __result->__startReadParams();
    __is->read(__ret);
    __result->__endReadParams();
    return __ret;
}

bool
IceProxy::ProcessFile::ProcessFileManager::sendFile(const ::std::string& __p_title, const ::ProcessFile::Bytes& __p_datas, const ::Ice::Context* __ctx)
{
    __checkTwowayOnly(__ProcessFile__ProcessFileManager__sendFile_name);
    ::IceInternal::Outgoing __og(this, __ProcessFile__ProcessFileManager__sendFile_name, ::Ice::Normal, __ctx);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_title);
        __os->write(__p_datas);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    if(!__og.invoke())
    {
        try
        {
            __og.throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
            throw __uue;
        }
    }
    bool __ret;
    ::IceInternal::BasicStream* __is = __og.startReadParams();
    __is->read(__ret);
    __og.endReadParams();
    return __ret;
}

::Ice::AsyncResultPtr
IceProxy::ProcessFile::ProcessFileManager::begin_sendFile(const ::std::string& __p_title, const ::ProcessFile::Bytes& __p_datas, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__ProcessFile__ProcessFileManager__sendFile_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __ProcessFile__ProcessFileManager__sendFile_name, __del, __cookie);
    try
    {
        __result->prepare(__ProcessFile__ProcessFileManager__sendFile_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_title);
        __os->write(__p_datas);
        __result->endWriteParams();
        __result->invoke();
    }
    catch(const ::Ice::Exception& __ex)
    {
        __result->abort(__ex);
    }
    return __result;
}

#ifdef ICE_CPP11

::Ice::AsyncResultPtr
IceProxy::ProcessFile::ProcessFileManager::__begin_sendFile(const ::std::string& __p_title, const ::ProcessFile::Bytes& __p_datas, const ::Ice::Context* __ctx, const ::IceInternal::Function<void (bool)>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception, const ::IceInternal::Function<void (bool)>& __sent)
{
    class Cpp11CB : public ::IceInternal::Cpp11FnCallbackNC
    {
    public:

        Cpp11CB(const ::std::function<void (bool)>& responseFunc, const ::std::function<void (const ::Ice::Exception&)>& exceptionFunc, const ::std::function<void (bool)>& sentFunc) :
            ::IceInternal::Cpp11FnCallbackNC(exceptionFunc, sentFunc),
            _response(responseFunc)
        {
            CallbackBase::checkCallback(true, responseFunc || exceptionFunc != nullptr);
        }

        virtual void completed(const ::Ice::AsyncResultPtr& __result) const
        {
            ::ProcessFile::ProcessFileManagerPrx __proxy = ::ProcessFile::ProcessFileManagerPrx::uncheckedCast(__result->getProxy());
            bool __ret;
            try
            {
                __ret = __proxy->end_sendFile(__result);
            }
            catch(const ::Ice::Exception& ex)
            {
                Cpp11FnCallbackNC::exception(__result, ex);
                return;
            }
            if(_response != nullptr)
            {
                _response(__ret);
            }
        }
    
    private:
        
        ::std::function<void (bool)> _response;
    };
    return begin_sendFile(__p_title, __p_datas, __ctx, new Cpp11CB(__response, __exception, __sent));
}
#endif

bool
IceProxy::ProcessFile::ProcessFileManager::end_sendFile(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __ProcessFile__ProcessFileManager__sendFile_name);
    bool __ret;
    if(!__result->__wait())
    {
        try
        {
            __result->__throwUserException();
        }
        catch(const ::Ice::UserException& __ex)
        {
            throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
        }
    }
    ::IceInternal::BasicStream* __is = __result->__startReadParams();
    __is->read(__ret);
    __result->__endReadParams();
    return __ret;
}

const ::std::string&
IceProxy::ProcessFile::ProcessFileManager::ice_staticId()
{
    return ::ProcessFile::ProcessFileManager::ice_staticId();
}

::IceProxy::Ice::Object*
IceProxy::ProcessFile::ProcessFileManager::__newInstance() const
{
    return new ProcessFileManager;
}

::Ice::Object* ProcessFile::upCast(::ProcessFile::ProcessFileManager* p) { return p; }

namespace
{
const ::std::string __ProcessFile__ProcessFileManager_ids[2] =
{
    "::Ice::Object",
    "::ProcessFile::ProcessFileManager"
};

}

bool
ProcessFile::ProcessFileManager::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__ProcessFile__ProcessFileManager_ids, __ProcessFile__ProcessFileManager_ids + 2, _s);
}

::std::vector< ::std::string>
ProcessFile::ProcessFileManager::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__ProcessFile__ProcessFileManager_ids[0], &__ProcessFile__ProcessFileManager_ids[2]);
}

const ::std::string&
ProcessFile::ProcessFileManager::ice_id(const ::Ice::Current&) const
{
    return __ProcessFile__ProcessFileManager_ids[1];
}

const ::std::string&
ProcessFile::ProcessFileManager::ice_staticId()
{
#ifdef ICE_HAS_THREAD_SAFE_LOCAL_STATIC
    static const ::std::string typeId = "::ProcessFile::ProcessFileManager";
    return typeId;
#else
    return __ProcessFile__ProcessFileManager_ids[1];
#endif
}

::Ice::DispatchStatus
ProcessFile::ProcessFileManager::___requestFile(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::std::string __p_title;
    ::Ice::Long __p_pos;
    __is->read(__p_title);
    __is->read(__p_pos);
    __inS.endReadParams();
    ::ProcessFile::FileContent __ret = requestFile(__p_title, __p_pos, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
ProcessFile::ProcessFileManager::___sendFile(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::std::string __p_title;
    ::ProcessFile::Bytes __p_datas;
    __is->read(__p_title);
    __is->read(__p_datas);
    __inS.endReadParams();
    bool __ret = sendFile(__p_title, __p_datas, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

namespace
{
const ::std::string __ProcessFile__ProcessFileManager_all[] =
{
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "requestFile",
    "sendFile"
};

}

::Ice::DispatchStatus
ProcessFile::ProcessFileManager::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__ProcessFile__ProcessFileManager_all, __ProcessFile__ProcessFileManager_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __ProcessFile__ProcessFileManager_all)
    {
        case 0:
        {
            return ___ice_id(in, current);
        }
        case 1:
        {
            return ___ice_ids(in, current);
        }
        case 2:
        {
            return ___ice_isA(in, current);
        }
        case 3:
        {
            return ___ice_ping(in, current);
        }
        case 4:
        {
            return ___requestFile(in, current);
        }
        case 5:
        {
            return ___sendFile(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
ProcessFile::ProcessFileManager::__writeImpl(::IceInternal::BasicStream* __os) const
{
    __os->startWriteSlice(ice_staticId(), -1, true);
    __os->endWriteSlice();
}

void
ProcessFile::ProcessFileManager::__readImpl(::IceInternal::BasicStream* __is)
{
    __is->startReadSlice();
    __is->endReadSlice();
}

void 
ProcessFile::__patch(ProcessFileManagerPtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::ProcessFile::ProcessFileManagerPtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::ProcessFile::ProcessFileManager::ice_staticId(), v);
    }
}
