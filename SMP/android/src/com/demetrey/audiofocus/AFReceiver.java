package com.demetrey.audiofocus;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;

import android.media.AudioManager;
import android.media.AudioManager.OnAudioFocusChangeListener;
import android.media.MediaPlayer.OnCompletionListener;

import android.util.Log;
import org.qtproject.qt5.android.bindings.QtService;

public class AFReceiver extends QtService {

    final static String LOG_TAG = "MY_SERVICE";
    static boolean isAudioFocusGranted = false;
    static AudioManager.OnAudioFocusChangeListener mOnAudioFocusChangeListener;

    public static void startService(Context context) {
        context.startService(new Intent(context, AFReceiver.class));
        createAFListener();
        requestAudioFocus(context);
        Log.i(LOG_TAG, "START SERVICE");
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    public static void requestAudioFocus(Context context) {
        //Если аудиофокус не получен
        if (!isAudioFocusGranted) {
            AudioManager am = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
            int result = am.requestAudioFocus(mOnAudioFocusChangeListener,
                    // Use the music stream.
                    AudioManager.STREAM_MUSIC,
                    // Request permanent focus.
                    AudioManager.AUDIOFOCUS_GAIN);
            if (result == AudioManager.AUDIOFOCUS_REQUEST_GRANTED) {
                // Фокус получен
                isAudioFocusGranted = true;
                AFFunctions.afCorrect();
                Log.i(LOG_TAG, "Get AF");
            } else {
                // Не удалось получить аудиофокус
                AFFunctions.afFailed();
                Log.i(LOG_TAG, "NOT Get AF");
            }
        }
    }

    private static void createAFListener() {
        // Создаем слушатель фокуса
        mOnAudioFocusChangeListener = new AudioManager.OnAudioFocusChangeListener() {

            @Override
            public void onAudioFocusChange(int focusChange) {
                switch (focusChange) {
                    case AudioManager.AUDIOFOCUS_GAIN:
                        Log.i(LOG_TAG, "AUDIOFOCUS_GAIN");
                        AFFunctions.afGain();
                        // resum playback
                        // Другое приложение закончило воспроизводить звук
                        // Можем продолжать воспроизведение
                        break;
                    case AudioManager.AUDIOFOCUS_LOSS:
                        Log.i(LOG_TAG, "AUDIOFOCUS_LOSS");
                        AFFunctions.afLoss();
                        // Другое приложение воспроизводить что-то большое
                        // pause playback
                        break;
                    case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT:
                        // Другое приложение воспроизводит что-то небольшое
                        // Требуется приостановить воспроизведение
                        Log.i(LOG_TAG, "AUDIOFOCUS_LOSS_TRANSIENT");
                        AFFunctions.afLossTransient();
                        break;
                    case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK:
                        // Другое приложение воспроизводит что-то небольшое
                        // Убавить звук
                        // lower volume
                        Log.i(LOG_TAG, "AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK");
                        AFFunctions.afLossTransientCanDuck();
                        break;
                    case AudioManager.AUDIOFOCUS_REQUEST_FAILED:
                        Log.i(LOG_TAG, "AUDIOFOCUS_REQUEST_FAILED");
                        break;
                    default:
                        break;
                }
            }
        };
    }
}
