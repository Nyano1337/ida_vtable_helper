#include <idc.idc>

static main()
{
	SetStatus(IDA_STATUS_WORK);

	auto pSelectedAddr = ScreenEA();
	
	if (pSelectedAddr == BADADDR)
	{
		Message("** No vtable selected! Aborted **");
		Warning("No vtable selected!\nSelect vtable block first.");							
		SetStatus(IDA_STATUS_READY);
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
	}
	else
	{
		Message("Current address is not a virtual function\n\n");
	}

	Message("===================================\n\n");

	SetStatus(IDA_STATUS_READY);
}
