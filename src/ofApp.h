#pragma once

#include "ofMain.h"
#include "ofxRPlidar.h"
#include "ofxOsc.h"
#include "ofxGui.h"

#define PORT 41234
#define HOST "127.0.0.1"

class ofApp : public ofBaseApp{
private:
  std::vector<std::shared_ptr<ofxRPlidar>> sensors_;
  ofxOscSender sender;

public:
  ofxIntSlider freq;
  ofxIntSlider scanMode;
  ofxToggle useScanModes;
  ofxToggle sending;
  ofxButton resetSensorsBtn;
  ofxPanel gui;

  int numSensors;

  void connectSensors();
  void resetSensors();

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
};
