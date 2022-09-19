package com.mi0.wificontroller.sockets;

public enum KEY
{
    RIGHT((byte)0x00),
    LEFT((byte)0x01),
    UP((byte)0x02),
    DOWN((byte)0x03),
    ENTER((byte)0x04),
    SPACE((byte)0x05);

    private final byte value;
    private KEY(byte value)
    {
        this.value = value;
    }

    public byte getValue()
    {
        return value;
    }
}
