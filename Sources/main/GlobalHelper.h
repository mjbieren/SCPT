#pragma once
#include "stdafx.h"
#include "Fasta.h"
#include "TaxonomicGroup.h"
#include "Management.h"
#include "SCPT_PropertyBag.h"

class CGlobal
{
public:
	CGlobal() {};
	~CGlobal() {};

	CSCPTPropertyBag propertyBag;
	CManagement management;
	//CFastaHeaders FastaHeaders;

};

extern CGlobal glb;


#define CHECK_RETURNVALUE(value)        \
if(value!=ERR_NOERROR)                  \
{                                       \
   glb.management.ErrorChecker(value);  \
   return (int) value;                        \
}                              

#define CHECK_RETURNVALUE_REL_PTR(value, ptr)        \
if(value!=ERR_NOERROR)                  \
{                                       \
    delete ptr;                         \
     glb.management.ErrorChecker(value); \
   return (int) value;                  \
}
