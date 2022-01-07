
////////////////////////////////////////////////////////////////////////////////////
//This example is about set plot's modifier
////////////////////////////////////////////////////////////////////////////////////

#include <Origin.h>

//use SetModifier to set plot label
void set_label_by_SetModifier()
{
	//prepare data
	Worksheet wks;
	wks.Create("origin");
	if(!wks)
		return;
	wks.AddCol();
	
	vector vn = {1,2,3,4,5};
	for(int ii = 0; ii < 3; ii++)
	{
		Dataset ds(wks, ii);
		ds = vn;
	}
	
	//plot
	DataRange dr;	
	dr.Add(wks, 0, "X");
	dr.Add(wks, 1, "Y");
	
	GraphPage gp;
	gp.Create("Origin");
	GraphLayer gl = gp.Layers();	
	gl.AddPlot(dr, IDM_PLOT_SCATTER);
	gl.Rescale();
	
	//set label
	Column col(wks, 2);
	DataPlot dp = gl.DataPlots(0); 
	if(!dp)
		return;
	dp.SetModifier(COLDESIG_PLOTLABEL_FORM, col);//see PlotDesignationEx for more modifier types.
	
	vector<int> vnDesigs;
	vector<string> saNames;
	dp.GetModifiers(vnDesigs, saNames);
	
	vector<uint> vecIndex;
	if(vnDesigs.Find(vecIndex, COLDESIG_PLOTLABEL_FORM) > 0) 
	{
		printf("label form = %s\n", saNames[ vecIndex[0] ]);
	}
}

//use ApplyFormat to set plot label
void set_label_by_applyformat()
{
	//prepare data
	Worksheet wks;
	wks.Create("origin");
	if(!wks)
		return;
	wks.AddCol();
	
	vector vn = {1,2,3,4,5};
	for(int ii = 0; ii < 3; ii++)
	{
		Dataset ds(wks, ii);
		ds = vn;
	}
	
	//plot
	DataRange dr;	
	dr.Add(wks, 0, "X");
	dr.Add(wks, 1, "Y");
	
	GraphPage gp;
	gp.Create("Origin");
	GraphLayer gl = gp.Layers();	
	gl.AddPlot(dr, IDM_PLOT_SCATTER);
	gl.Rescale();
	
	//set label
	DataPlot dp = gl.DataPlots(0);
	if(dp)
	{		
		Tree trFmt;
		TreeNode trEnable = trFmt.Root.Label.AddNode("Enable");
		trEnable.nVal = 1;
		
		OQCOLOR nLab;
		int ycol = 1, labelcol = 2;
		//convert the offset(modifier column to y column) to theme internal value
		okutil_get_ocolor_by_col(&nLab, labelcol, ycol, SYMB_COLOR_COLTYPE_INDEX);
		
		trFmt.Root.Label.Form.nVal = nLab;
		if ( 0 == dp.UpdateThemeIDs(trFmt.Root) )
			dp.ApplyFormat(trFmt, true, true);
	}	
}