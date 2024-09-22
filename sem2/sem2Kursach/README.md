# Исходный код курсовой "Крестики-нолики"

В этом репозитории находится исходный код для курсовой работы. 

## Структура проекта

Проект состоит из нескольких подпроектов.

### Подпроект tttlib

В подпроекте `tttlib` содержится библиотека, реализующую игровую логику. В этой
библиотеке определены базовые классы для игрока и наблюдателя, общие для всех
студентов.

В подпроекте есть следующие важные заголовочные файлы:

- `types.h` определяет простые типы данных, используемые в библиотеке;
- `field.h` определяет интерфейс для игрового поля;
- `events.h` определяет игровые события;
- `game_state.h` определяет классы для игровых настроек, состояния игры и наблюдателя 
за этим состоянием;
- `player.h` определяет базовый класс для игрока;
- `game_engine.h` определяет игровой движок.

Также в подпроекте содержатся автоматические тесты в папке `tests`.

### Подпроект tttplayer

В этом проекте каждый студент должен реализовать своего игрока.

## Сборка

Для сборки необходим `CMake 3.8+`.

### Сборка для Visual Studio

Для начала необходимо скачать проект. Это можно сделать двумя способами.

- Скачать проект в виде ZIP-архива. Для этого нужно нажать на зеленую кнопку
  `Code` и там выбрать ZIP архив.
- Склонировать проект с помощью Visual Studio. Для этого нужно нажать зеленую
  кнопку `Code`, оттуда скопировать https-ссылку; после этого нужно открыть
  Visual Studio, выбрать там "Клонирование репозитория", выбрать папку и
  вставить https-ссылку в поле "Расположение репозитория".

После этого нужно открыть этот проект, используя *представление папки*, 
выбрать самый верхний `CMakeLists.txt`, после чего выполнить сборку. Возможно,
перед сборкой потребуется создать кеш CMake.

Когда сборка завершится, можно выполнить тесты, чтобы проверить, успешно ли все
собралось. Для этого нужно выбрать "Тест"->"Запустить CTest для TicTacToe". 

В результате в консоль должно быть выведено "100% tests passed...".

### Сборка для Unix

```sh
mkdir build
cd build
cmake ..
make
```

Выполнение автотестов (после сборки проекта):

```sh
cd build
ctest
# or
make test
```