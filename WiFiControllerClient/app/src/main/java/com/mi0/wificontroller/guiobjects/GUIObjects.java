package com.mi0.wificontroller.guiobjects;

import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.mi0.wificontroller.R;
import com.mi0.wificontroller.sockets.ButtonPackets;
import com.mi0.wificontroller.sockets.Client;
import com.mi0.wificontroller.sockets.KEY;

public class GUIObjects
{
    public static EditText ipAddress;
    public static Button bindButton;
    public static Button enterButton;
    public static Button spaceButton;
    public static Button leftButton;
    public static Button rightButton;
    public static Button upButton;
    public static Button downButton;
    public static TextView connectView;

    private static Client clientInstance = null;
    private static ButtonPackets buttonPacket = null;

    public static void init(AppCompatActivity obj)
    {
        GUIObjects.clientInstance = Client.getInstance();
        if (GUIObjects.buttonPacket == null)
        {
            GUIObjects.buttonPacket = new ButtonPackets();
        }

        GUIObjects.ipAddress =      (EditText)  obj.findViewById(R.id.txtIP);
        GUIObjects.bindButton =     (Button)    obj.findViewById(R.id.btnConnect);
        GUIObjects.connectView =    (TextView)  obj.findViewById(R.id.lblConnectionOutput);
        GUIObjects.enterButton =   (Button)    obj.findViewById(R.id.btnEnter);
        GUIObjects.spaceButton =   (Button)    obj.findViewById(R.id.btnSpace);
        GUIObjects.leftButton =   (Button)    obj.findViewById(R.id.btnLeftClick);
        GUIObjects.rightButton =   (Button)    obj.findViewById(R.id.btnRightClick);
        GUIObjects.upButton =   (Button)    obj.findViewById(R.id.btnUpClick);
        GUIObjects.downButton =   (Button)    obj.findViewById(R.id.btnDownClick);

        GUIObjects.bindButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                if (!GUIObjects.clientInstance.bind(GUIObjects.ipAddress.getText().toString()))
                {
                    GUIObjects.connectView.setText("Binding failed");
                    return;
                }
                GUIObjects.connectView.setText("Bound");
            }
        });

        GUIObjects.enterButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                GUIObjects.buttonPacket.sendButton(KEY.ENTER);
            }
        });

        GUIObjects.spaceButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                GUIObjects.buttonPacket.sendButton(KEY.SPACE);
            }
        });

        GUIObjects.leftButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                GUIObjects.buttonPacket.sendButton(KEY.LEFT);
            }
        });

        GUIObjects.rightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                GUIObjects.buttonPacket.sendButton(KEY.RIGHT);
            }
        });

        GUIObjects.upButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                GUIObjects.buttonPacket.sendButton(KEY.UP);
            }
        });

        GUIObjects.downButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                GUIObjects.buttonPacket.sendButton(KEY.DOWN);
            }
        });

        if (!clientInstance.IsAddressNull())
        {
            GUIObjects.connectView.setText("Bound");
        }
    }
}
