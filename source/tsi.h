#define TSI_DATA ((TSI0->DATA) & 0xFFFF)

void TSI_init();

int TSI_scan();

