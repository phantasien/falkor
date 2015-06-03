package com.github.phantasien.falkor.test;

import android.app.Activity;
import android.os.Bundle;
import android.content.res.AssetManager;

public class FalkorTestMainActivity extends Activity
{
  
  private AssetManager assetManager;

  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);

    assetManager = getResources().getAssets();
    run(assetManager);
  }

  public native void run(AssetManager assetManager);

  static {
    System.loadLibrary("falkor-test");
  }
}
