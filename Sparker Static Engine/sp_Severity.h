#ifndef SP_SEVERITY_H
#define SP_SEVERITY_H


#define SP_INFO 0
#define SP_WARNING 1
#define SP_ERROR 2
#define SP_FATAL 3

#define SP_VK_VERBOSE VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
#define SP_VK_INFO VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
#define SP_VK_WARNING VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
#define SP_VK_ERROR VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
#define SP_VK_FATAL VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT

#endif // !SP_SEVERITY