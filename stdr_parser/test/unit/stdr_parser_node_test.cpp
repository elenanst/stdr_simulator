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
 * @class ParserNodeTest
 * @brief Basic Test Fixture for testing XmlParser
 */
class ParserNodeTest : public ::testing::Test
{

protected:
  void init(const std::string& filename)
  {
    utils_file_ = ros::package::getPath("stdr_parser") +
                    "/test/files/Node/" +
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
    std::ifstream inFile (file.c_str());
    std::string line;
    while( getline(inFile, line) ) {
        output_stream << line << std::endl;
    } 
    std::string content = output_stream.str().substr(0, output_stream.str().size()-1);
    return content;
  }


 std::string utils_file_;
 Node* root_node_;
 
};

TEST_F(ParserNodeTest, getTreeStructureNoIndent)
{

  init(std::string("Noise.xml"));
  std::ostringstream output_stream;
  
  //parse file into node
  XmlParser::parse(utils_file_, root_node_);
  std::string indent = "" ;

  //get the xml content of file into string
  root_node_->getTreeStructure(indent, output_stream);
  std::string tree = output_stream.str();
 
  //get expected output 
  init("Noise_tree.txt");
  std::string expected_tree = readFile(utils_file_);

  //test if getTreeStructure prints as expected
  EXPECT_STREQ(expected_tree.c_str(), tree.c_str());

}

TEST_F(ParserNodeTest,getTreeStructureIndent)
{
  init(std::string("Noise.xml"));
  std::ostringstream output_stream;
  
  //parse file into node
  XmlParser::parse(utils_file_, root_node_);
  std::string indent = "&" ;

  //get the xml content of file into string
  root_node_->getTreeStructure(indent, output_stream);
  std::string tree = output_stream.str();

  //get expected output 
  init("Noise_tree_Indent.txt");
  std::string expected_tree = readFile(utils_file_);

  //test if getTreeStructure prints as expected
  EXPECT_STREQ(expected_tree.c_str(), tree.c_str());
}

TEST_F(ParserNodeTest, increasePriority)
{
  init(std::string("CO2Sensor.xml"));

  //parse file into node
  XmlParser::parse(utils_file_, root_node_);

  //get current priorities
  int length =  root_node_->elements.size();
  int* priorities = new int[length];
  int priority = root_node_->priority;
  for(unsigned int i = 0 ; i < root_node_->elements.size() ; i++)
  {
      priorities[i] = root_node_->elements[i]->priority;
  }

  //increase priority of node
  root_node_->increasePriority();

  //test priority of node
  EXPECT_EQ(root_node_->priority, priority +1 );

  //test priorities of children of node
  for(unsigned int i = 0 ; i < root_node_->elements.size() ; i++)
  {
      EXPECT_EQ(root_node_->elements[i]->priority,priorities[i]+1);
  }
}

TEST_F(ParserNodeTest, getTagRightTag)
{
  init(std::string("LaserSensor.xml"));

  //parse file into node
  XmlParser::parse(utils_file_, root_node_);

  //get indexes of tag "laser_specifications" 
  std::vector<int> indexes =
   root_node_->elements[0]->getTag("laser_specifications");

  //check if number of indexes is correct
  EXPECT_EQ(indexes.size(),1);
  
  //check if index is correct
  EXPECT_EQ(indexes.at(0),0);
}

TEST_F(ParserNodeTest, getTagMultipleOccurence)
{
  init(std::string("LaserSensor_multiple.xml"));

  //parse file into node
  XmlParser::parse(utils_file_, root_node_);

  //get indexes of tag "max_angle" 
  std::vector<int> indexes =
   root_node_->elements[0]->elements[0]->getTag("max_angle");

  //check if number of indexes is correct
  EXPECT_EQ(indexes.size(),2);

  //check if indexes are correct
  EXPECT_EQ(indexes.at(0),2);
  EXPECT_EQ(indexes.at(1),3);
}

TEST_F(ParserNodeTest, getTagEmpty)
{
  init(std::string("SonarSensor.xml"));

  //parse file into node
  XmlParser::parse(utils_file_, root_node_);

  //get indexes of tag "max_angle" 
  std::vector<int> indexes =
   root_node_->elements[0]->getTag("theta");

  //check if number of indexes is correct
  EXPECT_EQ(indexes.size(),0);
}

TEST_F(ParserNodeTest, unallocateChildren)
{
  init(std::string("Noise.xml"));

  //parse file into node
  XmlParser::parse(utils_file_, root_node_);

  //unallocate children of node
  unallocateChildren(root_node_);

  //check if children have been unallocated
  EXPECT_TRUE(root_node_->elements.empty());
}

//not tested properly
TEST_F(ParserNodeTest,checkForFilenameTrue)
{
  init(std::string("test_robot_1.xml"));

  //parse file into node
  XmlParser::parse(utils_file_, root_node_);


  std::string filename = "robot" ;

  //check if element has tag robot
  EXPECT_TRUE(root_node_->checkForFilename(filename));
}

}
