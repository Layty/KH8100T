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
// Generated from file `transferfile.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <transferfile.h>
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

const ::std::string __TransferFileModule__TransferFileManager__uploadFile_name = "uploadFile";

const ::std::string __TransferFileModule__TransferFileManager__downloadFile_name = "downloadFile";

}

namespace Ice
{
}
::IceProxy::Ice::Object* ::IceProxy::TransferFileModule::upCast(::IceProxy::TransferFileModule::TransferFileManager* p) { return p; }

void
::IceProxy::TransferFileModule::__read(::IceInternal::BasicStream* __is, ::IceInternal::ProxyHandle< ::IceProxy::TransferFileModule::TransferFileManager>& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::TransferFileModule::TransferFileManager;
        v->__copyFrom(proxy);
    }
}

void
IceProxy::TransferFileModule::TransferFileManager::uploadFile(const ::std::string& __p_title, const ::TransferFileModule::Bytes& __p_content, const ::Ice::Context* __ctx)
{
    ::IceInternal::Outgoing __og(this, __TransferFileModule__TransferFileManager__uploadFile_name, ::Ice::Normal, __ctx);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_title);
        __os->write(__p_content);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    __invoke(__og);
}

::Ice::AsyncResultPtr
IceProxy::TransferFileModule::TransferFileManager::begin_uploadFile(const ::std::string& __p_title, const ::TransferFileModule::Bytes& __p_content, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __TransferFileModule__TransferFileManager__uploadFile_name, __del, __cookie);
    try
    {
        __result->prepare(__TransferFileModule__TransferFileManager__uploadFile_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->startWriteParams(::Ice::DefaultFormat);
        __os->write(__p_title);
        __os->write(__p_content);
        __result->endWriteParams();
        __result->invoke();
    }
    catch(const ::Ice::Exception& __ex)
    {
        __result->abort(__ex);
    }
    return __result;
}

void
IceProxy::TransferFileModule::TransferFileManager::end_uploadFile(const ::Ice::AsyncResultPtr& __result)
{
    __end(__result, __TransferFileModule__TransferFileManager__uploadFile_name);
}

::TransferFileModule::FileContent
IceProxy::TransferFileModule::TransferFileManager::downloadFile(const ::std::string& __p_title, ::Ice::Long __p_pos, const ::Ice::Context* __ctx)
{
    __checkTwowayOnly(__TransferFileModule__TransferFileManager__downloadFile_name);
    ::IceInternal::Outgoing __og(this, __TransferFileModule__TransferFileManager__downloadFile_name, ::Ice::Normal, __ctx);
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
    ::TransferFileModule::FileContent __ret;
    ::IceInternal::BasicStream* __is = __og.startReadParams();
    __is->read(__ret);
    __og.endReadParams();
    return __ret;
}

