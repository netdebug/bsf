/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2011 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "CmGLGpuProgramManager.h"
#include "CmException.h"

using namespace CamelotEngine;

GLGpuProgramManager::GLGpuProgramManager()
{
    // Superclass sets up members 
}

GLGpuProgramManager::~GLGpuProgramManager()
{
}

bool GLGpuProgramManager::registerProgramFactory(const String& syntaxCode, CreateGpuProgramCallback createFn)
{
    return mProgramMap.insert(ProgramMap::value_type(syntaxCode, createFn)).second;
}

bool GLGpuProgramManager::unregisterProgramFactory(const String& syntaxCode)
{
    return mProgramMap.erase(syntaxCode) != 0;
}

GpuProgram* GLGpuProgramManager::create(const String& source, const String& entryPoint, const String& language, GpuProgramType gptype, GpuProgramProfile profile)
{
    ProgramMap::const_iterator iter = mProgramMap.find(language);
    if(iter == mProgramMap.end())
    {
        CM_EXCEPT(InternalErrorException, "Cannot find propery factory to create GpuProgram of type: " + language);
    }
    
    return (iter->second)(source, entryPoint, language, gptype, profile);
}

