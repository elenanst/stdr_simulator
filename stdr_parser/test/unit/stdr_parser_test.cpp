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

    
  }

  void init(const std::string& filename)
  {
    
  }

  // Accessors for private methods of XmlParser
  void parse(std::string file_name);
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
  std::string robot_file_;
  std::string dump_file_;

};

TEST_F(ParserTest, parseNoThrowXml)
{
  init(std::string("/test/files/test_robot_1.xml"));

  // parse the test file
  EXPECT_NO_THROW(parse(robot_file_, root_node_));

}

TEST_F(ParserTest, parseNoThrowYaml)
{
  init(std::string("/test/files/test_robot_1.yaml"));

  // parse the test file
  EXPECT_NO_THROW(parse(robot_file_, root_node_));

}


}
