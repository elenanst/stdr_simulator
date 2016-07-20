/******************************************************************************
   STDR Simulator - Simple Two DImensional Robot Simulator
   Copyright (C) 2013 STDR Simulator
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

   Authors :
   * Eleni Nisioti, elennisioti@gmail.com
******************************************************************************/

#include <gtest/gtest.h>
#include "stdr_parser/stdr_parser_xml_file_writer.h"




namespace stdr_parser
{



/**
 * @class XmlFileWriterTest
 * @brief Basic Test Fixture for testing XmlFileWriter
 */
class XmlFileWriterTest : public ::testing::Test
{
public:
  struct sub_elements
  {
    std::string* values;
    std::string type;
    sub_elements* components;
    unsigned int num_components;
    
  };

 protected:
  XmlFileWriterTest()
  {
  }

  //initialize temporary file
  void initTempFile(const std::string& type)
  {
   std::string filename = "/tmp/tmpfileXXXXXX" + type;
   temp_file_ = strdup(filename.c_str());
   mkstemp(temp_file_);
  }

  void init(const std::string& filename)
  {
    utils_file_ = ros::package::getPath("stdr_parser") +
                    "/test/files/XmlFileWriter/" +
                   filename;
  }

  template <class T>
  void createMessage(T* msg, const sub_elements els);

  std::string readFile(const std::string& file)
  {
    
     std::ifstream ifs(file.c_str());
     std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
     content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());

     return content;
  }

 std::string utils_file_;
 char* temp_file_;
  
};

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::Noise>(stdr_msgs::Noise* msg, const sub_elements els)
{
  msg->noise = (els.values[0] == "1");
  msg->noiseMean = atoi(els.values[1].c_str());
  msg->noiseStd = atoi(els.values[2].c_str()); 
}


template <>
void XmlFileWriterTest::createMessage<geometry_msgs::Point>(geometry_msgs::Point*  msg, const sub_elements els)
{
  msg->x = atoi(els.values[0].c_str());
  msg->y = atoi(els.values[1].c_str());
  msg->z= atoi(els.values[2].c_str()); 
}

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::FootprintMsg>(stdr_msgs::FootprintMsg* msg, const sub_elements els)
{

  geometry_msgs::Point points[3];
  for (unsigned int i = 0 ; i < els.num_components ; i++)
  {
    createMessage(&(points[i]), els.components[i]);
    msg->points.push_back(points[i]);
  }
  msg->radius = atoi(els.values[0].c_str());
}

