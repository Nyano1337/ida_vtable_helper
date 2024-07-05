#include <idc.idc>

static main()
{
	auto pSelectedAddr = ScreenEA();
	
	if (pSelectedAddr == BADADDR)
	{
		Message("** No vtable selected! Aborted **");
		Warning("No vtable selected!\nSelect vtable block first.");							
		return;
	}
	
	auto iOffset = -1;

	Message("===================================\n\n");

	auto pAddr = pSelectedAddr;
	while (pAddr != BADADDR)
	{
		if (strlen(GetFunctionName(Qword(pAddr))) == 0)
		{
			break;
		}
		
		pAddr = pAddr - 8;

		iOffset++;
	};

	if (iOffset > -1)
	{
		Message("Func \'%s\' vable offset is %d\n\n", GetFunctionName(Qword(pSelectedAddr)), iOffset);
		MakeComm(pSelectedAddr, sprintf("%d", iOffset));
	}
	else
	{
		Message("Current address is not a virtual function\n\n");
	}

	Message("===================================\n\n");
}
