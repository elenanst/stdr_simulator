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



namespace stdr_parser
{


/**
 * @class ValidatorTest
 * @brief Basic Test Fixture for testing Validator
 */
class MsgCreatorTest : public ::testing::Test
{
 protected:
  MsgCreatorTest()
  {
  }

  virtual void TearDown()
  {
    
  }

  void init(const std::string& filename)
  {
    utils_file_ = ros::package::getPath("stdr_parser") +
                    filename;
  }
   

 
  std::string utils_file_;
  
};

TEST_F(ValidatorTest, parseMergableSpecificationsTestThrow)
{
}
}  // namespace stdr_parser
