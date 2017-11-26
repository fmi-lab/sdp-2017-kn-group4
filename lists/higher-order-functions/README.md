Функции от по-висок ред върху списъци
=====================================

Шаблонни реализации на функциите [`map`](map.cpp),
[`filter`](filter.cpp), [`foldl`](foldl.cpp) и [`zip`](zip.cpp) за едносвързан
списък ([`std::forward_list`](http://en.cppreference.com/w/cpp/container/forward_list)).

Допълнителна задача
-------------------
Реализирайте функция `group_by(l, f)`, която групира елементите на списъка `l`
по различните стойности, върнати от функцията `f`, приложена над елементите на
`l`. Стойностите, върнати от `f`, ще наричаме ключове. Всяка група ще
представяме чрез наредена двойка, чиито първи и втори елемент са съответно
ключ `key` и списък от тези елементи `x` на `l`, които отговарят на условието
`f(x) == key`. `group_by` трябва да върне списък от групи.

  Пример:
  ```cpp
  std::forward_list<int> l = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  auto mod_3 = [](int x) { return x % 3; };
  std::forward_list<std::pair<int, std::forward_list<int>>> mod_3_groups = group_by(l, mod_3);
  // mod_3_groups е списъка {{0, {0, 3, 6}}, {1, {1, 4, 7}}, {2, {2, 5, 8}}}.
  ```

Полезни ресурси
---------------
- [Template argument deduction](http://en.cppreference.com/w/cpp/language/template_argument_deduction)

  Повече информация за това как компилаторът извежда типовете на шаблонните
  аргументи.

- [auto](http://en.cppreference.com/w/cpp/language/auto) - документация

- [decltype](http://en.cppreference.com/w/cpp/language/decltype) - документация

- [C++ auto and decltype Explained](http://thbecker.net/articles/auto_and_decltype/section_01.html)

  Тази статия дава добро обяснение на `auto` и `decltype`.
