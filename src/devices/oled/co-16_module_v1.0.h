#ifndef CO_16_MODULE_V1_0
#define CO_16_MODULE_V1_0

#define CO_16_MODULE_V1_0_ADRESS 0x3c

#define CO_16_SEND_COMMAND(CMD)  CO_16_write_register(CO_16_MODULE_V1_0_ADRESS, 0x80, CMD)
#define CO_16_SEND_BYTE(BYTE)  CO_16_write_register(CO_16_MODULE_V1_0_ADRESS, 0x40, BYTE)



void CO_16_init(void);
void CO_16_write_register(uint8_t address, uint8_t reg, uint8_t value);

void CO_16_set_position(uint8_t row, uint8_t col);
void CO_16_clear_display(void);

#endif // CO_16_MODULE_V1_0