/******************************************************************************
   STDR Simulator - Simple Two DImensional Robot Simulator
   Copyright (C) 2013 STDR Simulator
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
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
   * Eleni Nisioti, elennisioti@auth.gr
******************************************************************************/

#include <gtest/gtest.h>
#include "stdr_parser/stdr_yaml_parser.h"
#include <fstream> 
namespace stdr_parser
{

/**
 * @class YamlParserTest
 * @brief Basic Test Fixture for testing YamlParser
 */
class YamlParserTest : public ::testing::Test
{
 protected:
  YamlParserTest()
  {
  }

  void SetUp()
  { 
     
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
    std::ostringstream output_stream;
    std::ifstream inFile (filename.c_str());
    std::string line;
    while( getline(inFile, line) ) {
        output_stream << line << std::endl;
    } 
    std::string content = output_stream.str().substr(0, output_stream.str().size()-1);
    return content;

  }
  // Accessors for private methods of XmlParser
  void parseLow(const YAML::Node& node, Node* n)
  {
    YamlParser::parseLow(node, n);
  }
  

  // Variables
  Node* root_node_;
  std::string robot_file_;
  std::string dump_file_;

};

TEST_F(YamlParserTest, parseTestRobot1)
{
  init(std::string("/test/files/too_simple_robot.yaml"));

  // parse the test file
  EXPECT_NO_THROW(YamlParser::parse(robot_file_, root_node_));

  EXPECT_EQ(root_node_->elements.size(), 1);

}

TEST_F(YamlParserTest, parseAlternateResourceLocation)
{
  init(std::string("/test/files/too_simple_robot.yaml"));

  // parse the correct test file
  EXPECT_NO_THROW(YamlParser::parse(robot_file_, root_node_));


  TearDown();
  init(std::string("/test/files/test_robot_3.yaml"));

  // parse the incorrect test file
  EXPECT_THROW(YamlParser::parse(robot_file_, root_node_), ParserException);
}

//random output of this test
TEST_F(YamlParserTest, parse)
{
    init(std::string("/test/files/test_robot_1.yaml"));
    
    YamlParser::parse(robot_file_,root_node_);

    //get string by calling printParsedFile
    std::string indent="";
    std::ostringstream output_stream;
    std::string tree = root_node_->printParsedFile(indent, output_stream);


    //read expected tree
    init(std::string("/test/files/test_robot_1_tree_yaml.txt"));
    std::string expected_tree = readFile(robot_file_);
    EXPECT_STREQ(expected_tree.c_str(), tree.c_str());
}

//random output of this test
TEST_F(YamlParserTest, parseLow)
{
    init(std::string("/test/files/test_robot_1.yaml"));
    std::string path = robot_file_;
    std::ifstream fin(path.c_str());
    
    if (!fin.good()) {
      throw ParserException("Failed to load '"+ robot_file_ +"', no such file!");
    }

#ifdef HAVE_NEW_YAMLCPP
    YAML::Node doc = YAML::Load(fin);
#else
    YAML::Parser parser(fin);
    YAML::Node doc;
    parser.GetNextDocument(doc);
#endif

    root_node_->file_origin = robot_file_;
#ifndef HAVE_NEW_YAMLCPP
    root_node_->file_row = doc.GetMark().line;
#endif

    root_node_->file_origin = robot_file_;
#ifndef HAVE_NEW_YAMLCPP
    root_node_->file_row = doc.GetMark().line;
#endif

    parseLow(doc,root_node_);


    //get string by calling printParsedFile
    std::string indent="";
    std::ostringstream output_stream;
    std::string tree = root_node_->printParsedFile(indent, output_stream);

    //read expected tree
    init(std::string("/test/files/test_robot_1_tree_parselow_yaml.txt"));
    std::string expected_tree = readFile(robot_file_);
    EXPECT_STREQ(expected_tree.c_str(), tree.c_str());
    

}








}  // namespace stdr_parser
