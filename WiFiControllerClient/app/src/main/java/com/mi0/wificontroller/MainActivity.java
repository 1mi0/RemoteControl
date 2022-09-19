package com.mi0.wificontroller;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.mi0.wificontroller.guiobjects.GUIObjects;

public class MainActivity extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        GUIObjects.init(this);
    }
}
