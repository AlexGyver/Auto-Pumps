/*
   Система управляет количеством помп PUPM_AMOUNT, подключенных подряд в пины платы, начиная с пина START_PIN.
   На каждую помпу заводится таймер, который включает помпу на заданное время через заданные промежутки времени.
   Промежутки времени (период работы) может быть в часах или минутах (настройка PERIOD).
   Время работы помпы может быть в минутах или секундах (настройка PUMPING).
   Включение производится сигналом уровня SWITCH_LEVEL. 0 - для реле низкого уровня (0 Вольт, все семейные модули реле),
   1 - высокого уровня (5 Вольт, редкие модули реле, все мосфеты).
   Примечание: катушка реле кушает около 60 мА, несколько включенных вместе катушек создадут лишнюю нагрузку
   на линию питания. Также несколько включенных одновременно помп сделают то же самое. Для устранения этого эффекта
   есть настройка PARALLEL. При её отключении помпы будут "вставать в очередь", совместное включение будет исключено.

   Управление:
   Нажатие на ручку энкодера - переключение выбора помпы/периода/времени работы
   Поворот ручки энкодера - изменение значения
   Кнопка энкодера удерживается при включении системы - сброс настроек

   Интерфейс отображается на дисплее 1602 с драйвером на I2C. Версий драйвера существует две.
   Смотри настройку DRIVER_VERSION ниже.
*/

#define DRIVER_VERSION 0    // 0 - маркировка драйвера дисплея кончается на 4АТ, 1 - на 4Т
#define PUPM_AMOUNT 8       // количество помп, подключенных через реле/мосфет
#define START_PIN 3         // подключены начиная с пина
#define SWITCH_LEVEL 0      // реле: 1 - высокого уровня (или мосфет), 0 - низкого
#define PARALLEL 0          // 1 - параллельный полив, 0 - полив в порядке очереди
#define TIMER_START 0       // 1 - отсчёт периода с момента ВЫКЛЮЧЕНИЯ помпы, 0 - с момента ВКЛЮЧЕНИЯ помпы

#define PERIOD 0            // 1 - период в часах, 0 - в минутах
#define PUMPING 1           // 1 - время работы помпы в секундах, 0 - в минутах

#define DROP_ICON 1         // 1 - отображать капельку, 0 - будет буква "t" (time)

// названия каналов управления. БУКВУ L НЕ ТРОГАТЬ БЛЕТ!!!!!!
static const wchar_t *relayNames[]  = {
  L"Pump 1",
  L"Pump 2",
  L"Pump 3",
  L"Помпа 4",
  L"Огурцы",
  L"Помидоры",
  L"Клубника",
  L"Папин куст",
};

#define CLK 0
#define DT 1
#define SW 2

#include "GyverEncoder.h"
Encoder enc1(CLK, DT, SW);

#include <EEPROMex.h>
#include <EEPROMVar.h>

#include "LCD_1602_RUS.h"

// -------- АВТОВЫБОР ОПРЕДЕЛЕНИЯ ДИСПЛЕЯ-------------
// Если кончается на 4Т - это 0х27. Если на 4АТ - 0х3f
#if (DRIVER_VERSION)
LCD_1602_RUS lcd(0x27, 16, 2);
#else
LCD_1602_RUS lcd(0x3f, 16, 2);
#endif
// -------- АВТОВЫБОР ОПРЕДЕЛЕНИЯ ДИСПЛЕЯ-------------
unsigned long pump_timers[PUPM_AMOUNT];

unsigned int pumping_time[PUPM_AMOUNT];
unsigned int period_time[PUPM_AMOUNT];
unsigned int time_left[PUPM_AMOUNT];
boolean pump_state[PUPM_AMOUNT];
byte pump_pins[PUPM_AMOUNT];

byte current_set = 2;
byte current_pump;
boolean reDraw_flag, arrow_update;
boolean now_pumping;
unsigned int period_coef, pumping_coef;

void setup() {
  // --------------------- КОНФИГУРИРУЕМ ПИНЫ ---------------------
  for (byte i = 0; i < PUPM_AMOUNT; i++) {            // пробегаем по всем помпам
    pump_pins[i] = START_PIN + i;                     // настраиваем массив пинов
    pinMode(START_PIN + i, OUTPUT);                   // настраиваем пины
    digitalWrite(START_PIN + i, !SWITCH_LEVEL);       // выключаем от греха
  }
  // --------------------- ИНИЦИАЛИЗИРУЕМ ЖЕЛЕЗО ---------------------
  //Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  enc1.setStepNorm(1);

  // --------------------- СБРОС НАСТРОЕК ---------------------
  if (!digitalRead(SW)) {          // если нажат энкодер, сбросить настройки до 1
    lcd.setCursor(0, 0);
    lcd.print("Reset settings");
    for (byte i = 0; i < 100; i++) {
      EEPROM.updateByte(i, 1);
    }
  }
  while (!digitalRead(SW));        // ждём отпускания кнопки
  lcd.clear();                     // очищаем дисплей, продолжаем работу

  // --------------------------- НАСТРОЙКИ ---------------------------
  if (PERIOD) period_coef = 1000 * 60 * 60;  // перевод в часы
  else period_coef = 1000 * 60;              // перевод в минуты

  if (PUMPING) pumping_coef = 1000;          // перевод в секунды
  else pumping_coef = 1000 * 60;             // перевод в минуты

  // в ячейке 100 должен быть записан флажок 1, если его нет - делаем (ПЕРВЫЙ ЗАПУСК)
  if (EEPROM.read(100) != 1) {
    EEPROM.writeByte(100, 1);

    // для порядку сделаем 1 ячейки с 0 по 99
    for (byte i = 0; i < 100; i++) {
      EEPROM.writeByte(i, 1);
    }
  }

  for (byte i = 0; i < PUPM_AMOUNT; i++) {            // пробегаем по всем помпам
    period_time[i] = EEPROM.readByte(2 * i);          // читаем данные из памяти. На чётных - период (ч)
    pumping_time[i] = EEPROM.readByte(2 * i + 1);     // на нечётных - полив (с)
  }

  // ---------------------- ВЫВОД НА ДИСПЛЕЙ ------------------------
  // вывести буквенные подписи
  lcd.setCursor(1, 0);
  //lcd.print("Pump #");
  lcd.print(relayNames[0]);
  lcd.setCursor(1, 1);
  lcd.print("Prd: ");
  lcd.setCursor(10, 1);
  lcd.print("t");
  lcd.print(": ");

  arrow_update = true;        // флаг на обновление стрелочки
  reDraw();                   // вывести на дисплей
  reDraw();                   // вывести на дисплей (флаг стрелок сбросился, выведем числа...)
}

