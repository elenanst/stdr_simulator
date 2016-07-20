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

  virtual void TearDown()
  {
    delete root_node_;
  
  }

  void init(const std::string& filename)
  {
    robot_file_ = ros::package::getPath("stdr_parser") +
                   "/test/files/XmlParser/" +
                    filename;

    root_node_ = new Node();  //auta na pane sto setup?
    root_node_->tag = "STDR_Parser_Root_Node";
  }

  std::string readFile(const std::string& filename)
  {
    std::ostringstream output_stream;
    std::ifstream inFile (filename.c_str());
    std::string line;
    while( getline(inFile, line) ) {
        output_stream << line << std::endl;
    } 
    std::string content = output_stream.str().substr(0,
      output_stream.str().size()-1);
    return content;

  }
  // Accessors for private methods of XmlParser
  void parseLow(TiXmlNode* node, Node* n)
  {
    XmlParser::parseLow(node, n);
  }
  

  // Variables
  Node* root_node_;
  std::string robot_file_;
};

TEST_F(XmlParserTest, parseTestRobot1)
{
  init(std::string("test_robot_1.xml"));

  // parse the test file
  EXPECT_NO_THROW(XmlParser::parse(robot_file_, root_node_));

  EXPECT_EQ(root_node_->elements.size(), 1);
}

TEST_F(XmlParserTest, parseAlternateResourceLocation)
{
  init(std::string("test_robot_2.xml"));

  // parse the correct test file
  EXPECT_NO_THROW(XmlParser::parse(robot_file_, root_node_));


  TearDown();
  init(std::string("test_robot_3.xml"));

  // parse the incorrect test file
  EXPECT_THROW(XmlParser::parse(robot_file_, root_node_), ParserException);
}


TEST_F(XmlParserTest, parse)
{
    init(std::string("too_simple_robot.xml"));
    
    XmlParser::parse(robot_file_,root_node_);

    //get string by calling printParsedFile
    std::string indent="";
    std::ostringstream output_stream;
    root_node_->getTreeStructure(indent, output_stream);
    std::string tree = output_stream.str();

    //read expected tree
    init(std::string("too_simple_robot.txt"));
    std::string expected_tree = readFile(robot_file_);
    EXPECT_STREQ(expected_tree.c_str(), tree.c_str());
    

}

TEST_F(XmlParserTest, parseLow)
{
    init(std::string("too_simple_robot.xml"));
    TiXmlDocument doc;
    doc.SetTabSize(2);
    doc.LoadFile(robot_file_.c_str());
    root_node_->file_origin = robot_file_;
    root_node_->file_row = doc.Row();

    
    parseLow(&doc,root_node_);

    //get string by calling printParsedFile
    std::string indent="";
    std::ostringstream output_stream;
    root_node_->getTreeStructure(indent, output_stream);
    std::string tree = output_stream.str();

    //read expected tree
    init(std::string("too_simple_robot.txt"));
    std::string expected_tree = readFile(robot_file_);
    EXPECT_STREQ(expected_tree.c_str(), tree.c_str());
    

}



}  // namespace stdr_parser
