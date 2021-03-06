#pragma once

struct ThreadData {
	ULONG ThreadId;
	int Priority;
};

#define SECOND_DRIVER_DEVICE 0x8000

#define IOCTL_SECOND_DRIVER_SET_PRIORITY CTL_CODE(SECOND_DRIVER_DEVICE, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)