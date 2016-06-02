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
   * Christos Zalidis, zalidis@gmail.com
******************************************************************************/

#include <gtest/gtest.h>
#include "stdr_parser/stdr_xml_parser.h"
#include <fstream> 
namespace stdr_parser
{

/**
 * @class XmlParserTest
 * @brief Basic Test Fixture for testing XmlParser
 */
class XmlParserTest : public ::testing::Test
{
 protected:
  XmlParserTest()
  {
  }

  void SetUp()
  { 
    std::string dump_file_ = ros::package::getPath("stdr_parser") +
                    "/test/files/dump_file.txt"; 
   
 
  }
  virtual void TearDown()
  {
    delete root_node_;
    remove(dump_file_.c_str());
    
  }

  void init(const std::string& filename)
  {
    robot_file_ = ros::package::getPath("stdr_parser") +
                    filename;

    root_node_ = new Node();  //auta na pane sto setup?
    root_node_->tag = "STDR_Parser_Root_Node";
  }

  std::string readFile(const std::string& filename)
  {
      std::string file = ros::package::getPath("stdr_parser") +
                    filename;
      std::ifstream t(file.c_str());
      std::string str;
      t.seekg(0, std::ios::end);   
      str.reserve(t.tellg());
      t.seekg(0, std::ios::beg);
      str.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
      return str;

  }
  // Accessors for private methods of XmlParser
  void parseLow(TiXmlNode* node, Node* n)
  {
    XmlParser::parseLow(node, n);
  }
  

  // Variables
  Node* root_node_;
  std::string robot_file_;
  std::string dump_file_;

};

TEST_F(XmlParserTest, parseTestRobot1)
{
  init(std::string("/test/files/test_robot_1.xml"));

  // parse the test file
  EXPECT_NO_THROW(XmlParser::parse(robot_file_, root_node_));

  EXPECT_EQ(root_node_->elements.size(), 1);

  //root_node->printParsedXml(root_node, "--");
}

TEST_F(XmlParserTest, parseAlternateResourceLocation)
{
  init(std::string("/test/files/test_robot_2.xml"));

  // parse the correct test file
  EXPECT_NO_THROW(XmlParser::parse(robot_file_, root_node_));


  TearDown();
  init(std::string("/test/files/test_robot_3.xml"));

  // parse the incorrect test file
  EXPECT_THROW(XmlParser::parse(robot_file_, root_node_), ParserException);
}

TEST_F(XmlParserTest, parseLow)
{
    init(std::string("/test/files/test_robot_1.xml"));
    TiXmlDocument doc;
    doc.SetTabSize(2);
    doc.LoadFile(robot_file_.c_str());
    root_node_->file_origin = robot_file_;
    root_node_->file_row = doc.Row();
    parseLow(&doc,root_node_);
    std::string indent="";
    std::ostringstream output_stream;
    std::string tree = root_node_->printParsedXml(root_node_, indent);
    ROS_INFO(tree.c_str());
    std::string expected_tree = readFile(std::string("/test/files/test_robot_1_tree.txt"));
    ROS_INFO(expected_tree.c_str());
    EXPECT_STREQ(tree.c_str(), expected_tree.c_str());
    

}



}  // namespace stdr_parser
