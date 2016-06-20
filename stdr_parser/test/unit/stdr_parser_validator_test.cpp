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
#include "stdr_parser/stdr_parser_tools.h"
#include "stdr_parser/stdr_parser_validator.h"
#include "stdr_parser/stdr_parser_node.h"
#include <typeinfo>
#include <vector>


namespace stdr_parser
{


/**
 * @class ValidatorTest
 * @brief Basic Test Fixture for testing Validator
 */
class ValidatorTest : public ::testing::Test
{
 protected:
  ValidatorTest()
  {
  }

  virtual void TearDown()
  {
    Validator::clearSpecs();
  }

  void init(const std::string& filename)
  {
    specs_file_ = ros::package::getPath("stdr_parser") +
                    filename;
    dummy_node_ = new Node();
  }

  TiXmlDocument loadStdrSpecifications(void)
  {
    init(std::string("/test/files/stdr_specifications.xml"));
    std::string path = extractDirname(specs_file_);
    TiXmlDocument test_doc;
    bool loadOkay = test_doc.LoadFile(specs_file_.c_str());
    if (!loadOkay)
    {
      std::string error =    
      std::string("Failed to load specifications file.\nShould be at '") + 
      path + std::string("'\nError was") + std::string(test_doc.ErrorDesc());
      throw ParserException(error);
    }
    return test_doc;
  }
   
  std::string readFile(const std::string& filename)
  {
     std::string file = ros::package::getPath("stdr_parser") +
                    filename;
     std::ifstream ifs(file.c_str());
     std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
     content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
     return content;
  }

  std::string mapToString(const std::map<std::string,ElSpecs>& specs_map)
  {
    std::ostringstream output_stream;
    std::string output ;
    for(std::map<std::string,ElSpecs>::const_iterator it = specs_map.begin();
    it != specs_map.end(); ++it)
    {
      std::string name = it->first;
      ElSpecs elspecs = it->second;
      output_stream << name  << elspecs;

    }

    return output_stream.str().c_str();

  }


  // Accessors for private methods of Validator
  std::map<std::string,ElSpecs> parseSpecifications(TiXmlNode* node)
  {
    return Validator::parseSpecifications(node);
  }

  void validityAllowedCheck(std::string file_name, Node* n)
  {
    Validator::validityAllowedCheck(file_name,n);
  }
  
  void validityRequiredCheck(std::string file_name, Node* n)
  {
    Validator::validityRequiredCheck(file_name,n);
  }

  void validate(std::string file_name, Node* n)
  {
    Validator::validate(file_name,n);
  }

