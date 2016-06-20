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
   * Eleni Nisioti, elennisi@auth.gr
******************************************************************************/

#include <gtest/gtest.h>
#include "stdr_parser/stdr_parser.h"
#include <fstream> 
namespace stdr_parser
{

/**
 * @class XmlParserTest
 * @brief Basic Test Fixture for testing XmlParser
 */
class ParserTest : public ::testing::Test
{
 protected:
  ParserTest()
  {
  }

  void SetUp()
  { 

 
  }
  virtual void TearDown()
  {

    Validator::clearSpecs();
    delete root_node_;
    
  }

  void init(const std::string& filename)
  {
    utils_file_ = ros::package::getPath("stdr_parser") +
                    filename;
    root_node_ = new Node(); 
  }
  
  //read file into string
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

  // Accessors for private methods of XmlParser
  void parse(std::string file_name)
  {
    Parser::parse(file_name);
  }
  
  bool eliminateFilenames(Node* n)
  {
    return Parser::eliminateFilenames(n);
  }

  bool mergeNodes(Node* n)
  {
    return Parser::mergeNodes(n);
  }
  
  void mergeNodesValues(Node* n)
  {
     Parser::mergeNodesValues(n);
  }
  // Variables
  Node* root_node_;
  std::string utils_file_;
  
};


TEST_F(ParserTest, parseNoThrowXml)
{
  init(std::string("/test/files/test_robot_1.xml"));
  
  // parse the test file
  EXPECT_NO_THROW(parse(utils_file_));

}

TEST_F(ParserTest, parseNoThrowYaml)
{
  init(std::string("/test/files/test_robot_1.yaml"));

  // parse the test file
  EXPECT_NO_THROW(parse(utils_file_));

}

TEST_F(ParserTest, saveMessageXml)
{
  init(std::string("/test/files/test_robot_1.xml"));

  //save the test file
  EXPECT_NO_THROW(parse(utils_file_));

}

TEST_F(ParserTest, saveMessageYaml)
{
  init(std::string("/test/files/test_robot_1.yaml"));

  //save the test file
  EXPECT_NO_THROW(parse(utils_file_));

}

TEST_F(ParserTest, eliminateFilenamesNoThrow)
{
  init(std::string("/test/files/test_robot_1.xml"));
  
  //parse the test file to root node
  XmlParser::parse(utils_file_,root_node_);

  //eliminate tags "filename" from root node
  EXPECT_NO_THROW(eliminateFilenames(root_node_));
}

TEST_F(ParserTest, eliminateFilenames)
{
  init(std::string("/test/files/test_robot_1.xml"));

  //parse the test file to root node
  XmlParser::parse(utils_file_,root_node_);

  //eliminate Filenames
  while(!eliminateFilenames(root_node_));
  std::string indent = "";
  std::ostringstream output_stream;
  std::string tree = root_node_->printParsedXml(root_node_, indent, output_stream);

  //read expected element
  init("/test/files/Robot_eliminated_filenames.txt");
  std::string expected_tree = readFile(utils_file_);
  EXPECT_STREQ(expected_tree.c_str(), tree.c_str());
}

TEST_F(ParserTest, mergeNodesNoThrow)
{
  init(std::string("/test/files/test_robot_1.xml"));

  //parse the test file to root node
  XmlParser::parse(utils_file_,root_node_);

  //merge nodes
  EXPECT_NO_THROW(mergeNodes(root_node_));
}

TEST_F(ParserTest, mergeNodesRobot)
{
  init(std::string("/test/files/stdr_multiple_allowed.xml"));
  Validator::parseMergableSpecifications(utils_file_);

  init(std::string("/test/files/Robot_merge_nodes.xml"));
  
  //parse the test file to root node
  XmlParser::parse(utils_file_,root_node_);
   
  //merge nodes
  while(!mergeNodes(root_node_));
  std::string indent = "";
  std::ostringstream output_stream;
  std::string tree = root_node_->printParsedXml(root_node_, indent, output_stream);

  //read expected element
  init("/test/files/Robot_merged_nodes.txt");
  std::string expected_tree = readFile(utils_file_);
  EXPECT_STREQ(expected_tree.c_str(), tree.c_str());
}


TEST_F(ParserTest, mergeNodesValuesNoThrow)
{
  init(std::string("/test/files/test_robot_1.xml"));
  
  //parse the test file to root node
  XmlParser::parse(utils_file_,root_node_);

  //merge values of nodes
  EXPECT_NO_THROW(mergeNodesValues(root_node_));
}


TEST_F(ParserTest, mergeNodesValuesRobot)
{
  init(std::string("/test/files/stdr_multiple_allowed.xml"));
  Validator::parseMergableSpecifications(utils_file_);

  init(std::string("/test/files/Robot_merge_nodesvalues.xml"));
  
  //parse the test file to root node
  XmlParser::parse(utils_file_,root_node_);
  
  //merge nodes
  mergeNodesValues(root_node_);
  std::string indent = "";
  std::ostringstream output_stream;
  std::string tree = root_node_->printParsedXml(root_node_, indent, output_stream);

  //read expected element
  init("/test/files/Robot_merged_nodesValues.txt");
  std::string expected_tree = readFile(utils_file_);
  EXPECT_STREQ(expected_tree.c_str(), tree.c_str());
}


TEST_F(ParserTest, createMessageNoThrow)
{
  init(std::string("/test/files/test_robot_1.xml"));
  stdr_msgs::RobotMsg msg;

  //create a mesage from file
  EXPECT_NO_THROW( msg = Parser::createMessage<stdr_msgs::RobotMsg>(utils_file_)); 
}

TEST_F(ParserTest, createMessageRobot)
{
  init(std::string("/test/files/test_robot_1.xml"));
  
  //create a mesage from file
  stdr_msgs::RobotMsg msg = Parser::createMessage<stdr_msgs::RobotMsg>(utils_file_);
  

  //get expected message
  init(std::string("/test/files/test_robot_1_exp.xml"));
  std::string expected_element = readFile(utils_file_);

  //write message to file and read into string
  init(std::string("/test/files/test_robot_1_temp.xml"));
  XmlFileWriter::messageToFile<>(msg, utils_file_);
  std::string element = readFile(utils_file_);

  //compare output with expected string
  EXPECT_STREQ(expected_element.c_str(), element.c_str());
}
}
