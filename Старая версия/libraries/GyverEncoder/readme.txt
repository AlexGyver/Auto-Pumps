- **GyverEncoder (текущая 1.2)** - библиотека для отработки энкодера. Возможности:
	+ Класс **Encoder (CLK, DT, SW)** - подключение пинов
	+ **setType(type)** - установка типа энкодера. 0 - полушаговый, 1 - полношаговый
	+ **setCounters(norm, hold)** - установка значений для инкремента
	+ **setCounterNorm(norm), setCounterHold(hold)** - то же самое, но отдельно
	+ **setSteps(norm, hold)** - установка шага изменения
	+ **setStepNorm(norm), setStepHold(hold)** - то же самое, но отдельно
	+ **setLimitsNorm(normMin, normMax), setLimitsHold(holdMin, holdMax)** - пределы изменения
	+ **invert()** - инвертировать направление
	+ **tick()** - отработка (опрос)
	+ **isTurn(), isRight(), isLeft()** - отработка поворота
	+ **isRightH(), isLeftH()** - отработка поворота с нажатием
	+ **isPress(), isRelease(), isHolded(), isHold()** - отработка нажатия кнопки с антидребезгом
	+ **normCount, holdCount** - получить значение со встроенного инкрементора
	+ Отработка "нажатого поворота" - такого вы нигде не найдёте. Расширяет возможности энкодера ровно в 2 раза
	+ Имеет встроенный счётчик для поворота, всё можно настроить
	+ Настраиваемые пределы изменяемой величины, а также шаг изменения
	+ Пример использования в папке examples, показывает все возможности библиотеки