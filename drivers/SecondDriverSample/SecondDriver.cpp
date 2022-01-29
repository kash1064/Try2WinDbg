#include <ntddk.h>

void SecondDriverUnload(_In_ PDRIVER_OBJECT DriverObject);
NTSTATUS SecondDriverCreateClose(_In_ PDRIVER_OBJECT DriverObject, _In_ PIRP irp);
NTSTATUS SecondDriverDeviceControl(_In_ PDRIVER_OBJECT DriverObject, _In_ PIRP irp);


void SecondDriverUnload(_In_ PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);

	KdPrint(("This driver unloaded\n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath);

	KdPrint(("SecondDriver DriverEntry started\n"));

	DriverObject->DriverUnload = SecondDriverUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = SecondDriverCreateClose;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = SecondDriverCreateClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = SecondDriverDeviceControl;

	UNICODE_STRING devName = RTL_CONSTANT_STRING(L"\\Device\\SecondDriver");

	//RtlInitUnicodeString(&devName, L"\\Device\\ThreadBoost");
	PDEVICE_OBJECT DeviceObject;
	NTSTATUS status = IoCreateDevice(DriverObject, 0, &devName, FILE_DEVICE_UNKNOWN, 0, FALSE, &DeviceObject);
	if (!NT_SUCCESS(status)) {
		KdPrint(("Failed to create device (0x%08X)\n", status));
		return status;
	}

	UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\SecondDriver");
	status = IoCreateSymbolicLink(&symLink, &devName);
	if (!NT_SUCCESS(status)) {
		KdPrint(("Failed to create symbolic link (0x%08X)\n", status));
		IoDeleteDevice(DeviceObject);
		return status;
	}

	KdPrint(("SecondDriverSecondDriver DriverEntry completed successfully\n"));

	return STATUS_SUCCESS;
}