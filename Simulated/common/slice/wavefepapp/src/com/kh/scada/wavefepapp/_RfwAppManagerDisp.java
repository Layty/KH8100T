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
// Generated from file `wavefepapp.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

package com.kh.scada.wavefepapp;

public abstract class _RfwAppManagerDisp extends Ice.ObjectImpl implements RfwAppManager
{
    protected void
    ice_copyStateFrom(Ice.Object __obj)
        throws java.lang.CloneNotSupportedException
    {
        throw new java.lang.CloneNotSupportedException();
    }

    public static final String[] __ids =
    {
        "::Ice::Object",
        "::wavefepapp::RfwAppManager"
    };

    public boolean ice_isA(String s)
    {
        return java.util.Arrays.binarySearch(__ids, s) >= 0;
    }

    public boolean ice_isA(String s, Ice.Current __current)
    {
        return java.util.Arrays.binarySearch(__ids, s) >= 0;
    }

    public String[] ice_ids()
    {
        return __ids;
    }

    public String[] ice_ids(Ice.Current __current)
    {
        return __ids;
    }

    public String ice_id()
    {
        return __ids[1];
    }

    public String ice_id(Ice.Current __current)
    {
        return __ids[1];
    }

    public static String ice_staticId()
    {
        return __ids[1];
    }

    public final void processRFW(RFWPacket aRFWPacket)
    {
        processRFW(aRFWPacket, null);
    }

    public final void processRfwDir(RFWDirPacket aRfwDirPacket)
    {
        processRfwDir(aRfwDirPacket, null);
    }

    /**
     * @param: unitno - �ն˺š�
     * @param: operateType - �������͡�
     * @param: tip - flag=true��tip=""��flag=false��tip��ʾ����ԭ��
     **/
    public final void rfwExecuteEcho(RfwOperate operate, boolean flag, String tip)
    {
        rfwExecuteEcho(operate, flag, tip, null);
    }

    public static Ice.DispatchStatus ___rfwExecuteEcho(RfwAppManager __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
        __checkMode(Ice.OperationMode.Normal, __current.mode);
        IceInternal.BasicStream __is = __inS.startReadParams();
        RfwOperate operate = null;
        boolean flag;
        String tip;
        operate = RfwOperate.__read(__is, operate);
        flag = __is.readBool();
        tip = __is.readString();
        __inS.endReadParams();
        __obj.rfwExecuteEcho(operate, flag, tip, __current);
        __inS.__writeEmptyParams();
        return Ice.DispatchStatus.DispatchOK;
    }

    public static Ice.DispatchStatus ___processRfwDir(RfwAppManager __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
        __checkMode(Ice.OperationMode.Normal, __current.mode);
        IceInternal.BasicStream __is = __inS.startReadParams();
        RFWDirPacket aRfwDirPacket = null;
        aRfwDirPacket = RFWDirPacket.__read(__is, aRfwDirPacket);
        __inS.endReadParams();
        __obj.processRfwDir(aRfwDirPacket, __current);
        __inS.__writeEmptyParams();
        return Ice.DispatchStatus.DispatchOK;
    }

    public static Ice.DispatchStatus ___processRFW(RfwAppManager __obj, IceInternal.Incoming __inS, Ice.Current __current)
    {
        __checkMode(Ice.OperationMode.Normal, __current.mode);
        IceInternal.BasicStream __is = __inS.startReadParams();
        RFWPacket aRFWPacket = null;
        aRFWPacket = RFWPacket.__read(__is, aRFWPacket);
        __inS.endReadParams();
        __obj.processRFW(aRFWPacket, __current);
        __inS.__writeEmptyParams();
        return Ice.DispatchStatus.DispatchOK;
    }

    private final static String[] __all =
    {
        "ice_id",
        "ice_ids",
        "ice_isA",
        "ice_ping",
        "processRFW",
        "processRfwDir",
        "rfwExecuteEcho"
    };

    public Ice.DispatchStatus __dispatch(IceInternal.Incoming in, Ice.Current __current)
    {
        int pos = java.util.Arrays.binarySearch(__all, __current.operation);
        if(pos < 0)
        {
            throw new Ice.OperationNotExistException(__current.id, __current.facet, __current.operation);
        }

        switch(pos)
        {
            case 0:
            {
                return ___ice_id(this, in, __current);
            }
            case 1:
            {
                return ___ice_ids(this, in, __current);
            }
            case 2:
            {
                return ___ice_isA(this, in, __current);
            }
            case 3:
            {
                return ___ice_ping(this, in, __current);
            }
            case 4:
            {
                return ___processRFW(this, in, __current);
            }
            case 5:
            {
                return ___processRfwDir(this, in, __current);
            }
            case 6:
            {
                return ___rfwExecuteEcho(this, in, __current);
            }
        }

        assert(false);
        throw new Ice.OperationNotExistException(__current.id, __current.facet, __current.operation);
    }

    protected void __writeImpl(IceInternal.BasicStream __os)
    {
        __os.startWriteSlice(ice_staticId(), -1, true);
        __os.endWriteSlice();
    }

    protected void __readImpl(IceInternal.BasicStream __is)
    {
        __is.startReadSlice();
        __is.endReadSlice();
    }

    public static final long serialVersionUID = 0L;
}