::Ice::AsyncResultPtr
IceProxy::TransferFileModule::TransferFileManager::begin_downloadFile(const ::std::string& __p_title, ::Ice::Long __p_pos, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__TransferFileModule__TransferFileManager__downloadFile_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __TransferFileModule__TransferFileManager__downloadFile_name, __del, __cookie);
    try
    {
        __result->prepare(__TransferFileModule__TransferFileManager__downloadFile_name, ::Ice::Normal, __ctx);
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
IceProxy::TransferFileModule::TransferFileManager::__begin_downloadFile(const ::std::string& __p_title, ::Ice::Long __p_pos, const ::Ice::Context* __ctx, const ::IceInternal::Function<void (const ::TransferFileModule::FileContent&)>& __response, const ::IceInternal::Function<void (const ::Ice::Exception&)>& __exception, const ::IceInternal::Function<void (bool)>& __sent)
{
    class Cpp11CB : public ::IceInternal::Cpp11FnCallbackNC
    {
    public:

        Cpp11CB(const ::std::function<void (const ::TransferFileModule::FileContent&)>& responseFunc, const ::std::function<void (const ::Ice::Exception&)>& exceptionFunc, const ::std::function<void (bool)>& sentFunc) :
            ::IceInternal::Cpp11FnCallbackNC(exceptionFunc, sentFunc),
            _response(responseFunc)
        {
            CallbackBase::checkCallback(true, responseFunc || exceptionFunc != nullptr);
        }

        virtual void completed(const ::Ice::AsyncResultPtr& __result) const
        {
            ::TransferFileModule::TransferFileManagerPrx __proxy = ::TransferFileModule::TransferFileManagerPrx::uncheckedCast(__result->getProxy());
            ::TransferFileModule::FileContent __ret;
            try
            {
                __ret = __proxy->end_downloadFile(__result);
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
        
        ::std::function<void (const ::TransferFileModule::FileContent&)> _response;
    };
    return begin_downloadFile(__p_title, __p_pos, __ctx, new Cpp11CB(__response, __exception, __sent));
}
#endif

::TransferFileModule::FileContent
IceProxy::TransferFileModule::TransferFileManager::end_downloadFile(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __TransferFileModule__TransferFileManager__downloadFile_name);
    ::TransferFileModule::FileContent __ret;
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
IceProxy::TransferFileModule::TransferFileManager::ice_staticId()
{
    return ::TransferFileModule::TransferFileManager::ice_staticId();
}

::IceProxy::Ice::Object*
IceProxy::TransferFileModule::TransferFileManager::__newInstance() const
{
    return new TransferFileManager;
}

::Ice::Object* TransferFileModule::upCast(::TransferFileModule::TransferFileManager* p) { return p; }

namespace
{
const ::std::string __TransferFileModule__TransferFileManager_ids[2] =
{
    "::Ice::Object",
    "::TransferFileModule::TransferFileManager"
};

}

bool
TransferFileModule::TransferFileManager::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__TransferFileModule__TransferFileManager_ids, __TransferFileModule__TransferFileManager_ids + 2, _s);
}

::std::vector< ::std::string>
TransferFileModule::TransferFileManager::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__TransferFileModule__TransferFileManager_ids[0], &__TransferFileModule__TransferFileManager_ids[2]);
}

const ::std::string&
TransferFileModule::TransferFileManager::ice_id(const ::Ice::Current&) const
{
    return __TransferFileModule__TransferFileManager_ids[1];
}

const ::std::string&
TransferFileModule::TransferFileManager::ice_staticId()
{
#ifdef ICE_HAS_THREAD_SAFE_LOCAL_STATIC
    static const ::std::string typeId = "::TransferFileModule::TransferFileManager";
    return typeId;
#else
    return __TransferFileModule__TransferFileManager_ids[1];
#endif
}

::Ice::DispatchStatus
TransferFileModule::TransferFileManager::___uploadFile(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::std::string __p_title;
    ::TransferFileModule::Bytes __p_content;
    __is->read(__p_title);
    __is->read(__p_content);
    __inS.endReadParams();
    uploadFile(__p_title, __p_content, __current);
    __inS.__writeEmptyParams();
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
TransferFileModule::TransferFileManager::___downloadFile(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::std::string __p_title;
    ::Ice::Long __p_pos;
    __is->read(__p_title);
    __is->read(__p_pos);
    __inS.endReadParams();
    ::TransferFileModule::FileContent __ret = downloadFile(__p_title, __p_pos, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

namespace
{
const ::std::string __TransferFileModule__TransferFileManager_all[] =
{
    "downloadFile",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "uploadFile"
};

}

::Ice::DispatchStatus
TransferFileModule::TransferFileManager::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__TransferFileModule__TransferFileManager_all, __TransferFileModule__TransferFileManager_all + 6, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __TransferFileModule__TransferFileManager_all)
    {
        case 0:
        {
            return ___downloadFile(in, current);
        }
        case 1:
        {
            return ___ice_id(in, current);
        }
        case 2:
        {
            return ___ice_ids(in, current);
        }
        case 3:
        {
            return ___ice_isA(in, current);
        }
        case 4:
        {
            return ___ice_ping(in, current);
        }
        case 5:
        {
            return ___uploadFile(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
TransferFileModule::TransferFileManager::__writeImpl(::IceInternal::BasicStream* __os) const
{
    __os->startWriteSlice(ice_staticId(), -1, true);
    __os->endWriteSlice();
}

void
TransferFileModule::TransferFileManager::__readImpl(::IceInternal::BasicStream* __is)
{
    __is->startReadSlice();
    __is->endReadSlice();
}

void 
TransferFileModule::__patch(TransferFileManagerPtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::TransferFileModule::TransferFileManagerPtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::TransferFileModule::TransferFileManager::ice_staticId(), v);
    }
}
