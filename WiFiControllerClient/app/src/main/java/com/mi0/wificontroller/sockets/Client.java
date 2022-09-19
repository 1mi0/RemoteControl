package com.mi0.wificontroller.sockets;

import android.util.Log;

import androidx.arch.core.util.Function;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;

public class Client
{
    private static Client instance = null;
    private DatagramSocket dataSocket = null;
    private InetAddress address = null;

    private Client()
    {
        try
        {
            this.dataSocket = new DatagramSocket();
            this.dataSocket.setSoTimeout(4000);
        }
        catch (SocketException exception) {}
    }

    public static Client getInstance()
    {
        if (instance == null)
        {
            instance = new Client();
        }

        return instance;
    }

    public boolean IsAddressNull()
    {
        return address == null;
    }

    public boolean bind(String ipAddress)
    {
        try
        {
            this.address = InetAddress.getByName(ipAddress);
        }
        catch (UnknownHostException exception)
        {
            Log.d("Client", exception.getMessage());
        }

        return this.address != null;
    }

    public void unbind()
    {
        if (address != null)
        {
            address = null;
        }
    }

    public boolean sendPacket(final byte[] packet)
    {
        if (address == null)
        {
            return false;
        }

        Thread threadWorker = new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                DatagramPacket dataPacket = new DatagramPacket(packet, packet.length, address, 12433);
                try
                {
                    dataSocket.send(dataPacket);
                }
                catch (IOException exception)
                {
                }
            }
        });
        threadWorker.start();

        return true;
    }

    public<Temp> void receivePacket(final Function<byte[], Temp> function)
    {
        if (address == null)
        {
            return;
        }

        final byte[] buffer = new byte[256];
        Thread threadWorker = new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                DatagramPacket dataPacket = new DatagramPacket(buffer, buffer.length);
                try
                {
                    dataSocket.receive(dataPacket);
                    function.apply(dataPacket.getData());
                }
                catch (SocketTimeoutException e)
                {
                    function.apply(new byte[]{ (byte)0xff });
                }
                catch (IOException e) {}
            }
        });
        threadWorker.start();
    }
}
