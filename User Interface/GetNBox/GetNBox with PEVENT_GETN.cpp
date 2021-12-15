
////////////////////////////////////////////////////////////////////////////////////
//This example is about GetNBox and PEVENT_GETN
////////////////////////////////////////////////////////////////////////////////////
#include <Origin.h>
#include <GetNbox.h>
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
	//show how to use tr, nRow and nEvent	
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