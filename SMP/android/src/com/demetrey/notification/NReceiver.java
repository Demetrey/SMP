package com.demetrey.notification;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;

public class NReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
          String extra = intent.getStringExtra("info");

          if (extra.equals("play")) {
              NFunctions.nPlayButtonClicked();
          } else if (extra.equals("next")) {
              NFunctions.nNextButtonClicked();
          } else if (extra.equals("previous")) {
              NFunctions.nPreviousButtonClicked();
          }
    }
}
