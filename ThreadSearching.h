//---------------------------------------------------------------------------

#ifndef ThreadSearchingH
#define ThreadSearchingH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
//#include "Forma.h"
#include "Fabrika.h"
#include "Decorator.h"
#include "ThreadDB.h"
#include "DB.h"

//---------------------------------------------------------------------------
class SearchingClusters : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall SearchingClusters(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
