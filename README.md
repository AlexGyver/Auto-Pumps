![PROJECT_PHOTO](https://github.com/AlexGyver/Auto-Pumps/blob/master/proj_img.jpg)
# Многоканальная система автополива на Arduino своими руками
* [Описание проекта](#chapter-0)
* [Папки проекта](#chapter-1)
* [Схемы подключения](#chapter-2)
* [Материалы и компоненты](#chapter-3)
* [Как скачать и прошить](#chapter-4)
* [FAQ](#chapter-5)
* [Полезная информация](#chapter-6)
[![AlexGyver YouTube](http://alexgyver.ru/git_banner.jpg)](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)

<a id="chapter-0"></a>
## Описание проекта
Многоканальный автополив
Особенности:
- Поддержка от 1 до 15 помп (Arduino NANO / UNO)
- Индивидуальная настройка периода и времени работы
- Дисплей 1602 с отображением настроек
- Управление и настройка энкодером
- Хранение настроек в энергонезависимой памяти
- Настройка уровня управляющего сигнала
- Подробности в видео: https://youtu.be/nu31By9Phdc

<a id="chapter-1"></a>
## Папки
**ВНИМАНИЕ! Если это твой первый опыт работы с Arduino, читай [инструкцию](#chapter-4)**
- **libraries** - библиотеки проекта. Заменить имеющиеся версии
- **auto-pumps** - прошивка для Arduino, файл в папке открыть в Arduino IDE ([инструкция](#chapter-4))
- **schemes** - схемы подключения

<a id="chapter-2"></a>
## Схемы
### Обычная
![SCHEME](https://github.com/AlexGyver/ColorMusic/blob/master/schemes/scheme2.jpg)
### С микрофоном
![SCHEME](https://github.com/AlexGyver/ColorMusic/blob/master/schemes/scheme3.jpg)

<a id="chapter-3"></a>
## Материалы и компоненты
### Ссылки оставлены на магазины, с которых я закупаюсь уже не один год
### Почти все компоненты можно взять в магазине WAVGAT по первым ссылкам
* Arduino NANO с ногами http://ali.pub/2iaezd http://ali.pub/2iaezy
* Arduino NANO без ног http://ali.pub/2iaewn http://ali.pub/2iaey0
* Помпа 5V  http://ali.pub/2iaf0x  http://ali.pub/2iaf1w
* Помпа 12V http://ali.pub/2iaf41  http://ali.pub/2iaf5l
* Дисплей http://ali.pub/2iaf75  http://ali.pub/2iaf84
* Энкодер http://ali.pub/2iafdk  http://ali.pub/2iafe5
* Реле электромагнитное
  * 1 канал http://ali.pub/2iafsc
  * 2 канала http://ali.pub/2iaft4
  * 4 канала http://ali.pub/2iaftb
  * 8 каналов http://ali.pub/2iafua
  * 16 каналов http://ali.pub/2iafuo
* Реле твердотельное
  * 1 канал http://ali.pub/2iafwm
  * 2 канала http://ali.pub/2iafx0
  * 4 канала http://ali.pub/2iafxe
  * 8 каналов http://ali.pub/2iafxl
* Макетная плата http://ali.pub/2iafj7
* Джамперы папа-мама http://ali.pub/2iafkk
* Джамперы макетные http://ali.pub/2iafi1
* Блок питания 5V - любой зарядник для смартфона
* Блок питания 12V https://alexgyver.ru/converters/

* Разветвитель потока с краниками http://ali.pub/2iafzq
* Разветвитель потока без краников http://ali.pub/2iag1a
* Шланг силиконовый http://ali.pub/2iag2u
* Тройничок http://ali.pub/2iag5k

## Вам скорее всего пригодится
* [Всё для пайки (паяльники и примочки)](http://alexgyver.ru/all-for-soldering/)
* [Недорогие инструменты](http://alexgyver.ru/my_instruments/)
* [Все существующие модули и сенсоры Arduino](http://alexgyver.ru/arduino_shop/)
* [Электронные компоненты](http://alexgyver.ru/electronics/)
* [Аккумуляторы и зарядные модули](http://alexgyver.ru/18650/)

<a id="chapter-4"></a>
## Как скачать и прошить
* [Первые шаги с Arduino](http://alexgyver.ru/arduino-first/) - ультра подробная статья по началу работы с Ардуино, ознакомиться первым делом!
* Скачать архив с проектом
> На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**
* Установить библиотеки в  
`C:\Program Files (x86)\Arduino\libraries\` (Windows x64)  
`C:\Program Files\Arduino\libraries\` (Windows x86)
* Подключить Ардуино к компьютеру
* Запустить файл прошивки (который имеет расширение .ino)
* Настроить IDE (COM порт, модель Arduino, как в статье выше)
* Настроить что нужно по проекту
* Нажать загрузить
* Пользоваться  

## Настройки в коде
    #define DRIVER_VERSION 0    // 0 - маркировка драйвера дисплея кончается на 4АТ, 1 - на 4Т
    #define PUPM_AMOUNT 8       // количество помп, подключенных через реле/мосфет
    #define START_PIN 3         // подключены начиная с пина
    #define SWITCH_LEVEL 0      // реле: 1 - высокого уровня (или мосфет), 0 - низкого
    #define PARALLEL 0          // 1 - параллельный полив, 0 - полив в порядке очереди
    #define TIMER_START 0       // 1 - отсчёт периода с момента ВЫКЛЮЧЕНИЯ помпы, 0 - с момента ВКЛЮЧЕНИЯ помпы
    
    #define PERIOD 0            // 1 - период в часах, 0 - в минутах
    #define PUMPING 1           // 1 - время работы помпы в секундах, 0 - в минутах
    
    #define DROP_ICON 1         // 1 - отображать капельку, 0 - будет буква "t" (time)
    
<a id="chapter-5"></a>
## FAQ
### Основные вопросы
В: Как скачать с этого грёбаного сайта?  
О: На главной странице проекта (где ты читаешь этот текст) вверху справа зелёная кнопка **Clone or download**, вот её жми, там будет **Download ZIP**

В: Скачался какой то файл .zip, куда его теперь?  
О: Это архив. Можно открыть стандартными средствами Windows, но думаю у всех на компьютере установлен WinRAR, архив нужно правой кнопкой и извлечь.

В: Я совсем новичок! Что мне делать с Ардуиной, где взять все программы?  
О: Читай и смотри видос http://alexgyver.ru/arduino-first/

В: Вылетает ошибка загрузки / компиляции!
О: Читай тут: https://alexgyver.ru/arduino-first/#step-5

В: Сколько стоит?  
О: Ничего не продаю.

### Вопросы по этому проекту

<a id="chapter-6"></a>
## Полезная информация
* [Мой сайт](http://alexgyver.ru/)
* [Основной YouTube канал](https://www.youtube.com/channel/UCgtAOyEQdAyjvm9ATCi_Aig?sub_confirmation=1)
* [YouTube канал про Arduino](https://www.youtube.com/channel/UC4axiS76D784-ofoTdo5zOA?sub_confirmation=1)
* [Мои видеоуроки по пайке](https://www.youtube.com/playlist?list=PLOT_HeyBraBuMIwfSYu7kCKXxQGsUKcqR)
* [Мои видеоуроки по Arduino](http://alexgyver.ru/arduino_lessons/)