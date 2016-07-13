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
   * Manos Tsardoulias, etsardou@gmail.com
   * Aris Thallas, aris.thallas@gmail.com
   * Chris Zalidis, zalidis@gmail.com 
******************************************************************************/

#include "stdr_parser/stdr_parser_node.h"


namespace stdr_parser
{

  
  /**
  @brief Default constructor
  @return void
  **/
  Node::Node(void)
  {
    priority = 0;
  }
  
  Node::~Node(void)
  {
	this->unallocateChildren();
  }

  /**
  @brief Checks a node if a specific filename exists
  @return void
  **/
  bool Node::checkForFilename(std::string base)
  {
    if(elements.size() == 1)
    {
      if(elements[0]->tag == base)
      {
        return true;
      }
    }
    return false;
  }
  
  /**
  @brief Searches for a tag in the specific node
  @param tag [std::string] The tag to search for
  @return std::vector<int> : The indexes in elements where tag is found
  **/
  std::vector<int> Node::getTag(std::string tag)
  {
    std::vector<int> ret;
    for(unsigned int i = 0 ; i < elements.size() ; i++)
    {
      if(elements[i]->tag == tag)
      {
        ret.push_back(i);
      }
    }
    return ret;
  }
  
  /**
  @brief Increases the priority of the node
  @return void
  **/
  void Node::increasePriority(void)
  {
    priority ++;
    for(unsigned int i = 0 ; i < elements.size() ; i++)
    {
      elements[i]->increasePriority();
    }
  }
  
  /**
  @brief Debug recursive function - Prints the xml tree
  @param n [Node*] The stdr xml tree node to begin
  @param indent [std::string] The indentation for the specific node
  @return void
  **/
  void Node::getTreeStructure(std::string indent, std::ostringstream& output_stream_)
  { 
   
    
    if(value != "")
    {  
       output_stream_ << indent.c_str() << "-" << value.c_str() <<"'  (" << priority << ") - ";

      if(file_origin.find(".yaml") != std::string::npos)
      {
#ifndef HAVE_NEW_YAMLCPP
      ROS_INFO("file origin is %s", file_origin.c_str());
        output_stream_ << file_row; 
#endif
      }
      else
      {
        output_stream_ << file_row; 
      }
      output_stream_ << extractFilename(file_origin).c_str() << "\n" ; 
    }
    else
    {
       output_stream_ << indent.c_str() << "-" << tag.c_str() <<"'  (" << priority << ") - " ;
       if(file_origin.find(".yaml") != std::string::npos)
       {
#ifndef HAVE_NEW_YAMLCPP
       output_stream_ << file_row; 
#endif
       }
       else
       {
         output_stream_ << file_row; 
       }
       output_stream_ << extractFilename(file_origin).c_str()<< "\n" ; 
    }  
    
    for(unsigned int i = 0 ; i < elements.size() ; i++)
    {
      elements[i]->getTreeStructure(indent+std::string("| "), output_stream_);
    }
    
  }
  
  /**
  * @brief Unallocates the memory of the node's children
  * @return void
  */
  void Node::unallocateChildren(void)
  {

  
    for(unsigned int i = 0 ; i < elements.size() ; i++)
    {     
      delete elements[i];
      elements.erase(elements.begin() + i);
    }
  }

  

}
