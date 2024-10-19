#include "Project_Asm.h"

.section    .firmware_image_scpu, "a"
.align      4

#if(_CPU32_COMPRESSED_IMAGE_SUPPORT == _ON)
.incbin     "firmware_image_SCPU.bin.lz4"
#else
.incbin     "firmware_image_SCPU.bin"
#endif
