#include "ofApp.h"

int numPoints = 0;
static TouchPoint globaltp[50];
ofApp::ofApp()
{
    memset(m_pf_on_tges,0, sizeof(m_pf_on_tges));
}
ofApp::~ofApp()
{
    DisconnectServer();
}

int ofApp::Init()
{
    int err_code = PQMTE_SUCCESS;
    
    // set the functions on server callback
    SetFuncsOnReceiveProc();
    // connect server
    cout << " connect to server..." << endl;
    if((err_code = ConnectServer()) != PQMTE_SUCCESS){
        cout << " connect server fail, socket error code:" << err_code << endl;
        return err_code;
    }
    // send request to server
    cout << " connect success, send request." << endl;
    TouchClientRequest tcq = {0};
    tcq.type = RQST_RAWDATA_ALL | RQST_GESTURE_ALL;
    if((err_code = SendRequest(tcq)) != PQMTE_SUCCESS){
        cout << " send request fail, error code:" << err_code << endl;
        return err_code;
    }
    //////////////you can set the move_threshold when the tcq.type is RQST_RAWDATA_INSIDE;
    //send threshold
    //int move_threshold = 1;// 1 pixel
    //if((err_code = SendThreshold(move_threshold) != PQMTE_SUCCESS){
    //    cout << " send threadhold fail, error code:" << err_code << endl;
    //    return err_code;
    //}
    //
    ////////////////////////
    //
    // start receiving
    cout << " send request success, start recv." << endl;
    return err_code;
}

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    for(int i = 0; i < numPoints; i++)
    {
        ofDrawRectangle(globaltp[i].x, globaltp[i].y, 30, 30);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::SetFuncsOnReceiveProc()
{
    PFuncOnReceivePointFrame old_rf_func = SetOnReceivePointFrame(&ofApp::OnReceivePointFrame,this);
}

void ofApp:: OnReceivePointFrame(int frame_id, int time_stamp, int moving_point_count, const PQ_SDK_MultiTouch::TouchPoint * moving_point_array, void * call_back_object)
{
    ofApp * sample = static_cast<ofApp*>(call_back_object);
    assert(sample != NULL);
    const char * tp_event[] =
    {
        "down",
        "move",
        "up",
    };
    
    numPoints = moving_point_count;
    //cout << " frame_id:" << frame_id << " time:"  << time_stamp << " ms" << " moving point count:" << moving_point_count << endl;
    for(int i = 0; i < moving_point_count; ++ i){
        PQ_SDK_MultiTouch::TouchPoint tp = moving_point_array[i];
        
        //globaltp = moving_point_array[i];
        //sample->OnTouchPoint(tp);
    }
    for(int j = 0; j < sizeof(moving_point_array); j++)
    {
        globaltp[j] = moving_point_array[j];
    }
}

void ofApp:: OnTouchPoint(const TouchPoint & tp)
{
    switch(tp.point_event)
    {
        case TP_DOWN:
            cout << "  point " << tp.id << " come at (" << tp.x << "," << tp.y
            << ") width:" << tp.dx << " height:" << tp.dy << endl;
            break;
        case TP_MOVE:
            cout << "  point " << tp.id << " move at (" << tp.x << "," << tp.y
            << ") width:" << tp.dx << " height:" << tp.dy << endl;
            break;
        case TP_UP:
            cout << "  point " << tp.id << " leave at (" << tp.x << "," << tp.y
            << ") width:" << tp.dx << " height:" << tp.dy << endl;
            break;
    }
}
