#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  this->connectSensors();

  sender.setup(HOST, PORT);

  resetSensorsBtn.addListener(this, &ofApp::resetSensors);

  gui.setup();
  gui.add(freq.setup("send once every x frame", 12, 1, 120));
  gui.add(resetSensorsBtn.setup("reset sensors"));
  gui.add(sending.setup("send", true));
}

//--------------------------------------------------------------
void ofApp::connectSensors(){
  auto sensor_list = ofxRPlidar::getDeviceList();
  for(auto &sensor_info : sensor_list) {
    auto sensor = make_shared<ofxRPlidar>();
    if(sensor->connect(sensor_info.getDevicePath())) {
      sensor->start();
      sensors_.push_back(sensor);
    }
  }
}

//--------------------------------------------------------------
void ofApp::resetSensors(){
  for(auto &s : sensors_) {
    s->stop();
    s->disconnect();
  }
  sensors_.clear();
  this->connectSensors();
}

//--------------------------------------------------------------
void ofApp::update(){
  numSensors = 0;
  for(auto &s : sensors_) {
    if (s->isConnected()) {
      numSensors++;
    } else {
      ofLogNotice(ofToString(s->isConnected()));
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  if ((ofGetFrameNum() % freq) == 0) {
    for(auto &s : sensors_) {
      s->update();

      if (sending) {
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
  }

  string buf1 = "sending osc messages to: \n";
  buf1 += ofToString(HOST) + ":" + ofToString(PORT);
  ofDrawBitmapStringHighlight(buf1, 10, 120);

  string buf2 = ofToString((int) ofGetFrameRate()) + "fps";
  buf2 += "\nsending " + ofToString((int) ofGetFrameRate() / freq) + " lidar datas per sec.";
  ofDrawBitmapStringHighlight(buf2, 10, 220);

  string buf3 = ofToString(numSensors) + " sensor(s) connected";
  ofDrawBitmapStringHighlight(buf3, 10, 320);

  gui.draw();
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
