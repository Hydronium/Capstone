#define BACKGROUND_COLOUR LCD_COLOR_WHITE

void LCDInit(void);
void LCDClear(void);
void LCDDisplayText(int X, int Y, char * message);
void LCDDisplayCurrentAlarmTime(int day, int hour, int minute, int dispenseCycle);
