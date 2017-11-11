#include "stdafx.h"

struct SYSTEM_PROCESS_ID_INFORMATION
{
	PVOID process_id;
	UNICODE_STRING image_name;
};
int main()
{
	auto class_id = static_cast<_SYSTEM_INFORMATION_CLASS>(0x58);
	auto size = sizeof(SYSTEM_PROCESS_ID_INFORMATION);
	for (size_t id = 0; id < 10000; id += 4)
	{
		SYSTEM_PROCESS_ID_INFORMATION buffer = {};
		buffer.image_name.MaximumLength = 250;
		buffer.image_name.Buffer = new wchar_t[250];
		buffer.process_id = reinterpret_cast<PVOID>(id);

		auto temp_buffer = buffer.image_name.Buffer; // NtQuerySystemInformation will null it if process name is not found

		ULONG return_length;

		if (NtQuerySystemInformation(class_id, &buffer, size, &return_length) == ERROR_SUCCESS) // VALID PROCESS ID
		{
			if (buffer.image_name.Buffer)
			{
				std::wcout << id << " - " << buffer.image_name.Buffer << std::endl;
			}
			else
			{
				std::wcout << id << " - <empty>" << std::endl;
			}
		}

		delete temp_buffer;
	}

    return 0;
}

