#ifndef __OUTPUT_H
#define __OUTPUT_H

#include "sys.h"

#define Data_LED (PBout(15))
#define Data_LED_ON (PBout(15)=1)
#define Data_LED_OFF (PBout(15)=0)


void Output_Init(void);

#endif