template <>
void XmlFileWriterTest::createMessage<geometry_msgs::Pose2D>(geometry_msgs::Pose2D*  msg, const sub_elements els)
{
  msg->x = atoi(els.values[0].c_str());
  msg->y = atoi(els.values[1].c_str());
  msg->theta= atoi(els.values[2].c_str()); 
}

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::LaserSensorMsg>(stdr_msgs::LaserSensorMsg*  msg, const sub_elements els)
{
  msg->maxAngle = atoi(els.values[0].c_str());
  msg->minAngle= atoi(els.values[1].c_str()); 
  msg->maxRange = atoi(els.values[2].c_str());
  msg->minRange = atoi(els.values[3].c_str());
  msg->numRays = atoi(els.values[4].c_str()); 
  msg->frequency = atoi(els.values[5].c_str());
  msg->frame_id = els.values[6]; 
  for (unsigned int i = 0 ; i < els.num_components ; i++)
  {
    if(!(strcmp(els.components[i].type.c_str(),"Noise")) )
    {
      stdr_msgs::Noise msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->noise = msg_n;
    }
    else if(!(strcmp(els.components[i].type.c_str(),"Pose2D")))
    {
      geometry_msgs::Pose2D msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->pose = msg_n;
    }

  }

}

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::SonarSensorMsg>(stdr_msgs::SonarSensorMsg*  msg, const sub_elements els)
{
  msg->maxRange = atoi(els.values[0].c_str());
  msg->minRange= atoi(els.values[1].c_str()); 
  msg->coneAngle = atoi(els.values[2].c_str());
  msg->frequency = atoi(els.values[3].c_str());
  msg->frame_id = els.values[4]; 
  for (unsigned int i = 0 ; i < els.num_components ; i++)
  {
    if(!(strcmp(els.components[i].type.c_str(),"Noise")) )
    {
      stdr_msgs::Noise msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->noise = msg_n;
    }
    else if(!(strcmp(els.components[i].type.c_str(),"Pose2D")))
    {
      geometry_msgs::Pose2D msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->pose = msg_n;
    }

  }
}

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::RfidSensorMsg>(stdr_msgs::RfidSensorMsg*  msg, const sub_elements els)
{
  msg->maxRange = atoi(els.values[0].c_str());
  msg->angleSpan = atoi(els.values[1].c_str()); 
  msg->signalCutoff = atoi(els.values[2].c_str());
  msg->frequency = atoi(els.values[3].c_str());
  msg->frame_id = els.values[4]; 
  geometry_msgs::Pose2D pose;
  createMessage(&pose, els.components[0]);
  msg->pose = pose;
 
}

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::CO2SensorMsg>(stdr_msgs::CO2SensorMsg*  msg, const sub_elements els)
{
  msg->maxRange = atoi(els.values[0].c_str());
  msg->frequency = atoi(els.values[1].c_str());
  msg->frame_id = els.values[2]; 
  geometry_msgs::Pose2D pose;
  createMessage(&pose, els.components[0]);
  msg->pose = pose;
}

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::ThermalSensorMsg>(stdr_msgs::ThermalSensorMsg*  msg, const sub_elements els)
{
  msg->maxRange = atoi(els.values[0].c_str());
  msg->frequency = atoi(els.values[1].c_str());
  msg->angleSpan= atoi(els.values[2].c_str()); 
  msg->frame_id = els.values[3]; 
  geometry_msgs::Pose2D pose;
  createMessage(&pose, els.components[0]);
  msg->pose = pose;
}

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::SoundSensorMsg>(stdr_msgs::SoundSensorMsg*  msg, const sub_elements els)
{
  msg->maxRange = atoi(els.values[0].c_str());
  msg->frequency = atoi(els.values[1].c_str());
  msg->angleSpan = atoi(els.values[2].c_str()); 
  msg->frame_id = els.values[3]; 
  geometry_msgs::Pose2D pose;
  createMessage(&pose, els.components[0]);
  msg->pose = pose;
}

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::KinematicMsg>(stdr_msgs::KinematicMsg*  msg,
const sub_elements els)
{
  msg->type = els.values[0]; 
  msg->a_ux_ux = atoi(els.values[1].c_str());
  msg->a_ux_uy = atoi(els.values[2].c_str());
  msg->a_ux_w= atoi(els.values[3].c_str());
  msg->a_uy_ux = atoi(els.values[4].c_str());
  msg->a_uy_uy = atoi(els.values[5].c_str());
  msg->a_uy_w = atoi(els.values[6].c_str());
  msg->a_w_ux = atoi(els.values[7].c_str());
  msg->a_w_uy = atoi(els.values[8].c_str());
  msg->a_w_w = atoi(els.values[9].c_str());
  msg->a_g_ux = atoi(els.values[10].c_str());
  msg->a_g_uy = atoi(els.values[11].c_str());
  msg->a_g_w = atoi(els.values[12].c_str());
}

