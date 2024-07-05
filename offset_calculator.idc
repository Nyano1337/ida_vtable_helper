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
	auto pAddr = pSelectedAddr;
	while (pAddr != BADADDR && strlen(GetFunctionName(Qword(pAddr))))
	{
		pAddr = pAddr - 8;
		iOffset++;
	};

	if (iOffset > -1)
	{
		MakeComm(pSelectedAddr, sprintf("%d", iOffset));
	}
	else
	{
		Warning("Current address is not a virtual function\n\n");
	}
}
