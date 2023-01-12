# DronsEngine2D

## В РАЗРАБОТКЕ НА НАЧАЛЬНОЙ СТАДИИ!

### DronsEngine2D - мой игровой движок для 2D игр, который я пишу при помощи C++&SFML.
По своей задумке это не должен быть убийца Godot, Unreal и т.д. по своей универсальности, удобству и функциональности. Я вижу этот проект как какой-то базовый фундамент движка (который я буду понимать "под капотом"), уже на основе которого я буду делать прототипы и сами игры. Т.е. в нем для этого уже будет базовая и оптимальная реализация игрового цикла, заготовки в архитектуре для мультиплеера, многопоточности и поддержки модов, уже какой-то набор функционала для работы с физикой, графикой, какой-то математикой и т.д.

## **TODO:**
- [x] *Игровой цикл с разделенной частотой обновления физики и всего остального:* `physicsUpdate, update, render, deltaTime`
- [x] *Фиксированный `viewport` под разные разрешения экрана*
- [x] *Класс для работы с ini файлами:* `INIFile`
- [x] *Класс логгер, а также главный логгер движка:* `Logger, GameLogger`
- - [ ] *Пересмотреть реализацию от `Singleton` в сторону `Service Locator`*
- [x] *Класс для состояний игры:* `GameState`
- [ ] *Двойной буффер рендеринга*
- [ ] *Класс для сериализации (желательно в бинарном виде):* `Serializable`
- [ ] *Класс (и структура данных) для локализации (например для строки в зависимости от языка будет выводить нужную из списка, определенном в файле):* `Localizable`
- [ ] *Класс для слоев отрисовки:* `RenderLayer`
- [ ] *Подумать над специальным механизмом управлением памяти в движке*
- [ ] *Подумать над реализацией компонентной системы в архитектуре движка: классы компоненты, сущности являются контейнерами для компонентов*
- [ ] *Обработка событий* `Observer` или `Event Queue`
- [ ] *Работа с медиа файлами: загрузка изображений, видео и аудио*
- [ ] *Простой UI для начала: `Button, Image, Label, TextBox` и т.д.*
- [ ] *Реализация класса `Object, Entity` и т.д. + подвязать под паттерн `Prototype`*
- [ ] *`State Machine` для определения логики состояний игровых обьектов или, например, анимаций этих объектов*
- [ ] *Подумать о реализации простого физического движка, возможно через `Observer` и `Singleton`*
- [ ] *Слои и маски для физического движка: `PhysicsLayer` и `PhysicsMask`*
- [ ] *Подумать о реализации и организации сцены/уровня и хранении в нем игровых объектов, вероятно через `Scene Graph` и пространственное разбиение*
- [ ] *Система активных в экране и неактивных за экраном игровых объектов*
- [ ] *Подумать над реализацией быстрой обработки и рендеринга карты из огромного кол-ва тайлов*
- [ ] *Подумать о реализации частичной многопоточности в движке: можно попытаться разделить некоторые компоненты движка по потокам, например физика, аудио и т.д*
- [ ] *Реализация поддержки пользовательских модификаций через `Lua`*
