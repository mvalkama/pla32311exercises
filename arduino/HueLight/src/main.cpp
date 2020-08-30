#include <Arduino.h>


void H2R_HSBtoRGB(int hue, int sat, int bright, int* colors);

const float H2R_MAX_RGB_val = 255.0;

const int PIN_GREEN = 9;
const int PIN_BLUE = 10;
const int PIN_RED = 11;

const int HUE_PIN = PIN_A0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10000);

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

}

void loop() {
  int hueValue = map(analogRead(HUE_PIN), 0, 1023, 0, 360);
  int saturation = 100;
  int brightness = 100;

  int rgb[3];
  
  H2R_HSBtoRGB(hueValue, saturation, brightness, rgb);

  int red = rgb[0];
  int green = rgb[1];
  int blue = rgb[2];

  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);
}

// from https://github.com/julioterra/HSB_Color
void H2R_HSBtoRGB(int hue, int sat, int bright, int* colors) {
		
	// constrain all input variables to expected range
    hue = constrain(hue, 0, 360);
    sat = constrain(sat, 0, 100);
    bright = constrain(bright, 0, 100);

	// define maximum value for RGB array elements
	float max_rgb_val = H2R_MAX_RGB_val;

	// convert saturation and brightness value to decimals and init r, g, b variables
    float sat_f = float(sat) / 100.0;
    float bright_f = float(bright) / 100.0;        
    int r, g, b;
    
    // If brightness is 0 then color is black (achromatic)
    // therefore, R, G and B values will all equal to 0
    if (bright <= 0) {      
        colors[0] = 0;
        colors[1] = 0;
        colors[2] = 0;
    } 
	
	// If saturation is 0 then color is gray (achromatic)
    // therefore, R, G and B values will all equal the current brightness
    if (sat <= 0) {      
        colors[0] = bright_f * max_rgb_val;
        colors[1] = bright_f * max_rgb_val;
        colors[2] = bright_f * max_rgb_val;
    } 
    
    // if saturation and brightness are greater than 0 then calculate 
	// R, G and B values based on the current hue and brightness
    else {
        
        if (hue >= 0 && hue < 120) {
			float hue_primary = 1.0 - (float(hue) / 120.0);
			float hue_secondary = float(hue) / 120.0;
			float sat_primary = (1.0 - hue_primary) * (1.0 - sat_f);
			float sat_secondary = (1.0 - hue_secondary) * (1.0 - sat_f);
			float sat_tertiary = 1.0 - sat_f;
			r = (bright_f * max_rgb_val) * (hue_primary + sat_primary);
			g = (bright_f * max_rgb_val) * (hue_secondary + sat_secondary);
			b = (bright_f * max_rgb_val) * sat_tertiary;  
        }

        else if (hue >= 120 && hue < 240) {
			float hue_primary = 1.0 - ((float(hue)-120.0) / 120.0);
			float hue_secondary = (float(hue)-120.0) / 120.0;
			float sat_primary = (1.0 - hue_primary) * (1.0 - sat_f);
			float sat_secondary = (1.0 - hue_secondary) * (1.0 - sat_f);
			float sat_tertiary = 1.0 - sat_f;
			r = (bright_f * max_rgb_val) * sat_tertiary;  
			g = (bright_f * max_rgb_val) * (hue_primary + sat_primary);
			b = (bright_f * max_rgb_val) * (hue_secondary + sat_secondary);
        }

        else if (hue >= 240 && hue <= 360) {
			float hue_primary = 1.0 - ((float(hue)-240.0) / 120.0);
			float hue_secondary = (float(hue)-240.0) / 120.0;
			float sat_primary = (1.0 - hue_primary) * (1.0 - sat_f);
			float sat_secondary = (1.0 - hue_secondary) * (1.0 - sat_f);
			float sat_tertiary = 1.0 - sat_f;
			r = (bright_f * max_rgb_val) * (hue_secondary + sat_secondary);
			g = (bright_f * max_rgb_val) * sat_tertiary;  
			b = (bright_f * max_rgb_val) * (hue_primary + sat_primary);
        }
        
        colors[0]=r;
        colors[1]=g;
        colors[2]=b;
		
    }
}