void loop() {
  encoderTick();
  periodTick();
  flowTick();
}

void periodTick() {
  for (byte i = 0; i < PUPM_AMOUNT; i++) {            // пробегаем по всем помпам
    if ( (millis() - pump_timers[i] > ( (long)period_time[i] * period_coef) )
         && (pump_state[i] != SWITCH_LEVEL)
         && !(now_pumping * !PARALLEL)) {
      pump_state[i] = SWITCH_LEVEL;
      digitalWrite(pump_pins[i], SWITCH_LEVEL);
      pump_timers[i] = millis();
      now_pumping = true;
    }
  }
}

void flowTick() {
  for (byte i = 0; i < PUPM_AMOUNT; i++) {            // пробегаем по всем помпам
    if ( (millis() - pump_timers[i] > ( (long)pumping_time[i] * pumping_coef) )
         && (pump_state[i] == SWITCH_LEVEL) ) {
      pump_state[i] = !SWITCH_LEVEL;
      digitalWrite(pump_pins[i], !SWITCH_LEVEL);
      if (TIMER_START) pump_timers[i] = millis();
      now_pumping = false;
    }
  }
}

void encoderTick() {
  enc1.tick();                  // отработка энкодера

  if (enc1.isRelease()) {        // если был нажат
    arrow_update = true;        // флаг на обновление стрелочки
    reDraw();                   // обновить дисплей
  }

  if (enc1.isTurn()) {                               // если был совершён поворот
    switch (current_set) {                           // смотрим, какая опция сейчас меняется
      case 0:                                        // если номер помпы
        current_pump = enc1.normCount;               // получить значение с энкодера
        break;
      case 1:                                        // если период работы помпы
        period_time[current_pump] = enc1.normCount;  // получить значение с энкодера
        break;
      case 2:                                        // если время работы помпы
        pumping_time[current_pump] = enc1.normCount; // получить значение с энкодера
        break;
    }
    reDraw();                                        // обновить дисплей
  }
}

void reDraw() {
  if (arrow_update) {                            // если изменился режим выбора
    if (++current_set > 2)                       // менять current_set в пределах 0.. 2
      current_set = 0;
    if (current_set == 0) update_EEPROM();       // если переключилиссь на выбор помпы, обновить данные
    switch (current_set) {                       // смотрим, какая опция сейчас выбрана
      case 0:                                    // если номер помпы
        enc1.setCounterNorm(current_pump);       // говорим энкодеру работать с номером помпы
        enc1.setLimitsNorm(0, PUPM_AMOUNT - 1);  // ограничиваем
        // стереть предыдущую стрелочку и нарисовать новую
        lcd.setCursor(0, 0); lcd.write(126); lcd.setCursor(9, 1); lcd.print(" ");
        break;
      case 1:
        enc1.setCounterNorm(period_time[current_pump]);
        enc1.setLimitsNorm(1, 99);
        lcd.setCursor(0, 1); lcd.write(126); lcd.setCursor(0, 0); lcd.print(" ");
        break;
      case 2:
        enc1.setCounterNorm(pumping_time[current_pump]);
        enc1.setLimitsNorm(1, 99);
        lcd.setCursor(9, 1); lcd.write(126); lcd.setCursor(0, 1); lcd.print(" ");
        break;
    }
    arrow_update = false;
  } else {
    // вывести все цифровые значения на их места
    //lcd.setCursor(7, 0);
    //lcd.print(current_pump);
    lcd.setCursor(1, 0);
    lcd.print("              ");
    lcd.setCursor(1, 0);
    lcd.print(relayNames[current_pump]);
    
    lcd.setCursor(5, 1);
    lcd.print(period_time[current_pump]);
    if (PERIOD) lcd.print("h ");
    else lcd.print("m ");
    lcd.setCursor(12, 1);
    lcd.print(pumping_time[current_pump]);
    if (PUMPING) lcd.print("s ");
    else lcd.print("m ");
    /*
        Serial.print("Pump #"); Serial.print(current_pump);

            if (PERIOD) Serial.print(" hrs, period: ");
            else Serial.print(" min, period: ");
            Serial.print(period_time[current_pump]);

            if (PUMPING) Serial.print(" sec, flow: ");
            else Serial.print(" min, flow: ");
            Serial.println(pumping_time[current_pump]);
    */
  }
}

// обновляем данные в памяти
void update_EEPROM() {
  EEPROM.updateByte(2 * current_pump, period_time[current_pump]);
  EEPROM.updateByte(2 * current_pump + 1, pumping_time[current_pump]);
}
