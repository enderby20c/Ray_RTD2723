#if(_LOCAL_DIMMING_TOTAL_REGION >= _LOCAL_DIMMING_TRUE_DIRECT_REGION)
#include "Panel/LocalDimmingDefaultTable/Direct/tPWMDecreaseTable.h"
#else
#include "Panel/LocalDimmingDefaultTable/Edge/tPWMDecreaseTable.h"
#endif