#ifndef SP_SEVERITY_H
#define SP_SEVERITY_H

/*
#define SP_MESSAGE_INFO 0
#define SP_MESSAGE_WARNING 1
#define SP_MESSAGE_ERROR 2
#define SP_MESSAGE_FATAL 3
#define SP_VK_RESULT 4*/

#define SP_VK_VERBOSE VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
#define SP_VK_INFO VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
#define SP_VK_WARNING VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
#define SP_VK_ERROR VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT

enum SpExitCode {

	Sp_Exit_ValidationLayersUnavailable = 50,
	Sp_Exit_DebugMessengerPtrNotProvided = 51,
	Sp_Exit_DebugMessengerFailedToCreate = 52,
	Sp_Exit_InstancePtrNotProvided = 100,
	Sp_Exit_InstanceFailedToCreate = 101,
	Sp_Exit_SurfaceFailedToCreate = 105
};

enum SpMessage {
	SP_MESSAGE_INFO,
	SP_MESSAGE_WARNING,
	SP_MESSAGE_ERROR,
	SP_MESSAGE_FATAL,
	SP_VK_RESULT
};


#endif // !SP_SEVERITY