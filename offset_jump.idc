#include <idc.idc>

static main()
{
	auto pSelectedAddr = ScreenEA();
	if (!strlen(GetFunctionName(Qword(pSelectedAddr))) || pSelectedAddr == BADADDR)
	{
		Warning("Current address is not a virtual function\n\n");
		return;
	}

	auto iOffset = AskLong(0, "Number of vtable offset:");
	if (iOffset < 0)
	{
		Warning("Vtable offset must above 0");
		return;
	}
	
	// Find vtable base address.
	auto pAddr = pSelectedAddr;
	while (pAddr != BADADDR && strlen(GetFunctionName(Qword(pAddr))))
	{
		pAddr = pAddr - 8;
	};

	// Now, base address is vtable offset 0.
	auto pBaseAddr = pAddr + 8;

	// Find VtableMaxOffset
	auto iVtableMaxOffset = 0;
	pAddr = pBaseAddr + 8;
	while (pAddr != BADADDR && strlen(GetFunctionName(Qword(pAddr))))
	{
		pAddr = pAddr + 8;
		iVtableMaxOffset++;
	};

	if (iOffset > iVtableMaxOffset)
	{
		Warning("The given vtable offset %d is out of range %d\n\n", iOffset, iVtableMaxOffset);
		return;
	}

	auto pCalculatedAddr = pBaseAddr + (iOffset * 8);
	Jump(pCalculatedAddr);
	MakeComm(pCalculatedAddr, sprintf("%d", iOffset));
}
