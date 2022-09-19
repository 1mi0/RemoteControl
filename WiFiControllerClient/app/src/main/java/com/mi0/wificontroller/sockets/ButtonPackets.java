package com.mi0.wificontroller.sockets;

import android.os.Handler;
import android.os.Looper;

import androidx.arch.core.util.Function;

import com.mi0.wificontroller.guiobjects.GUIObjects;


public class ButtonPackets implements Packet
{
    private static Client clientInstance = null;
    private final byte action = 0x01;
    private byte[] packet;

    public ButtonPackets()
    {
        clientInstance = Client.getInstance();
    }

    @Override
    public void send()
    {
        if (clientInstance.sendPacket(this.packet))
        {
            GUIObjects.connectView.setText("Button sent");
        }
    }
    public void sendButton(final KEY button)
    {
        this.packet = new byte[] { action, button.getValue(), (byte)0xff };
        this.send();

        final byte[] expectedPacket = new byte[] { action, button.getValue(), 0x01, (byte)0xff };
        clientInstance.receivePacket(new Function<byte[], Boolean>()
        {
            @Override
            public Boolean apply(byte[] bytes)
            {
                if (bytes != expectedPacket)
                {
                    new Handler(Looper.getMainLooper()).post(new Runnable () {
                        @Override
                        public void run () {
                            sendButton(button);
                        }
                    });
                }

                return true;
            }
        });
    }
}
