#include "Project_Asm.h"

#if((_GOSD_SUPPORT == _ON) && (_USER_EMBEDDED_GOSD_RESOURCE_FILE_SUPPORT == _ON))

.section    .resource, "a"
.balign      65536

##################################################################
# Resource name and path
##################################################################
__resource_start:
.incbin     "./User/RTD_Series/RTD2020Resource/RTD2020GosdImageSource.bin"
__resource_end:


##################################################################
# Resource info
#   - address
#   - size
##################################################################
.section    .resource_info, "a"
.balign      4
.word       __resource_start
.word       __resource_end - __resource_start

#endif