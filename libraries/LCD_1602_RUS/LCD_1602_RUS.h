#include <LiquidCrystal_I2C.h>
#include <Print.h>

#define MAX_SYMBOL_COUNT 8  //Максимальное количество переназначаемых символов от 0 до 7
#define BYTE 0

class LCD_1602_RUS : public LiquidCrystal_I2C {
public:
  LCD_1602_RUS(uint8_t, uint8_t, uint8_t);
  void print(const wchar_t[]);
  void print(const char[]);
  void print(int, int = DEC);
  void print(unsigned int, int = DEC);
  void print(long, int = DEC);
  void print(unsigned long, int = DEC);
  void print(const String &);
  void print(char, int = BYTE);
  void print(unsigned char, int = BYTE);
  void print(double, int = 2);
  void clear();
  void setCursor(uint8_t, uint8_t); 
  uint8_t getCursorCol(); 
  uint8_t getCursorRow(); 
  wchar_t *asciiutf8(unsigned char);

private:
  void CharSetToLCD(uint8_t *, uint8_t *);
  void ResetAllIndex();
  void printwc(const wchar_t);
  uint8_t mbtowc(wchar_t *, char *, uint8_t);

  int symbol_index;//Индекс символа (от 0 до 7)
  uint8_t cursor_col;
  uint8_t cursor_row;
  //===Буквы====
  uint8_t index_rus_B;
  uint8_t index_rus_G;
  uint8_t index_rus_D;
  uint8_t index_rus_ZH;
  uint8_t index_rus_Z;
  uint8_t index_rus_I;
  uint8_t index_rus_II;
  uint8_t index_rus_L;
  uint8_t index_rus_P;
  uint8_t index_rus_U;
  uint8_t index_rus_F;
  uint8_t index_rus_TS;
  uint8_t index_rus_CH;
  uint8_t index_rus_SH;
  uint8_t index_rus_SCH;
  uint8_t index_rus_tverd;
  uint8_t index_rus_Y;
  uint8_t index_rus_myagk;
  uint8_t index_rus_EE;
  uint8_t index_rus_YU;
  uint8_t index_rus_YA;
  uint8_t index_rus_b;
  uint8_t index_rus_v;
  uint8_t index_rus_g;
  uint8_t index_rus_d;
  uint8_t index_rus_yo;
  uint8_t index_rus_zh;
  uint8_t index_rus_z;
  uint8_t index_rus_i;
  uint8_t index_rus_ii;
  uint8_t index_rus_k;
  uint8_t index_rus_l;
  uint8_t index_rus_m;
  uint8_t index_rus_n;
  uint8_t index_rus_p;
  uint8_t index_rus_t;
  uint8_t index_rus_u;
  uint8_t index_rus_f;
  uint8_t index_rus_ts;
  uint8_t index_rus_ch;
  uint8_t index_rus_sh;
  uint8_t index_rus_sch;
  uint8_t index_rus_tverd_mal;
  uint8_t index_rus_y;
  uint8_t index_rus_myagk_mal;
  uint8_t index_rus_ee;
  uint8_t index_rus_yu;
  uint8_t index_rus_ya;
};

extern const uint8_t rus_B[];
extern const uint8_t rus_G[];
extern const uint8_t rus_D[];
extern const uint8_t rus_ZH[];
extern const uint8_t rus_Z[];
extern const uint8_t rus_I[];
extern const uint8_t rus_II[];
extern const uint8_t rus_L[];
extern const uint8_t rus_P[];
extern const uint8_t rus_U[];
extern const uint8_t rus_F[];
extern const uint8_t rus_TS[];
extern const uint8_t rus_CH[];
extern const uint8_t rus_SH[];
extern const uint8_t rus_SCH[];
extern const uint8_t rus_tverd[];
extern const uint8_t rus_Y[];
extern const uint8_t rus_myagk[];
extern const uint8_t rus_EE[];
extern const uint8_t rus_YU[];
extern const uint8_t rus_YA[];
extern const uint8_t rus_b[];
extern const uint8_t rus_v[];
extern const uint8_t rus_g[];
extern const uint8_t rus_d[];
extern const uint8_t rus_yo[];
extern const uint8_t rus_zh[];
extern const uint8_t rus_z[];
extern const uint8_t rus_i[];
extern const uint8_t rus_ii[];
extern const uint8_t rus_k[];
extern const uint8_t rus_l[];
extern const uint8_t rus_m[];
extern const uint8_t rus_n[];
extern const uint8_t rus_p[];
extern const uint8_t rus_t[];
extern const uint8_t rus_u[];
extern const uint8_t rus_f[];
extern const uint8_t rus_ts[];
extern const uint8_t rus_ch[];
extern const uint8_t rus_sh[];
extern const uint8_t rus_sch[];
extern const uint8_t rus_tverd_mal[];
extern const uint8_t rus_y[];
extern const uint8_t rus_myagk_mal[];
extern const uint8_t rus_ee[];
extern const uint8_t rus_yu[];
extern const uint8_t rus_ya[];

extern wchar_t char_utf8[];
