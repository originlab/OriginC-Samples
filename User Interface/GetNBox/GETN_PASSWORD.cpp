
#include <Origin.h>
#include <GetNbox.h>

void GETN_PASSWORD_ex1()
{
    GETN_BOX( treeTest )
    GETN_BEGIN_BRANCH(trBranch, " ") GETN_OPTION_BRANCH(GETNBRANCH_OPEN)
    GETN_MULTI_COLS_BRANCH(2, DYNA_MULTI_COLS_COMAPCT) 
		GETN_PASSWORD(Key, "PassWord", " ")
		GETN_PAD(dummy)
		GETN_CHECK(View, "View", 0) 
		GETN_STR(Info, "", "") GETN_INFO
	GETN_END_BRANCH(trBranch)
    
    if( GetNBox( treeTest, _pw_event_func_ex, "Title PassWord", "Input PassWord") )
    {
        out_tree( treeTest );
    }
}

static int _pw_event_func_ex(TreeNode& tr, int nRow, int nEvent, DWORD& dwEnables, LPCSTR lpcszNodeName, WndContainer& getNContainer, string& strAux, string& strErrMsg)
{   
    if(1 == tr.trBranch.View.nVal)
    	tr.trBranch.Info.strVal = tr.trBranch.Key.strVal;
    else
    	tr.trBranch.Info.strVal = "";
    
    return 0;
}