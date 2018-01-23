#pragma once

#include <PQMTClient.h>

#include "ofMain.h"
using namespace PQ_SDK_MultiTouch;

class ofApp : public ofBaseApp{

	public:
    
    typedef void (*PFuncOnTouchGesture)(const TouchGesture & tg,void * call_object);

    PFuncOnTouchGesture m_pf_on_tges[TG_TOUCH_END + 1];
    
    
        ofApp();
        ~ofApp();
        int Init();
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void SetFuncsOnReceiveProc();
        void OnTouchPoint(const PQ_SDK_MultiTouch::TouchPoint & tp);
        static void OnReceivePointFrame(int frame_id,int time_stamp,int moving_point_count,const PQ_SDK_MultiTouch::TouchPoint * moving_point_array, void * call_back_object);
    
    
		
};
