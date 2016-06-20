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
#include "stdr_parser/stdr_parser_yaml_file_writer.h"
#include "stdr_parser_xml_file_writer_test.cpp"


/**
 * @class YamlFileWriterTest
 * @brief Basic Test Fixture for testing YamlFileWriter
 */
namespace stdr_parser
{

class YamlFileWriterTest :  public XmlFileWriterTest
{

  

};

TEST_F(YamlFileWriterTest, messageToYamlElementNoise)
{
  init("/test/files/elements/element.yaml");

  //create message
  stdr_msgs::Noise msg;
  std::string values[] = {"1", "2", "0.2"};
  sub_elements els;
  els.values=values;
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to xml element and write to file
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/Noise_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementFootprint)
{
  init("/test/files/elements/element.yaml");

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

  //convert message to xml element and write to file
  XmlFileWriterTest::createMessage(&msg, els);
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/Footprint_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementPose2D)
{
  init("/test/files/elements/element.yaml");

  //create message
  geometry_msgs::Pose2D msg;
  std::string values[] = {"1", "2", "0.2"};
  sub_elements els;
  els.values=values;  
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to xml element and write to file
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/Pose2D_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementLaserSensor)
{
  init("/test/files/elements/element.yaml");

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
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to xml element and write to file
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/LaserSensor_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementSonarSensor)
{ 
  init("/test/files/elements/element.yaml");

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
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to xml element and write to file
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/SonarSensor_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementRfidSensor)
{ 
  init("/test/files/elements/element.yaml");

  //create message
  stdr_msgs::RfidSensorMsg msg;
  std::string values[] = {"5", "2", "5", "2", "2"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[1];
  std::string val_1[] = {"10", "2", "37"};
  components[0].values = val_1;
  els.components = components;
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to yaml element and write to file
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/RfidSensor_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementCO2Sensor)
{ 
  init("/test/files/elements/element.yaml");

  //create message
  stdr_msgs::CO2SensorMsg  msg;
  std::string values[] = {"5", "2", "5"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[1];
  std::string val_1[] = {"20", "32", "47"};
  components[0].values = val_1;
  els.components = components;
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to yaml element and write to file
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/CO2Sensor_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementThermalSensor)
{ 
  init("/test/files/elements/element.yaml");

  //create message
  stdr_msgs::ThermalSensorMsg  msg;
  std::string values[] = {"5", "2", "5","3"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[1];
  std::string val_1[] = {"45", "52", "27"};
  components[0].values = val_1;
  els.components = components;
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to yaml element and write to file
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/ThermalSensor_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementSoundSensor)
{ 
  init("/test/files/elements/element.yaml");

  //create message
  stdr_msgs::SoundSensorMsg  msg;
  std::string values[] = {"5", "2", "5","3"};
  sub_elements els;
  els.values=values;
  sub_elements* components = new sub_elements[1];
  std::string val_1[] = {"20", "32", "47"};
  components[0].values = val_1;
  els.components = components;
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to yaml element and write to file
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/SoundSensor_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementKinematic)
{ 
  init("/test/files/elements/element.yaml");

  //create message
  stdr_msgs::KinematicMsg  msg;
  std::string values[] = {"5", "2", "5","3","5", "2", "5","3","5", "2", "5","3","8"};
  sub_elements els;
  els.values=values;
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to yaml element and write to file
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/Kinematic_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlElementRobot)
{ 
  init("/test/files/elements/element.yaml");

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

  //convert message to yaml element and write to file
  XmlFileWriterTest::createMessage(&msg, els);
  YAML::Emitter out;
  out << msg;
  std::ofstream sensorYamlFile;    
  sensorYamlFile.open(utils_file_.c_str());
  sensorYamlFile << out.c_str();
  sensorYamlFile.close();
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/Robot_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(YamlFileWriterTest, messageToYamlFileNoise)
{
  init("/test/files/elements/element.yaml");

  //create message
  stdr_msgs::Noise msg;
  std::string values[] = {"1", "2", "0.2"};
  sub_elements els;
  els.values=values;
  XmlFileWriterTest::createMessage(&msg, els);

  //convert message to yaml element and write to file
  YamlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);

  //read expected element
  init("/test/files/elements/Noise_element_exp.yaml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

}




