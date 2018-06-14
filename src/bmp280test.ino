#include <stdio.h>
#include <Wire.h>
#include <BME280I2C.h>
#include <U8g2lib.h>

#define INTERVAL 60 * 1000 // in msec
#define DISPLAY_I2C_ADDRESS 0x3c

BME280I2C::Settings settings(
	/* obtained from 3.5.3 Indoor navigation */
	BME280::OSR_X2,     // Temperature
	BME280::OSR_X1,     // Humidity
	BME280::OSR_X16,    // Pressure
	BME280::Mode_Normal,
	BME280::StandbyTime_500us,
	BME280::Filter_16,
	BME280::SpiEnable_False,
	BME280I2C::I2CAddr_0x76
);

BME280I2C bme(settings);
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, GPIO_SCL, GPIO_SDA);

struct censor_value {
	float t;
	float h;
	float p;
};

void
setup() {
	Serial.begin(115200);
	Serial.println();
	Serial.println(F(__FILE__));
	Serial.println(F("BMP280 with OLED display"));
	Serial.println(F("Initialing..."));

	Wire.begin();
	u8g2_init();

	while (!bme.begin()) {
		Serial.println(F("Failed to contact BMP280 via I2C"));
		delay(1000);
	}
	switch(bme.chipModel()) {
		case BME280::ChipModel_BME280:
			Serial.println("Found BME280 sensor! Success.");
			break;
		case BME280::ChipModel_BMP280:
			Serial.println(F("Found BMP280 sensor! No Humidity available."));
			break;
		case BME280::ChipModel_UNKNOWN:
			Serial.println(F("Found UNKNOWN sensor!"));
	}
	Serial.println(F("Initialized."));
	u8g2.firstPage();
	do {
		u8g2.setCursor(0, line_number(1));
		u8g2.print(F("Initialized."));
	} while (u8g2.nextPage());
}

void
u8g2_init()
{
	u8g2.begin();
	u8g2.setFont(u8g2_font_7x14_tf);
	u8g2.firstPage();
	do {
		u8g2.setCursor(0, line_number(1));
		u8g2.print(F("Initializing..."));
	} while (u8g2.nextPage());
}

void
update_u8g2_screen(const struct censor_value *v)
{
	/* -10.0 */
	char t_string[6], h_string[6], p_string[7];
	dtostrf(v->t, sizeof(t_string) / sizeof(t_string[0]) -1, 1, t_string);
	dtostrf(v->h, sizeof(h_string) / sizeof(h_string[0]) -1, 1, h_string);
	dtostrf(v->p, sizeof(p_string) / sizeof(p_string[0]) - 1, 1, p_string);
	u8g2.firstPage();
	do {
		u8g2.setCursor(0, line_number(1));
		u8g2.print(F("Temp.:"));
        u8g2.print((String)t_string);
        u8g2.print(F("`C"));
		u8g2.setCursor(0, line_number(2));
		u8g2.print(F("Humidity:"));
        u8g2.print((String)h_string);
        u8g2.print(F("%"));
		u8g2.setCursor(0, line_number(3));
		u8g2.print(F("Press.: "));
        u8g2.print((String)p_string);
        u8g2.print(F("hPa"));
	} while (u8g2.nextPage());
}

uint8_t
line_number(uint8_t line) {
	return (uint8_t) u8g2.getMaxCharHeight() * line;
}

void
log(String msg) {
}

void
loop()
{
	struct censor_value v;

	delay(INTERVAL);
	bme.read(v.p, v.t, v.h, BME280::TempUnit_Celsius, BME280::PresUnit_hPa);
	update_u8g2_screen(&v);

	Serial.print(F("Temperature = "));
	Serial.print(v.t);
	Serial.println("'C");

	Serial.print(F("Humidity = "));
	Serial.print(v.h);
	Serial.println(F("%"));

	Serial.print(F("Pressure = "));
	Serial.print(v.p);
	Serial.println(F("hPa"));
	Serial.println();
}
