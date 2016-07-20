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
#include "stdr_parser/stdr_parser_validator.h"


namespace stdr_parser
{


/**
 * @class MsgCreatorTest
 * @brief Basic Test Fixture for testing MsgCreator
 */
class MsgCreatorTest : public ::testing::Test
{

 protected:
  MsgCreatorTest()
  {
  }

  virtual void TearDown()
  {
    delete root_node_;
  }

  //initialize members
  void init(const std::string& filename)
  {
    utils_file_ = ros::package::getPath("stdr_parser") +
                    "/test/files/MsgCreator/" +
                      filename;
    root_node_ = new Node(); 
    id_ = 0;
  }

  //initialize temporary file
  void initTempFile(const std::string& type)
  {
   std::string filename = "/tmp/tmpfileXXXXXX" + type;
   temp_file_ = strdup(filename.c_str());
   mkstemp(temp_file_);
  }
 
  //read file into string
  std::string readFile(const std::string& file)
  {
    std::ifstream ifs(file.c_str());
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
    content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
    return content;
  }

  //members of test
  std::string utils_file_;
  Node* root_node_;
  unsigned int id_;
  char* temp_file_;
  
};


TEST_F(MsgCreatorTest, createMessageNoise)
{
  init(std::string("Noise.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::Noise msg =
   MessageCreator::createMessage<stdr_msgs::Noise>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);

  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(MsgCreatorTest, createMessageFootprint)
{
  init(std::string("Footprint.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::FootprintMsg msg =
   MessageCreator::createMessage<stdr_msgs::FootprintMsg>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);

  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(MsgCreatorTest, createMessageLaserSensor)
{
  init(std::string("LaserSensor.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::LaserSensorMsg msg =
   MessageCreator::createMessage<stdr_msgs::LaserSensorMsg>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);
  
  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(MsgCreatorTest, createMessageSonarSensor)
{
  init(std::string("SonarSensor.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::SonarSensorMsg msg =
   MessageCreator::createMessage<stdr_msgs::SonarSensorMsg>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);

  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());

}

TEST_F(MsgCreatorTest, createMessageRfidSensor)
{
  init(std::string("RfidSensor.xml"));
  std::string expected_element = readFile(utils_file_);
 
  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::RfidSensorMsg msg =
   MessageCreator::createMessage<stdr_msgs::RfidSensorMsg>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);
  
  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(MsgCreatorTest, createMessageCO2Sensor)
{
  init(std::string("CO2Sensor.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::CO2SensorMsg msg =
   MessageCreator::createMessage<stdr_msgs::CO2SensorMsg>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);

  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str()); 
}

TEST_F(MsgCreatorTest, createMessageThermalSensor)
{
  init(std::string("ThermalSensor.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::ThermalSensorMsg msg =
   MessageCreator::createMessage<stdr_msgs::ThermalSensorMsg>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);

  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(MsgCreatorTest, createMessageSoundSensor)
{
  init(std::string("SoundSensor.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::SoundSensorMsg msg = 
    MessageCreator::createMessage<stdr_msgs::SoundSensorMsg>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);

  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

TEST_F(MsgCreatorTest, createMessageKinematic)
{
  init(std::string("Kinematic.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::KinematicMsg msg =
     MessageCreator::createMessage<stdr_msgs::KinematicMsg>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);

  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str()); 
}

TEST_F(MsgCreatorTest, createMessageRobot)
{
  init(std::string("Robot.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  //create message from Node
  stdr_msgs::RobotMsg msg =
     MessageCreator::createMessage<stdr_msgs::RobotMsg>(root_node_, id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);
  
  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str()); 
}

 
TEST_F(MsgCreatorTest, createMessagePose2D)
{
  init(std::string("Pose2D.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  std::vector<int> indexes;
  indexes = root_node_->getTag("pose");

  //create message from Node
  geometry_msgs::Pose2D msg =
    MessageCreator::createMessage<geometry_msgs::Pose2D>(root_node_->elements[indexes[0]], id_);

  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);

  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}


TEST_F(MsgCreatorTest, createMessagePoint)
{
  init(std::string("Point.xml"));
  std::string expected_element = readFile(utils_file_);

  //read xml file into Node
  XmlParser::parse(utils_file_, root_node_);

  std::vector<int> indexes;
  indexes = root_node_->getTag("point");

  //create message from Node
  geometry_msgs::Point msg =
   MessageCreator::createMessage<geometry_msgs::Point>(root_node_->elements[indexes[0]], id_);


  //write message to file and read into string
  initTempFile(".xml");
  XmlFileWriter::messageToFile<>(msg, temp_file_);
  std::string element = readFile(utils_file_);
  
  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}

}  // namespace stdr_parser