template <>
void XmlFileWriterTest::createMessage<stdr_msgs::RobotMsg>(stdr_msgs::RobotMsg*  msg,
                                                            const sub_elements els)
{

  for (unsigned int i = 0 ; i < els.num_components ; i++)
  {
    if(!(strcmp(els.components[i].type.c_str(),"laserSensors")) )
    {
      stdr_msgs::LaserSensorMsg  msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->laserSensors.push_back(msg_n);
    }
    else if(!(strcmp(els.components[i].type.c_str(),"sonarSensors")) )
    {
      stdr_msgs::SonarSensorMsg msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->sonarSensors.push_back(msg_n);
    }
    else if(!(strcmp(els.components[i].type.c_str(),"rfidSensors")) )
    {
      stdr_msgs::RfidSensorMsg msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->rfidSensors.push_back(msg_n);
    }
    else if(!(strcmp(els.components[i].type.c_str(),"co2Sensors")) )
    {
      stdr_msgs::CO2SensorMsg msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->co2Sensors.push_back(msg_n);
    }
    else if(!(strcmp(els.components[i].type.c_str(),"soundSensors")) )
    {
     stdr_msgs::SoundSensorMsg msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->soundSensors.push_back(msg_n);
    }
    else if(!(strcmp(els.components[i].type.c_str(),"thermalSensors")) )
    {
      stdr_msgs::ThermalSensorMsg msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->thermalSensors.push_back(msg_n);
    }
    else if(!(strcmp(els.components[i].type.c_str(),"footprint")) )
    {
      stdr_msgs::FootprintMsg msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->footprint = msg_n;
    }
    else if(!(strcmp(els.components[i].type.c_str(),"kinematicModel") ))
    {
      stdr_msgs::KinematicMsg msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->kinematicModel = msg_n;
    }
    else if(!(strcmp(els.components[i].type.c_str(),"initialPose")) )
    {
      geometry_msgs::Pose2D  msg_n;
      createMessage(&msg_n, els.components[i]);
      msg->initialPose = msg_n;
    }
  }
}

