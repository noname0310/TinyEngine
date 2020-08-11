// Project1.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Project1.h"


// This is an example of an exported variable
PROJECT1_API int nProject1=0;

// This is an example of an exported function.
PROJECT1_API int fnProject1(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CProject1::CProject1()
{
    return;
}
