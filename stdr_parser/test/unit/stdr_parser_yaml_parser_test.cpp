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

  virtual void TearDown()
  {
    delete root_node_;
    remove(dump_file_.c_str());
  }

  void init(const std::string& filename)
  {
    robot_file_ = ros::package::getPath("stdr_parser") +
                  "/test/files/YamlParser/" +
                    filename;

    root_node_ = new Node();  //auta na pane sto setup?
    root_node_->tag = "STDR_Parser_Root_Node";
  }
 
  void initNode(void)
  {
    expected_node_ = new Node();
    Node* tag1 = new Node();
    tag1->tag = "noise";
    expected_node_->elements.push_back(tag1);
    Node* tag2 = new Node();
    tag2->tag = "noise_specifications";
    tag1->elements.push_back(tag2);
    Node* tag3 = new Node();
    tag3->tag = "noise_mean";
    tag2->elements.push_back(tag3);
    Node* tag4 = new Node();
    tag4->tag = "noise_std";
    tag2->elements.push_back(tag4);
    Node* value1 = new Node();
    value1->value = "2";
    tag3->elements.push_back(value1);
    Node* value2 = new Node();
    value2->value = "0";
    tag4->elements.push_back(value2);
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

  bool compareNodes(Node* expected, Node* node, bool* result)
  {
    std::vector<Node*> elements = node->elements;
    std::vector<Node*> elements_exp = expected->elements;
    std::vector<std::string> expected_tags;
    std::vector<std::string> expected_values;
    for(int i = 0; i < elements_exp.size(); i++)
    {
      if(elements_exp.at(i)->tag != "")
      {
        expected_tags.push_back(elements_exp.at(i)->tag);
      }
    }
    for(int i = 0; i < elements_exp.size(); i++)
    {
       if(elements_exp.at(i)->value != "")
       {
          expected_values.push_back(elements_exp.at(i)->value);
       }
    }
    int hits = 0;
    for(int i = 0; i < elements.size(); i++)
    {
       int pos;
       
       if(elements[i]->tag != "")
       {
        
         pos = find(expected_tags.begin(), expected_tags.end(),
                elements[i]->tag) - expected_tags.begin();
         if(pos >= expected_tags.size())
         {
           *result = *result && false;
         }
         else
         {
           hits +=1;
         }
       }
       else
       {
         pos = find(expected_values.begin(), expected_values.end(),
                 elements[i]->value) - expected_values.begin();
         if(pos >= expected_values.size())
         {
           *result = *result && false;
         }
         else
         {
           hits +=1;
         }
       }
       
       compareNodes(elements[i], elements_exp.at(pos), result);
    }
    if(hits == elements.size())
    {
      *result = *result && true;
    }
    else
    {
      *result = *result && false;
    }
 }
  

  // Variables
  Node* root_node_;
  std::string robot_file_;
  std::string dump_file_;
  Node* expected_node_;

};

TEST_F(YamlParserTest, parseTestRobot1)
{
  init(std::string("too_simple_robot.yaml"));

  // parse the test file
  EXPECT_NO_THROW(YamlParser::parse(robot_file_, root_node_));

  EXPECT_EQ(root_node_->elements.size(), 1);

}

TEST_F(YamlParserTest, parseAlternateResourceLocation)
{
  init(std::string("too_simple_robot.yaml"));

  // parse the correct test file
  EXPECT_NO_THROW(YamlParser::parse(robot_file_, root_node_));


  TearDown();
  init(std::string("test_robot_3.yaml"));

  // parse the incorrect test file
  EXPECT_THROW(YamlParser::parse(robot_file_, root_node_), ParserException);
}

//random output of this test
TEST_F(YamlParserTest, parse)
{
    init(std::string("Noise_element_exp.yaml"));
    
    YamlParser::parse(robot_file_,root_node_);
    std::string indent="";
    std::ostringstream output_stream;
    root_node_->getTreeStructure(indent, output_stream);
    std::string tree = output_stream.str();
    initNode();
    
    bool result = true;
    compareNodes(expected_node_, root_node_, &result);
    EXPECT_TRUE(result);
}

//random output of this test
TEST_F(YamlParserTest, parseLow)
{
    init(std::string("Noise_element_exp.yaml"));
    std::string path = robot_file_;
    std::ifstream fin(path.c_str());
    
    if (!fin.good()) {
      throw ParserException("Failed to load '"+ robot_file_ +
          "', no such file!");
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
    root_node_->getTreeStructure(indent, output_stream);
    std::string tree = output_stream.str();

    //read expected tree
    initNode();
    
    bool result = true;
    compareNodes(expected_node_, root_node_, &result);
    EXPECT_TRUE(result);
    

}








}  // namespace stdr_parser
