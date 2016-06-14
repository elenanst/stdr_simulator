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
#include "stdr_parser/stdr_parser_node.h"
#include "stdr_parser/stdr_xml_parser.h"
#include <fstream> 
namespace stdr_parser
{

/**
 * @class XmlParserTest
 * @brief Basic Test Fixture for testing XmlParser
 */
class ParserNodeTest : public ::testing::Test
{
protected:
  void init(const std::string& filename)
  {
    utils_file_ = ros::package::getPath("stdr_parser") +
                    filename;
    root_node_ = new Node();
  }

  void unallocateChildren(Node* node)
  {
    node->unallocateChildren();
  }

  std::string readFile(const std::string& file)
  {
    std::ostringstream output_stream;
      std::ostringstream output_stream_2;
    std::ifstream inFile (file.c_str());
    std::string line;
    while( getline(inFile, line) ) {
        output_stream << line << std::endl;
    } 
    return output_stream.str();
  }


 std::string utils_file_;
 Node* root_node_;
 
};

TEST_F(ParserNodeTest, printParsedXmlNoIndent)
{
  std::ostringstream output_stream_;
  init(std::string("/test/files/elements/noise_gauss.xml"));
  XmlParser::parse(utils_file_, root_node_);
  std::string indent = "" ;
  std::string tree = root_node_->printParsedXml(root_node_, indent, output_stream_);
  tree+="\n";
  init("/test/files/elements/Noise_tree.txt");
  std::string expected_tree = readFile(utils_file_);
  EXPECT_STREQ(tree.c_str(), expected_tree.c_str());

}

TEST_F(ParserNodeTest, printParsedXmlIndent)
{
  std::ostringstream output_stream_;
  init(std::string("/test/files/elements/noise_gauss.xml"));
  XmlParser::parse(utils_file_, root_node_);
  std::string indent = "&" ;
  std::string tree = root_node_->printParsedXml(root_node_, indent, output_stream_);
  init("/test/files/elements/Noise_tree_Indent.txt");
  std::string expected_tree = readFile(utils_file_);
  EXPECT_STREQ(tree.c_str(), expected_tree.c_str());
}

TEST_F(ParserNodeTest, increasePriority)
{
  init(std::string("/test/files/elements/element_ex_CO2Sensor.xml"));
  XmlParser::parse(utils_file_, root_node_);
  int priority = root_node_->priority;;
  int length =  root_node_->elements.size();
  int* priorities= new int[length];
  for(unsigned int i = 0 ; i < root_node_->elements.size() ; i++)
  {
      priorities[i] = root_node_->elements[i]->priority;
  }
  root_node_->increasePriority();
  EXPECT_EQ(root_node_->priority, priority +1 );
  for(unsigned int i = 0 ; i < root_node_->elements.size() ; i++)
  {
      EXPECT_EQ(root_node_->elements[i]->priority,priorities[i]+1);
  }
}

TEST_F(ParserNodeTest, getTagRightTag)
{
  init(std::string("/test/files/elements/element_ex_LaserSensor.xml"));
  XmlParser::parse(utils_file_, root_node_);
  std::vector<int> indexes = root_node_->elements[0]->getTag("laser_specifications");
  EXPECT_EQ(indexes.size(),1);
  EXPECT_EQ(indexes.at(0),0);
}

TEST_F(ParserNodeTest, getTagMultipleOccurence)
{
  init(std::string("/test/files/elements/element_ex_LaserSensor_multiple.xml"));
  XmlParser::parse(utils_file_, root_node_);
  std::vector<int> indexes = root_node_->elements[0]->elements[0]->getTag("max_angle");
  EXPECT_EQ(indexes.size(),2);
  EXPECT_EQ(indexes.at(0),2);
  EXPECT_EQ(indexes.at(1),3);
}

TEST_F(ParserNodeTest, getTagEmpty)
{
  init(std::string("/test/files/elements/element_ex_SonarSensor.xml"));
  XmlParser::parse(utils_file_, root_node_);
  std::vector<int> indexes = root_node_->elements[0]->getTag("theta");
  EXPECT_EQ(indexes.size(),0);
}

//provlima: kaleitai polles fores h unallocateChildren
TEST_F(ParserNodeTest, unallocateChildren)
{
  init(std::string("/test/files/elements/noise_gauss.xml"));
  XmlParser::parse(utils_file_, root_node_);
  unallocateChildren(root_node_);
  EXPECT_EQ(root_node_->elements.size(),0);
}
/* den eimai sigouri ti kanei auti i sunartisi
TEST_F(ParserNodeTest,checkForFilenameTrue)
{
  init(std::string("/test/files/test_robot_1.xml"));
  XmlParser::parse(utils_file_, root_node_);
  std::string filename = "robots/too_simple_robot.xml" ;
  std::string tag = root_node_->value;
  ROS_INFO("tag is %s", tag.c_str()  );
  EXPECT_TRUE(root_node_->elements[0]->elements[0]->checkForFilename(filename));
}
*/
}
