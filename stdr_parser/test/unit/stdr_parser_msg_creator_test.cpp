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
#include <iterator> 
#include <tinyxml.h>
#include "stdr_parser/stdr_parser_msg_creator.h"
#include "stdr_parser/stdr_xml_parser.h"
#include "stdr_parser/stdr_parser_xml_file_writer.h"


namespace stdr_parser
{


/**
 * @class ValidatorTest
 * @brief Basic Test Fixture for testing Validator
 */
class MsgCreatorTest : public ::testing::Test
{
 protected:
  MsgCreatorTest()
  {
  }

  virtual void TearDown()
  {
    
  }

  void init(const std::string& filename)
  {
    utils_file_ = ros::package::getPath("stdr_parser") +
                    filename;
    root_node_ = new Node(); 
    id_ = 0;
  }
   
 std::string readFile(const std::string& file)
  {
    
     std::ifstream ifs(file.c_str());
     std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
     content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());

     return content;
 }

 
  std::string utils_file_;
  Node* root_node_;
  unsigned int id_;
  
};

TEST_F(MsgCreatorTest, createMessageNoise)
{
  init(std::string("/test/files/elements/noise_gauss.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::Noise msg = MessageCreator::createMessage<stdr_msgs::Noise>(root_node_, id_);
  init(std::string("/test/files/elements/noise_gauss_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/noise_gauss_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}

TEST_F(MsgCreatorTest, createMessageFootprint)
{
  init(std::string("/test/files/elements/element_ex_Footprint.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::FootprintMsg msg = MessageCreator::createMessage<stdr_msgs::FootprintMsg>(root_node_, id_);
  init(std::string("/test/files/elements/footprint_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/footprint_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}

TEST_F(MsgCreatorTest, createMessageLaserSensor)
{
  init(std::string("/test/files/elements/element_ex_LaserSensor.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::LaserSensorMsg msg = MessageCreator::createMessage<stdr_msgs::LaserSensorMsg>(root_node_, id_);
  init(std::string("/test/files/elements/LaserSensor_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/LaserSensor_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}

TEST_F(MsgCreatorTest, createMessageSonarSensor)
{
  init(std::string("/test/files/elements/element_ex_SonarSensor.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::SonarSensorMsg msg = MessageCreator::createMessage<stdr_msgs::SonarSensorMsg>(root_node_, id_);
  init(std::string("/test/files/elements/SonarSensor_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/SonarSensor_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}

TEST_F(MsgCreatorTest, createMessageRfidSensor)
{
  init(std::string("/test/files/elements/element_ex_RfidSensor.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::RfidSensorMsg msg = MessageCreator::createMessage<stdr_msgs::RfidSensorMsg>(root_node_, id_);
  init(std::string("/test/files/elements/RfidSensor_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/RfidSensor_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}

TEST_F(MsgCreatorTest, createMessageCO2Sensor)
{
  init(std::string("/test/files/elements/element_ex_CO2Sensor.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::CO2SensorMsg msg = MessageCreator::createMessage<stdr_msgs::CO2SensorMsg>(root_node_, id_);
  init(std::string("/test/files/elements/CO2Sensor_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/CO2Sensor_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}

TEST_F(MsgCreatorTest, createMessageThermalSensor)
{
  init(std::string("/test/files/elements/element_ex_ThermalSensor.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::ThermalSensorMsg msg = MessageCreator::createMessage<stdr_msgs::ThermalSensorMsg>(root_node_, id_);
  init(std::string("/test/files/elements/ThermalSensor_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/ThermalSensor_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}

TEST_F(MsgCreatorTest, createMessageSoundSensor)
{
  init(std::string("/test/files/elements/element_ex_SoundSensor.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::SoundSensorMsg msg = MessageCreator::createMessage<stdr_msgs::SoundSensorMsg>(root_node_, id_);
  init(std::string("/test/files/elements/SoundSensor_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/SoundSensor_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}

TEST_F(MsgCreatorTest, createMessageKinematic)
{
  init(std::string("/test/files/elements/element_ex_Kinematic.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::KinematicMsg msg = MessageCreator::createMessage<stdr_msgs::KinematicMsg>(root_node_, id_);
  init(std::string("/test/files/elements/Kinematic_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/Kinematic_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}

TEST_F(MsgCreatorTest, createMessageRobot)
{
  init(std::string("/test/files/elements/element_ex_Robot.xml"));
  XmlParser::parse(utils_file_, root_node_);
  stdr_msgs::RobotMsg msg = MessageCreator::createMessage<stdr_msgs::RobotMsg>(root_node_, id_);
  init(std::string("/test/files/elements/Robot_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/Robot_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}
/*TEST_F(MsgCreatorTest, createMessagePose2D)
{
  init(std::string("/test/files/elements/element_ex_Pose2D.xml"));
  XmlParser::parse(utils_file_, root_node_);
  geometry_msgs::Pose2D msg;
  msg = MessageCreator::createMessage<geometry_msgs::Pose2D>(root_node_, id_);
  init(std::string("/test/files/elements/pose2D_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/elements/pose2D_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}
*/
/*TEST_F(MsgCreatorTest, createMessagePoint)
{
  init(std::string("/test/files/nodes/point.xml"));
  XmlParser::parse(utils_file_, root_node_);
  geometry_msgs::Point msg = MessageCreator::createMessage<geometry_msgs::Point>(root_node_, id_);
  init(std::string("/test/files/nodes/point_message.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);
  init("/test/files/nodes/point_message_exp.xml");
  std::string expected_element = readFile(utils_file_);
  EXPECT_STREQ(element.c_str(), expected_element.c_str());
 
}*/
}  // namespace stdr_parser
