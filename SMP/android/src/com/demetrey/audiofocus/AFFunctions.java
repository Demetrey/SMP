package com.demetrey.audiofocus;

public class AFFunctions {
    public static native void afGain();
    public static native void afLoss();
    public static native void afLossTransient();
    public static native void afLossTransientCanDuck();
    public static native void afCorrect();
    public static native void afFailed();
}
