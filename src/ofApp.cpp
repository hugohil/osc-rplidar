#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  auto sensor_list = ofxRPlidar::getDeviceList();
  for(auto &sensor_info : sensor_list) {
    auto sensor = make_shared<ofxRPlidar>();
    if(sensor->connect(sensor_info.getDevicePath())) {
      sensor->start();
      sensors_.push_back(sensor);
    }
  }

  connected = sender.setup(HOST, PORT);

  ofSetFrameRate(5);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  for(auto &s : sensors_) {
    s->update();

    if (connected && sending) {
      string serial = s->getSerialNumber();

      ofxOscMessage message;
      message.setAddress("/lidar");
      message.addStringArg(serial);

      auto data = s->getResult();
      for(auto &d : data) {
        if(d.quality > 0) {
          message.addFloatArg(d.distance);
          message.addFloatArg(d.angle);
        }
      }
      sender.sendMessage(message);
    }
  }

  string buf = "sending osc messages to: " + string(HOST);
  buf += " " + ofToString(PORT);
  buf += "\ncurrently ";
  buf += connected ? "connected" : "not connected";
  buf += "\nrunning at " + ofToString((int) ofGetFrameRate()) + " fps";
  buf += "\npsending is ";
  buf += sending ? "ON" : "OFF";
  buf += " (S to switch)";
  ofDrawBitmapStringHighlight(buf, 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == 'S' || key == 's') {
    sending = !sending;
  }
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
