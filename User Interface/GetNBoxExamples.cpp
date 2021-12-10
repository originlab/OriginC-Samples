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
#include <GetNbox.h>

////////////////////////////////////////////////////////////////////////////////////

//#pragma labtalk(0) // to disable OC functions for LT calling.


////////////////////////////////////////////////////////////////////////////////////
//This example is about GetNBox and PEVENT_GETN
////////////////////////////////////////////////////////////////////////////////////
#include <Control.h> 
void GetNBox_ex()
{
    GETN_TREE(tr)
    GETN_COMBO_BUTTON(test, ">", "List", "User", "AAA|BBB", "")
    GETN_CHECK(check, "Yes or No", 0) 
 
    if( GetNBox(tr, _event_func_ex, "Test Event Function", "Test...") ) 
    {
    	out_str("Done"); // if OK button clicked
    }
}
static int _event_func_ex(TreeNode& tr, int nRow, int nEvent, DWORD& dwEnables, LPCSTR lpcszNodeName, WndContainer& getNContainer, string& strAux, string& strErrMsg)
{	
	//1. show how to use tr, nRow and nEvent	
    if(GETNE_ON_VALUE_CHANGE == nEvent)
    {
    	//get the value-changed node
    	TreeNode trEdited = tree_get_node(tr, nRow);
    	if( trEdited )
    	    printf("changed node: %s\n", trEdited.tagName);
    }
 
	
	//show how to use nEvent, lpcszNodeName, and getNContainer
    if(ONODETYPE_BROWSECOMBO == nEvent && lstrcmpi(lpcszNodeName,"test") == 0)
    { 
		//click the ">" button to show menu
    	Menu myMenu;
    	myMenu.Add("Item1", 1, MF_STRING);
    	myMenu.Add("Item2", 2, MF_STRING);
    	
    	int nSelCmd;
		POINT pt;
		GetCursorPos(&pt);
		myMenu.TrackPopupMenu(0, pt.x, pt.y, getNContainer.GetSafeHwnd(), &nSelCmd);
		if(nSelCmd > 0)
		{
			string strName;
			myMenu.GetMenuString(nSelCmd, strName, MF_STRING);
			tr.test.strVal = strName;
		}
    }
	

    //shows how to use strErrMsg and disable OK button
    if( tr.check )
    {
    	// disable OK button if "Yes or No" checkbox is unchecked.
    	bool bEnable = ( 1 == tr.check.nVal ); 
    	O_SET_BIT(dwEnables, GETNGEVT_OK_ENABLE, bEnable);     	
    	if( !bEnable )
    		strErrMsg = "Error! Yes or No checkbox is unchecked";
    }
    return true;
}


////////////////////////////////////////////////////////////////////////////////////
//This example shows the difference in 
//GETN_STR_GROUP, GETN_MULTISEL_STR_LISTBOX and GETN_MULTISEL_LISTBOX
////////////////////////////////////////////////////////////////////////////////////
static int Dialog1Node_event(TreeNode& tr, int nRow, int nEvent, DWORD& dwEnables, LPCSTR lpcszNodeName, WndContainer& getNContainer, string& strAux, string& strErrMsg)
{	
	string strNode = lpcszNodeName;
	
	if(strNode == "list") {
		vector<int> vnSel;
		vnSel = tr.list.nVals;
		for(int ii = 0; ii < vnSel.GetSize(); ii++) {
			printf("%d: %d\n", ii+1, vnSel[ii]);
		}
	}

	return true;
}

void GetNMultiBox_ex()
{
	vector<string> vsFruits = {"Apple", "Orange", "Banana", "Berries", "Grapes"};
	string strCombo;
	strCombo.SetTokens(vsFruits, '|');
	
	GETN_TREE(tr)
	GETN_STR_GROUP(stats, "Please pick a few US Stats", "MA", "|MA|CA|RI|VT|NY")
	GETN_MULTISEL_STR_LISTBOX(StateList, _L("Positive State Value"), "", "a|b|c")
	GETN_MULTISEL_LISTBOX(list, "Select", 0, strCombo)
	
	if(GetNBox(tr, Dialog1Node_event , "Dialog title"))
	{
		out_tree( tr );
		
		vector<int> vnSel;vnSel = tr.list.nVals;
		for(int ii = 0; ii < vnSel.GetSize(); ii++) {			
			string strName = vsFruits[vnSel[ii]];
			printf("%d: %s\n", ii+1, strName);
		}	
	}
}