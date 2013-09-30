/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.Arette.Grandblue;

import org.cocos2dx.lib.Cocos2dxActivity;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

import android.os.Bundle;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.util.Log;
import android.widget.LinearLayout;

public class Grandblue extends Cocos2dxActivity{
	
	private static AdView adView_Top = null;
	private static AdView adView_Bottom = null;
	public static Handler handler = null;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		InitAdMob();
	}
    
    public void InitAdMob() {
    	try{
    		DisplayMetrics displaymetrics = new DisplayMetrics();
        	getWindowManager().getDefaultDisplay().getMetrics(displaymetrics);
        	int height = displaymetrics.heightPixels;
        	int width = displaymetrics.widthPixels;
        	
        	LinearLayout.LayoutParams adParams_Top = new LinearLayout.LayoutParams(width, LinearLayout.LayoutParams.WRAP_CONTENT);
        	LinearLayout.LayoutParams adParams_Bottom = new LinearLayout.LayoutParams(width, height*2 - 100);

        	adView_Top = new AdView(this, AdSize.BANNER, "fa6fc886b95242f1");
        	adView_Top.loadAd(new AdRequest());
        	adView_Top.setVisibility(AdView.INVISIBLE);
        	
        	adView_Bottom = new AdView(this, AdSize.BANNER, "fa6fc886b95242f1");
        	adView_Bottom.loadAd(new AdRequest());
        	adView_Bottom.setVisibility(AdView.INVISIBLE);
            
            // Adding full screen container
            addContentView(adView_Top, adParams_Top);
            addContentView(adView_Bottom, adParams_Bottom);
            
            // Set Handler
            handler = new Handler();
        }catch (Exception e) {
            //log("ADMOB ERROR: "+e);
        }
    }
    
    public static void SetAdModVisible(final boolean visible, final boolean isTop) {
    	/* ORIGINAL
    	if(visible) {
    		adView.setVisibility(AdView.VISIBLE);
    	} else {
    		adView.setVisibility(AdView.INVISIBLE);
    	}
    	*/
    	Runnable runnable;
		runnable = new Runnable() {
			@Override
			public void run() {
				handler.post(new Runnable() {
					@Override
					public void run() {
						if(visible) {
							if(isTop) {
								adView_Top.setVisibility(AdView.VISIBLE);
							} else {
								adView_Bottom.setVisibility(AdView.VISIBLE);
							}
						} else {
							if(isTop) {
								adView_Top.setVisibility(AdView.INVISIBLE);
							} else {
								adView_Bottom.setVisibility(AdView.INVISIBLE);
							}
						}
					}
				});
			}
		};
		new Thread(runnable).start();
    }
    
	public static void JavaJniTestFunc()
	{ 
		Log.d("JNITest", "Success Java Func Call!"); 
	} 

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// Grandblue should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