  // Variables
  std::string specs_file_;
  Node* dummy_node_;

};

TEST_F(ValidatorTest, parseMergableSpecificationsNoThrow)
{
  init(std::string("/test/files/stdr_multiple_allowed.xml"));

  //parse stdr_multiple_allowed.xml
  EXPECT_NO_THROW(Validator::parseMergableSpecifications(specs_file_));

}



TEST_F(ValidatorTest, parseMergableSpecificationsRightTags)
{
  init(std::string("/test/files/stdr_multiple_allowed.xml"));

  //parse stdr_multiple_allowed.xml to get non_mergable_tags
  std::set<std::string> non_mergable_tags = Validator::parseMergableSpecifications(specs_file_);

  //fill non_mergable_tags_test as defined in stdr_multiple_allowed.xml
  std::string tags[] = {"robot","laser","sonar","rfid_reader","point","co2_sensor","thermal_sensor","sound_sensor"};
  std::set<std::string> expected(tags, tags + sizeof(tags) / sizeof(tags[0]));
  

  //check if non_mergable_tags are correct
  EXPECT_TRUE(expected == non_mergable_tags);
} 

TEST_F(ValidatorTest,parseSpecificationsNoThrow)
{
   TiXmlDocument test_doc = loadStdrSpecifications();
 
  //parse stdr_speficications.xml
  EXPECT_NO_THROW(parseSpecifications(&test_doc));
}


TEST_F(ValidatorTest,parseSpecificationsRightSpecs)
{
    
  TiXmlDocument test_doc = loadStdrSpecifications();

  //parse specifications
  std::map<std::string,ElSpecs> specs_map = parseSpecifications(&test_doc);

  //convert specification to string
  std::string specs = mapToString(specs_map);

  //load expected string
  std::string expected = readFile(std::string("/test/files/specifications.txt"));
  EXPECT_STREQ(expected.c_str(), specs.c_str());
}

TEST_F(ValidatorTest,validityAllowedCheckValueNoThrow)
{

  TiXmlDocument test_doc = loadStdrSpecifications();
  dummy_node_ = new Node();
  dummy_node_->value = "5";
  std::string file_name = "";

  //check if value node passes validityAllowedCheck
  EXPECT_NO_THROW(validityAllowedCheck(file_name,dummy_node_));
}

TEST_F(ValidatorTest,validityAllowedCheckTagNoThrow)
{
  TiXmlDocument test_doc = loadStdrSpecifications();

   //parse specifications
  std::map<std::string,ElSpecs> specs_map = parseSpecifications(&test_doc);

  dummy_node_ = new Node();
  dummy_node_->tag = "sonar_specifications";
  std::string tags[] = {"cone_angle","max_range","min_range","frequency","frame_id"};
  std::set<std::string> tags_set(tags, tags + sizeof(tags) / sizeof(tags[0]));
  for(std::set<std::string>::const_iterator it = tags_set.begin(); it != tags_set.end(); ++it)
  {
    Node* new_node=new Node();
    new_node->tag=*it;
    dummy_node_->elements.push_back(new_node);
  }
  std::string file_name="";
  //check if tag node passes validityAllowedCheck
  EXPECT_NO_THROW(validityAllowedCheck(file_name,dummy_node_));
}


TEST_F(ValidatorTest,validityAllowedCheckTagThrow)
{
  TiXmlDocument test_doc = loadStdrSpecifications();
  dummy_node_ = new Node();
  dummy_node_->tag = "sonar_specifications";
  std::string tags[] = {"cone_angle","max_range","min_range","frequency","num_rays"};
  std::set<std::string> tags_set(tags, tags + sizeof(tags) / sizeof(tags[0]));
  for(std::set<std::string>::const_iterator it = tags_set.begin(); it != tags_set.end(); ++it)
  {
    Node* new_node = new Node();
    new_node->tag =*it;
    dummy_node_->elements.push_back(new_node);
  }
  std::string file_name = "";
  //check if tag node, whose elements include not allowed tags, fails to pass validityAllowedCheck
  EXPECT_THROW(validityAllowedCheck(file_name,dummy_node_),ParserException);
}

TEST_F(ValidatorTest,validityAllowedCheckTagRecThrow)
{
  TiXmlDocument test_doc = loadStdrSpecifications();
  dummy_node_ = new Node();
  dummy_node_->tag = "environment";
  std::string tags[] = {"map","robot","rfid_tag"};
  std::set<std::string> tags_set(tags, tags + sizeof(tags) / sizeof(tags[0]));
  for(std::set<std::string>::const_iterator it = tags_set.begin(); it != tags_set.end(); ++it)
  {
    Node* new_node = new Node();
    new_node->tag = *it;
    dummy_node_->elements.push_back(new_node);
  }
  Node* new_node = new Node();
  new_node->tag = "image";
  dummy_node_->elements.at(0)->elements.push_back(new_node);
  std::string file_name = "";
  //check if tag node with one element, whose elements include not allowed tags, fails to pass validityAllowedCheck
  EXPECT_THROW(validityAllowedCheck(file_name,dummy_node_),ParserException);
}

TEST_F(ValidatorTest,validityRequiredCheckValueNoThrow)
{
  TiXmlDocument test_doc = loadStdrSpecifications();
  dummy_node_ = new Node();
  dummy_node_->value = "5";
  std::string file_name = "";
  //check if value node passes validityRequiredCheck
  EXPECT_NO_THROW(validityRequiredCheck(file_name,dummy_node_));
}

TEST_F(ValidatorTest,validityRequiredCheckTagNoThrow)
{
  init(std::string("/test/files/stdr_specifications.xml"));
  TiXmlDocument test_doc = loadStdrSpecifications();
  EXPECT_NO_THROW(parseSpecifications(&test_doc));
  dummy_node_ = new Node();
  dummy_node_->tag = "kinematic_parameters";
  std::string tags[] = {"a_ux_ux","a_ux_uy","a_ux_w","a_uy_ux","a_uy_uy","a_uy_w","a_w_ux","a_w_uy","a_w_w","a_g_ux","a_g_uy","a_g_w"};
  std::set<std::string> tags_set(tags, tags + sizeof(tags) / sizeof(tags[0]));
  for(std::set<std::string>::const_iterator it = tags_set.begin(); it != tags_set.end(); ++it)
  {
    Node* new_node = new Node();
    new_node->tag = *it;
    dummy_node_->elements.push_back(new_node);
  }
  std::string file_name = "";
  //check if tag node passes validityRequiredCheck
  EXPECT_NO_THROW(validityRequiredCheck(file_name,dummy_node_));
}

TEST_F(ValidatorTest,validityRequiredCheckTagThrow)
{
  TiXmlDocument test_doc = loadStdrSpecifications();
  dummy_node_ = new Node();
  dummy_node_->tag = "map_specifications";
  std::string tags[] = {"image"};
  std::set<std::string> tags_set(tags, tags + sizeof(tags) / sizeof(tags[0]));
  for(std::set<std::string>::const_iterator it = tags_set.begin(); it != tags_set.end(); ++it)
  {
    Node* new_node = new Node();
    new_node->tag = *it;
    dummy_node_->elements.push_back(new_node);
  }
  std::string file_name = "";
  //check if tag node, whose elements don't include all required tags, fails to pass validityRequiredCheck
  EXPECT_THROW(validityRequiredCheck(file_name,dummy_node_),ParserException);
}

TEST_F(ValidatorTest,validateTagNoThrow)
{
  TiXmlDocument test_doc = loadStdrSpecifications();
  dummy_node_ = new Node();
  dummy_node_->tag = "point";
  std::string tags[] = {"x","y"};
  std::set<std::string> tags_set(tags, tags + sizeof(tags) / sizeof(tags[0]));
  std::set<std::string>::const_iterator it;
  for(it = tags_set.begin(); it != tags_set.end(); ++it)
  {
    Node* new_node = new Node();
    new_node->tag = *it;
    dummy_node_->elements.push_back(new_node);
  }
  std::string file_name = "";
  //check if tag node passes validate
  EXPECT_NO_THROW(validate(file_name,dummy_node_));
}

TEST_F(ValidatorTest,clearSpecsIsEmpty)
{
  Specs specs;
  Specs returned = Validator::clearSpecs();
  EXPECT_EQ(specs,returned);
}

TEST_F(ValidatorTest, equalitySpecs)
{
  Specs specs_1;
  std::string tmp[] = {"robot", "laser", "sonar"};
  std::set<std::string> tmp_set(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));
  specs_1.non_mergable_tags = tmp_set;
  ElSpecs elspecs;
  std::string tmp_2[] = {"map", "robot", "rfid_tag"};
  elspecs.allowed.insert(tmp_2, tmp_2 + sizeof(tmp_2) / sizeof(tmp_2[0]));
  std::string tmp_3[] = {"map"};
  elspecs.required.insert(tmp_3, tmp_3 + sizeof(tmp_3) / sizeof(tmp_3[0]));
  std::map<std::string,ElSpecs> specs;
  specs.insert ( std::pair<std::string,ElSpecs>("environment",elspecs) );
  specs_1.specs = specs;
  Specs specs_2 = specs_1;
  EXPECT_TRUE(specs_1 == specs_2);
}

TEST_F(ValidatorTest, outputElSpecs)
{  

  ElSpecs elspecs;
  std::string tmp_2[] = {"map", "robot", "rfid_tag"};
  elspecs.allowed.insert(tmp_2, tmp_2 + sizeof(tmp_2) / sizeof(tmp_2[0]));
  std::string tmp_3[] = {"map"};
  elspecs.required.insert(tmp_3, tmp_3 + sizeof(tmp_3) / sizeof(tmp_3[0]));
  elspecs.default_value = "0";
  std::ostringstream elspecs_stream;
  elspecs_stream << elspecs; 
  std::ostringstream expected;
  expected << "mapmaprfid_tagrobot0";
  EXPECT_STREQ(expected.str().c_str(), elspecs_stream.str().c_str());
}
}  // namespace stdr_parser
