/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/


#ifndef _LCFILE_H
#define _LCFILE_H

#include "LTask.h"


class LCFileClass  : public _LTaskClass {

public:
	LCFileClass() { };

public:
	/**
	 *  \brief Create a file with name.
	 *  
	 *  \param [in] filename the name of file
	 *  \return Return Null.
	 */
	void Create(const char* filename);
		
	/**
	 *  \brief Write a buffer into a file.
	 *  
	 *  \param [in] strbuf the buffer want to write.
	 *  \return Return Null.
	 */
	void Write(const char* fileName, const char* strbuf);
	
	/**
	 *  \brief Delete a file, need to open file.
	 *  
	 *  \return Return Null.
	 */
	void Delete(const char* fileName);
	
	/**
	 *  \brief Read a file, need to open file.
	 *  
	 *  \param [in] strbuf the pointer of buffer.
	 *  \param [in] nbyte the size of buffer.
	 *  \param [in] pos the position of beginning.
	 *  
	 *  \return Return Null.
	 */
	void Read(const char* fileName, char* strbuf, unsigned int nbyte, unsigned long pos = 0);
	
	/**
	 *  \brief Get the size of a file, need to open file.
	 *  
	 *  \param [in] size the pointer of size.
	 *  \return Return Null.
	 */
	void Size(const char* fileName, unsigned long* size);

private:

};

extern LCFileClass LFile;

#endif