TEST_F(XmlFileWriterTest, messageToXmlElementNoise)
{
   //create message
  stdr_msgs::Noise msg;
  std::string values[] = {"1", "5", "0"};
  sub_elements els;
  els.values=values;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

  //read expected string
  init("Noise_element_exp.xml");
  std::string expected_element = readFile(utils_file_);

  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementFootprint)
{


  //create message
  stdr_msgs::FootprintMsg msg;
  std::string values[] = {"12"};
  sub_elements els;
  els.values = values;
  sub_elements* components = new sub_elements[3];
  std::string val_1[] = {"10", "2", "37"};
  std::string val_2[] = {"4", "26", "23"};
  std::string val_3[] = {"51", "12", "53"};
  components[0].values = val_1;
  components[1].values = val_2;
  components[2].values = val_3;
  els.components = components;
  els.num_components = 3;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element =readFile(std::string(temp_file_));
  
  //read expected string
  init("Footprint_element_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementPose2D)
{

  //create message
  geometry_msgs::Pose2D msg;
  std::string values[] = {"1", "2", "0.2"};
  sub_elements els;
  els.values=values;  
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

  //read expected string
  init("Pose2D_element_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementLaserSensor)
{
    //create message
  stdr_msgs::LaserSensorMsg msg;
  std::string values[] = {"50", "20", "5", "2", "10", "25", "2"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[2];
  std::string val_1[] = {"1", "2", "4"};
  std::string val_2[] = {"5", "10", "40"};
  components[0].values = val_1;
  components[1].values = val_2;
  components[0].type = "noise";
  components[1].type = "pose2d";
  els.num_components = 2;
  els.components = components;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

  init("LaserSensor_element_exp.xml");

  //read expected elements
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementSonarSensor)
{ 
  //create message
  stdr_msgs::SonarSensorMsg msg;
  std::string values[] = {"5", "2", "5", "2", "2"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[2];
  std::string val_1[] = {"1", "2", "4"};
  std::string val_2[] = {"5", "10", "40"};
  components[0].values = val_1;
  components[1].values = val_2;
  components[0].type = "noise";
  components[1].type = "pose2d";
  els.num_components = 2;
  els.components = components;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

    //read expected element
  init("SonarSensor_element_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementRfidSensor)
{ 
  //create message
  stdr_msgs::RfidSensorMsg msg;
  std::string values[] = {"5", "2", "5", "2", "2"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[1];
  std::string val_1[] = {"10", "2", "37"};
  components[0].values = val_1;
  els.components = components;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

  //read expected element
  init("RfidSensor_element_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementCO2Sensor)
{ 
  //create message
  stdr_msgs::CO2SensorMsg  msg;
  std::string values[] = {"5", "2", "5"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[1];
  std::string val_1[] = {"20", "32", "47"};
  components[0].values = val_1;
  els.components = components;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

  //read expected element
  init("CO2Sensor_element_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementThermalSensor)
{ 

  //create message
  stdr_msgs::ThermalSensorMsg  msg;
  std::string values[] = {"5", "2", "5","3"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[1];
  std::string val_1[] = {"45", "52", "27"};
  components[0].values = val_1;
  els.components = components;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

  //read expected element
  init("ThermalSensor_element_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementSoundSensor)
{ 
  //create message
  stdr_msgs::SoundSensorMsg  msg;
  std::string values[] = {"5", "2", "5","3"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[1];
  std::string val_1[] = {"20", "32", "47"};
  components[0].values = val_1;
  els.components = components;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

  //read expected element
  init("SoundSensor_element_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementKinematic)
{ 
  //create message
  stdr_msgs::KinematicMsg  msg;
  std::string values[] = {"5", "2", "5","3","5", "2", "5","3","5", "2", "5","3","8"};
  sub_elements els;
  els.values=values;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

  //read expected element
  init("Kinematic_element_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(XmlFileWriterTest, messageToXmlElementRobot)
{ 
  //create message
  stdr_msgs::RobotMsg  msg;
  sub_elements els;
  sub_elements* components = new sub_elements[9];
  std::string val_1[] = {"50", "20", "5", "2", "10", "25", "2"};
  std::string val_2[] = {"5", "2", "5", "2", "2"};
  std::string val_3[] = {"5", "2", "5", "2", "2"};
  std::string val_4[] = {"5", "2", "5"};
  std::string val_5[] = {"5", "2", "5","3"};
  std::string val_6[] = {"5", "2", "5","3"};
  std::string val_7[] = {"12"};
  std::string val_8[] = {"5", "2", "5","3","5", "2", "5","3","5", "2", "5","3","8"};
  std::string val_9[] = {"5", "2", "5"};
  std::string val_noise[] = {"1", "2", "4"};
  std::string val_pose2d[] = {"5", "10", "40"};
  std::string val_point[] = {"15", "100", "42"};
  sub_elements* sub_components = new sub_elements[2];
  sub_components[0].values = val_noise;
  sub_components[1].values = val_pose2d;
  sub_components[0].type = "Noise";
  sub_components[1].type = "Pose2D";

  components[0].values = val_1;
  components[0].type = "laserSensors";
  components[0].num_components = 2;
  components[0].components = sub_components; 

  components[1].values = val_2;
  components[1].type = "sonarSensors";
  components[1].num_components = 2;
  components[1].components = sub_components; 

  components[2].values = val_3;
  components[2].type = "rfidSensors";
  components[2].num_components = 1;
  components[2].components = &sub_components[1]; 

  components[3].values = val_4;
  components[3].type = "co2Sensors";
  components[3].num_components = 1;
  components[3].components = &sub_components[1]; 

  components[4].values = val_5;
  components[4].type = "soundSensors";
  components[4].num_components = 1;
  components[4].components = &sub_components[1]; 

  components[5].values = val_6;
  components[5].type = "thermalSensors";
  sub_elements* thermalcomponents = new sub_elements[1];
  components[5].components = &sub_components[1]; 

  components[6].values = val_7;
  components[6].type = "footprint";
  sub_elements* footprint_components = new sub_elements[1];
  footprint_components[0].values = val_point;
  components[6].num_components = 1;
  components[6].components = footprint_components; 


  components[7].values = val_8;
  components[7].type = "kinematicModel";
  components[8].values = val_9;
  components[8].type = "initialPose";


  els.components = components;
  els.num_components = 9;
  createMessage(&msg, els);

  //convert message to xml element and save
  TiXmlDocument doc;
  XmlFileWriter::messageToXmlElement<>(msg, &doc);
  initTempFile(".xml"); 
  doc.SaveFile(temp_file_);
  std::string element = readFile(std::string(temp_file_));

  //read expected element
  init("Robot_element_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(XmlFileWriterTest, messageToFileNoise)
{
  //create message
  stdr_msgs::Noise msg;
  std::string values[] = {"1", "5", "0"};
  sub_elements els;
  els.values=values;
  createMessage(&msg, els);

  //convert message to xml element and save
  initTempFile(".xml"); 
  XmlFileWriter::messageToFile<>(msg, std::string(temp_file_));
  std::string element = readFile(std::string(temp_file_));
  init("Noise_element_exp.xml");

  //read expected element
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}
}  // namespace stdr_parser

