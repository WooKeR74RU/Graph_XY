# Graph_XY
Построитель графиков функций в декартовой системе координат.

![Graph_XY](https://imgur.com/OU1FKQT.png)

### Как пользоваться?

* Ввести список функций в **functions.txt**.  
* Запустить **Graph_XY.exe**.

Собранная версия в папке **Test build**.

Формат файла **functions.txt**:  
<количество функций>  
[x | y]=[<выражение не содержащее x > | <выражение не содержащее y>] <цвет графика этой функции>  
**Выражения вводятся без пробелов.**

Пример **functions.txt** со скриншота:  
*3  
x=cos(3*y)+sin(y) Aqua  
y=3*sin(x) Lime  
y=x^2 Red*

### Управление

**W** - переместить отображаемую область вверх  
**A** - переместить отображаемую область влево  
**S** - переместить отображаемую область вниз  
**D** - переместить отображаемую область вправо  
**стрелка вверх** - увеличить масштаб  
**стрелка вниз** - уменьшить масштаб  
**колесико мыши вверх** - увеличить масштаб  
**колесико мыши вниз** - уменьшить масштаб  
**1** - переместить указатель на предыдущий график  
**2** - переместить указатель на следующий график  

Поддерживаемые операции: *abs*, *sqrt*, *ln*, *lg*, *log*, *sin*, *cos*, *tg*, *ctg*, *arcsin*, *arccos*, *arctg*, *arcctg*

Цвета:  
Aqua ![Aqua](https://placehold.it/15/00ffff/000000?text=+)
Black ![Black](https://placehold.it/15/000000/000000?text=+)
Blue ![Blue](https://placehold.it/15/0000ff/000000?text=+)
Fuchsia ![Fuchsia](https://placehold.it/15/ff00ff/000000?text=+)  
Gray ![Gray](https://placehold.it/15/808080/000000?text=+)
Green ![Green](https://placehold.it/15/008000/000000?text=+)
Lime ![Lime](https://placehold.it/15/00ff00/000000?text=+)
Maroon ![Maroon](https://placehold.it/15/800000/000000?text=+)  
Navy ![Navy](https://placehold.it/15/000080/000000?text=+)
Olive ![Olive](https://placehold.it/15/808000/000000?text=+)
Purple ![Purple](https://placehold.it/15/800080/000000?text=+)
Red ![Red](https://placehold.it/15/ff0000/000000?text=+)  
Silver ![Silver](https://placehold.it/15/C0C0C0/000000?text=+)
Teal ![Teal](https://placehold.it/15/008080/000000?text=+)
White ![White](https://placehold.it/15/ffffff/000000?text=+)
Yellow ![Yellow](https://placehold.it/15/ffff00/000000?text=+)
