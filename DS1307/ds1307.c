#include "ds1307.h"

static uint8_t BCD2DEC(uint8_t bcd){
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

static uint8_t DEC2BCD(uint8_t dec){
    return ((dec / 10) << 4) | (dec % 10);
}

void DS1307_Init(DS1307_Typedef* rtc, Soft_I2C_TypeDef* _i2c, uint8_t _address){
    rtc->i2c = _i2c;
    rtc->address = _address;
}

void DS1307_SetTime(DS1307_Typedef* rtc,
                    uint8_t hour,
                    uint8_t minute,
                    uint8_t second,
                    uint8_t date,
                    uint8_t month,
                    uint8_t year)
{
    uint8_t buf[7];

    buf[0] = DEC2BCD(second);
    buf[1] = DEC2BCD(minute);
    buf[2] = DEC2BCD(hour) & 0x3F;
    buf[3] = 1;
    buf[4] = DEC2BCD(date);
    buf[5] = DEC2BCD(month);
    buf[6] = DEC2BCD(year);

    i2c_soft_write_addr8_bytes(rtc->i2c, rtc->address, 0x00, buf, 7);
}

void DS1307_GetTime(DS1307_Typedef* rtc){
    uint8_t buf[7];
    if (!i2c_soft_read_addr8_bytes(rtc->i2c, rtc->address, 0x00, buf, 7)) return;
    rtc->second = BCD2DEC(buf[0] & 0x7F);
    rtc->minute = BCD2DEC(buf[1]);

    if (buf[2] & (1 << 6)) {
        uint8_t hour = BCD2DEC(buf[2] & 0x1F);
        if (buf[2] & (1 << 5)) {
            if (hour < 12) hour += 12;
        } else {
            if (hour == 12) hour = 0;
        }
        rtc->hour = hour;
    } else {
        rtc->hour = BCD2DEC(buf[2]);
    }

    rtc->date  = BCD2DEC(buf[4]);
    rtc->month = BCD2DEC(buf[5]);
    rtc->year  = BCD2DEC(buf[6]);
}
