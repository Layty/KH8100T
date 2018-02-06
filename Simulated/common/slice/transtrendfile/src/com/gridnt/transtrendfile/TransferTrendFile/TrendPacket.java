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
// Generated from file `transtrendfile.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

package com.gridnt.transtrendfile.TransferTrendFile;

public class TrendPacket implements java.lang.Cloneable, java.io.Serializable
{
    public byte id;

    public String fepNode;

    public String filename;

    public int filelength;

    public byte[] datas;

    public TrendPacket()
    {
        fepNode = "";
        filename = "";
    }

    public TrendPacket(byte id, String fepNode, String filename, int filelength, byte[] datas)
    {
        this.id = id;
        this.fepNode = fepNode;
        this.filename = filename;
        this.filelength = filelength;
        this.datas = datas;
    }

    public boolean
    equals(java.lang.Object rhs)
    {
        if(this == rhs)
        {
            return true;
        }
        TrendPacket _r = null;
        if(rhs instanceof TrendPacket)
        {
            _r = (TrendPacket)rhs;
        }

        if(_r != null)
        {
            if(id != _r.id)
            {
                return false;
            }
            if(fepNode != _r.fepNode)
            {
                if(fepNode == null || _r.fepNode == null || !fepNode.equals(_r.fepNode))
                {
                    return false;
                }
            }
            if(filename != _r.filename)
            {
                if(filename == null || _r.filename == null || !filename.equals(_r.filename))
                {
                    return false;
                }
            }
            if(filelength != _r.filelength)
            {
                return false;
            }
            if(!java.util.Arrays.equals(datas, _r.datas))
            {
                return false;
            }

            return true;
        }

        return false;
    }

    public int
    hashCode()
    {
        int __h = 5381;
        __h = IceInternal.HashUtil.hashAdd(__h, "::TransferTrendFile::TrendPacket");
        __h = IceInternal.HashUtil.hashAdd(__h, id);
        __h = IceInternal.HashUtil.hashAdd(__h, fepNode);
        __h = IceInternal.HashUtil.hashAdd(__h, filename);
        __h = IceInternal.HashUtil.hashAdd(__h, filelength);
        __h = IceInternal.HashUtil.hashAdd(__h, datas);
        return __h;
    }

    public TrendPacket
    clone()
    {
        TrendPacket c = null;
        try
        {
            c = (TrendPacket)super.clone();
        }
        catch(CloneNotSupportedException ex)
        {
            assert false; // impossible
        }
        return c;
    }

    public void
    __write(IceInternal.BasicStream __os)
    {
        __os.writeByte(id);
        __os.writeString(fepNode);
        __os.writeString(filename);
        __os.writeInt(filelength);
        BytesHelper.write(__os, datas);
    }

    public void
    __read(IceInternal.BasicStream __is)
    {
        id = __is.readByte();
        fepNode = __is.readString();
        filename = __is.readString();
        filelength = __is.readInt();
        datas = BytesHelper.read(__is);
    }

    static public void
    __write(IceInternal.BasicStream __os, TrendPacket __v)
    {
        if(__v == null)
        {
            __nullMarshalValue.__write(__os);
        }
        else
        {
            __v.__write(__os);
        }
    }

    static public TrendPacket
    __read(IceInternal.BasicStream __is, TrendPacket __v)
    {
        if(__v == null)
        {
             __v = new TrendPacket();
        }
        __v.__read(__is);
        return __v;
    }
    
    private static final TrendPacket __nullMarshalValue = new TrendPacket();

    public static final long serialVersionUID = -2080769649L;
}