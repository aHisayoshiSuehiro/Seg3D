/*
 For more information, please see: http://software.sci.utah.edu

 The MIT License

 Copyright (c) 2016 Scientific Computing and Imaging Institute,
 University of Utah.


 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

#ifndef APPLICATION_PROJECT_PROJECTNOTE_H
#define APPLICATION_PROJECT_PROJECTNOTE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

// STL includes
#include <string>
#include <vector>

// boost includes
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

namespace Seg3D
{

// Forward declaration
class ProjectNote;
typedef std::vector< ProjectNote > ProjectNoteList;
typedef boost::shared_ptr< ProjectNoteList > ProjectNoteListHandle;

/// CLASS ProjectNote
/// This helper class is for querying project notes from the interface thread.
class ProjectNote
{
public:
  typedef boost::posix_time::ptime timestamp_type;

  ProjectNote( const std::string& note, const std::string& user_id, 
    const timestamp_type& timestamp ) :
    note_( note ),
    user_id_( user_id ),
    timestamp_( timestamp )
  {
  }

  ProjectNote() {}

  ~ProjectNote() {}
  
  const std::string& note() const
  {
    return this->note_;
  }

  const std::string& user_id() const
  {
    return this->user_id_;
  }

  const timestamp_type& timestamp() const
  {
    return this->timestamp_;
  }
  
private:
  /// The content of the note
  std::string note_;
  /// User that wrote the note
  std::string user_id_;
  /// Timestamp of when the note was saved in UTC time
  timestamp_type timestamp_;
};  

} // end namespace Seg3D

#endif
