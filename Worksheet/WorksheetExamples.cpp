/*------------------------------------------------------------------------------*
 * File Name:				 													*
 * Creation: 																	*
 * Purpose: OriginC Source C file												*
 * Copyright (c) ABCD Corp.	2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010		*
 * All Rights Reserved															*
 * 																				*
 * Modification Log:															*
 *------------------------------------------------------------------------------*/
 
////////////////////////////////////////////////////////////////////////////////////
// Including the system header file Origin.h should be sufficient for most Origin
// applications and is recommended. Origin.h includes many of the most common system
// header files and is automatically pre-compiled when Origin runs the first time.
// Programs including Origin.h subsequently compile much more quickly as long as
// the size and number of other included header files is minimized. All NAG header
// files are now included in Origin.h and no longer need be separately included.
//
// Right-click on the line below and select 'Open "Origin.h"' to open the Origin.h
// system header file.
#include <Origin.h>
////////////////////////////////////////////////////////////////////////////////////

//#pragma labtalk(0) // to disable OC functions for LT calling.

////////////////////////////////////////////////////////////////////////////////////
// Include your own header files here.


////////////////////////////////////////////////////////////////////////////////////
// Start your functions here.


////////////////////////////////////////////////////////////////////////////////////
//This example shows how to extract data with LT condition expression
////////////////////////////////////////////////////////////////////////////////////
enum
{
	EXTRACT_TO_NEW_WKS = 1,
	EXTRACT_WITH_HIGH_LIGHT,
	EXTRACT_WITH_NEW_TAG_COL
};

void Worksheet_Extract_Example(int nOption = EXTRACT_TO_NEW_WKS)
{	
	Worksheet wks = Project.ActiveLayer();
	if( !wks )
		return;

	// prepare test condition string
    string strCondition = "abs(a) >= 1 && abs(b) >= 1";  //Note: here used "&&" not "AND". And || for "OR".
    string strLTRunBeforeloop = "range a=1; range b=2"; // define range objects, a is column 1 and b is column 2.
    
    // check worksheet with strCondition and result the number of rows base on the condition expression. 
    // vnRowIndices included the row index as result.
    vector<uint> vnRowIndices;
    int nn = wks.SelectRows(strCondition, vnRowIndices, 0, -1, -1, strLTRunBeforeloop);
    
    if(nn < 0)
    {
    	out_str("User cancel");
    	return;
    }    
    
    if(nn == 0)
    {
        out_str("No matching row");
        return;
    }    
    
	printf("%d rows selected with condition -- %s\n", nn, strCondition);
	
	switch(nOption)
	{
	case EXTRACT_TO_NEW_WKS:	    
	    Worksheet wksResult;
	    wksResult.Create();	    
	    
		// Extract data to new worksheet with column indices "vsCols" and row indices "vnRowIndices"
		vector<uint> vnCols = {0, 1}; // only extract the first two columns to new worksheet
	    BOOL bRet = wks.Extract(wksResult, vnRowIndices, vnCols);
	    if(bRet)
	        printf("Extract selected rows to [%s]!%s.\n", wksResult.GetPage().GetName(), wksResult.GetName());  	    
	    break;
	
	case EXTRACT_WITH_HIGH_LIGHT:
        // hight light rows by vnRowIndices
        vector<int> vnRows;
        vnRows = vnRowIndices; // convert vector<uint> to vector<int>
        wks.SetSelectedRange(vnRows);
        break;
        
    case EXTRACT_WITH_NEW_TAG_COL:
        // add a new column with 0/1 to mark if not fit or fit condiftion
        Dataset ds(wks, wks.AddCol());
        ds.SetSize(wks.GetNumRows());
        ds = 0;
        ds.Replace(vnRowIndices, 1);
        break;

	default:
		break;
	}    
}

void Before_Running()
{
	// prepare worksheet with data to do extract
	Worksheet wks;
	wks.Create();
	wks.SetSize(30, 3); // set worksheet with 3o rows and 3 columns	
	
	// set random data for the first TWO columns
	for(int nCol = 0; nCol < wks.GetNumCols()-1; nCol++)
	{
		Dataset ds(wks, nCol);
		ds.Normal(wks.GetNumRows());
	}
	
	// fill row numbers to Column C
	Dataset dsC(wks, 2); 
	dsC.Data(1, wks.GetNumRows(), 1);
}