# SearchEngine

## Итоговый проект от SkillBox на тему: "Реализация системы поиска по корпоративному порталу компании "АйТиБокс"

### Содержание
- [Введение](#введение)
- [Описание](#описание)
    * [Принципы работы поискового движка](#принципы-работы-поискового-движка)
- [Этапы разработки](#этапы-разработки)
- [Используемые технологии](#используемые-технологии)
- [Краткая инструкция пользователю](#краткая-инструкция-пользователю)
    * [Проверка](#проверка)
        + [Файл конфигурации config.json](#файл-конфигурации-configjson)
        + [Файл с запросами requests.json](#файл-с-запросами-requestsjson)
    * [Запуск](#запуск)
    * [Вывод](#вывод)
        + [Файл с ответами на запросы answers.json](#файл-с-ответами-на-запросы-answersjson)

### Введение
Этот проект является заключительным этапом в процессе моего обучения в [SkillBox](https://skillbox.ru/ "Сайт SkillBox") по программе "Разработчик на C++ с нуля".

Темой проекта является разработка системы поиска по корпоратировному порталу вымышленной компании "АйТиБокс". В целях выполнения итогового проекта необходимо разработать поисковый движок для корпоратировного портала компании. Этот движок является аналогом всеми известных в глобальной сети поисковых систем.

В данной работе продемонстрированы не только навыки, приобретенные за время обучения профессии: владение синтаксисом языка C++ и умение выстраивать архитектуру проекта, но и навыки в построении поисковых индексов, работа с конфигурационными файлами и даже написание набора тестов для проверки разработанного решения.

### Описание
Поисковый движок SearchEngine представляет собой консольное приложение, осуществляющее поиск и имеющее возможность настройки через файлы формата JSON. Вдальнейшем данный движок может быть использован в веб-разработке и по необходимости доработан заказчиком.

#### Принципы работы поискового движка

1. В конфигурационном файле перед запуском приложения задаются названия файлов, по которым движок осуществляет поиск.
2. Поисковый движок самостоятельно обходит все файлы и индексирует их таким образом, чтобы потом по любому поисковому запросу находить наиболее релевантные документы.
3. Пользователь задает запрос через JSON-файл __requests.json__. Запрос представляет собой набор слов, по которым нужно найти документы.
4. Запрос трансформируется в список слов.
5. В индексе ищутся те документы, в составе которых встречаются эти слова.
6. Результаты ранжируются, сортируются и отдаются пользователю. Максимальное количество возможных документов в ответе задается в конфигурационном файле __config.json__.
7. В конце работы приложение формирует файл __answers.json__, в который записывает результаты поиска.

### Этапы разработки

Поисковый движок разрабатан в 7 этапов:

**Этап 1. Подготовка**

&ensp;&ensp;&ensp;&ensp;<u>Цель этапа</u>: подготовка необходимого программного обеспечения для разработки.

**Этап 2. Разработка класса для взаимодействия с файлами JSON в описанном формате**

&ensp;&ensp;&ensp;&ensp;<u>Цель этапа</u>: добавление в созданный проект класса ConverterJSON для работы с файлами формата JSON.

**Этап 3. Подключение системы тестирования к проекту**

&ensp;&ensp;&ensp;&ensp;<u>Цель этапа</u>: подключение к проекту библиотеки Google Test для проведения автоматических модульных тестов.

**Этап 4. Создание инвертированного индекса для документов**

&ensp;&ensp;&ensp;&ensp;<u>Цель этапа</u>: реализация инвертированной индексации документов.

**Этап 5. Система индексации документов**

&ensp;&ensp;&ensp;&ensp;<u>Цель этапа</u>: реализация системы определения релевантности поискового запроса.

**Этап 6. Размещение в GitHub**

&ensp;&ensp;&ensp;&ensp;<u>Цель этапа</u>: научиться размещать проекты в публичном доступе для демонстрации при презентации проектов и при общении с потенциальными работодателями.

**Этап 7. Подготовка к сдаче проекта**

&ensp;&ensp;&ensp;&ensp;<u>Цель этапа</u>: подготовка проекта к сдаче на проверку куратору.

### Используемые технологии

|№<br>п/п|Параметр|Версия|
|:-:|:-|:-|
|1|Целевые ОС|Windows 10, Windows 11|
|2|Компилятор|GCC 13.2.0 (Rev6, Built by MSYS2 project)|
|3|Средство сборки|cmake версии 3.30.0-rc4|
|3|IDE|Visual Studio Code версии 1.90.2|
|4|СКВ|Git version 2.45.2.windows.1|
|5|C/C++ Extansion Pack|Идентификатор: [ms-vscode.cpptools-extension-pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack "C/C++ Extansion Pack - VS Code")<br>Версия: 1.3.0|
|6|CMake Tools|Идентификатор: [ms-vscode.cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools "CMake Tools - VS Code")<br>Версия: 1.18.42|
|7|Библиотека nlohmann_json|[Библиотека](https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz "Nlohmann-JSON - GitHub") версии 3.11.3|
|8|Google Test|[Библиотека](https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip "Google Test - GitHub") версии 1.12.1|

### Краткая инструкция пользователю

#### Проверка
Перед запуском проекта проверьте следующее:
- установлен GCC версии 13.2.0 (остальные версии GCC не тестировались);
- путь к _gcc.exe_ прописан в системных переменных среды;
- установлен cmake версии 3.30.0 (остальные версии cmake не тестировались)
- путь к _cmake.exe_ прописан в системных переменных среды;
- имеется доступ в сеть Интернет для загрузки библиотек JSON и GTest либо данные библиотеки уже подгружены в нужную директорию;
- в папке appendix созданы и заполнены файлы config.json и requests.json.

**Не забудьте удалить директорию resources или ее содержимое после копирования проекта!**

##### Файл конфигурации config.json
Без файла конфигурации запуск приложения невозможен. Он содержит название поискового движка, его версию и максимальное количество вариантов в ответе (если не указано, то значение выбирается равным пяти).
Пример описания файла _config.json_:

```json
{
    "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1",
        "max_responses": 5
    },
    "files": [
        "../resources/file001.txt",
        "../resources/file002.txt",
        "../resources/file003.txt",
        "../resources/file004.txt",
        ...
    ]
}
```

###### Подробнее:
- ___config___ - общая информация, без которой приложение не запускается. Если это поле отсутствует, то при старте программа должна выбросить исключение и вывести в текстовую консоль ошибку _config file is empty_. Если отсутствует сам файл config.json, то необходимо выбросить исключение и вывести ошибку _config file is missing_.
    * ___name___ - поле с названием поискового движка. Оно может быть любым. Информацию из данного поля необходимо отображать при старте приложения.
    * ___version___ - поле с номером версии поискового движка. _На данный момент не используется._
    * ___max_responses___ - поле, определяющее максимальное количество ответов на один запрос.
- ___files___ - поле с путями к файлами, по которым необходимо осуществлять поиск. Внутри списка files лежат пути к файлам (относительные или абсолютные).
    * ___<путь к файлу>___ ("..resources/file001.txt") - это путь к файлу, по содержимому которого необходимо совершить поиск. Если по этому пути файл не существует, то на экран выводится соответствующая ошибка, но выполнение программы не прекращается. При этом каждый документ содержит не более 1000 слов с максимальной длиной каждого в 100 символов. Слова состоят из строчных латинских букв и разделены одним или несколькими пробелами.

##### Файл с запросами requests.json
Файл содержит запросы, которые необходимо обработать поисковому движку.
Пример описания файла _requests.json_:
```json
{
    "requests": [
        "some words",
        "some words",
        "some words",
        "some words",
        ...
    ]
}
```

###### Подробнее:
- ___requests___ - поле, состоящее из списка запросов, которые необходимо обработать поисковым движком. Поле содержит не более 1000 запросов, каждый из которых включает от одного до десяти слов.
    * ___<содержимое запроса>___ ("some words") - поисковый запрос, набор слов, разделенных одним или несколькими пробелами, по которым необходимо совершить поиск. Все слова состоят из строчных латинских букв.

#### Запуск
Для запуска проекта необходимо выполнить конфигурацию CMake, далее выполнить сборку и после этого запустить исполняемый файл.

#### Вывод
В результате своей работы приложение формирует файл _answers.json_. 

##### Файл с ответами на запросы answers.json
В него записываются результаты работы поискового движка. Если при старте приложения в директории appendix не существует этого файла, то он будет создан. Если файл существует, то приложение сотрет все его содержимое.
Пример описания файла _answers.json_:
```json
{
    "answers": {
        "request001.txt": {
            "result": "true",
            "relevance": [
                { "docid": 0, "rank": 0.989 },
                { "docid": 1, "rank": 0.897 },
                { "docid": 2, "rank": 0.750 },
                { "docid": 3, "rank": 0.670 },
                { "docid": 4, "rank": 0.561 }
            ]
        },
        "request002": {
            "result": "true",
            "docid": 0,
            "rank": 0.769
        },
        "request003": {
            "result": "false"
        }
    }
}
```
###### Подробнее:
- ___answers___ - базовое поле в этом файле, которое содержит ответы на запросы.
    * ___request001 ... 003___ - идентификатор запроса, по которому сформирован ответ. Идентификатор запроса формируется автоматически по порядку, в котором находятся запросы в поле requests файла _requests.json_, начиная с 001.
        + ___result___ - результат поиска запроса. Если он принимает значение "true", значит по данному запросу найден хотя бы один документ, иначе поле принимает значение "false".
        + ___relevance___ - поле, включаемое в ответ на запрос в случае нахождения более одного документа.
        + ___docid___ - идентификатор документа, в котором найден ответ на запрос. Он формируется автоматически при индексации всех документов, исходя из порядка, в котором документы расположены в поле files в файле _config.json_, начиная с 0. В случае нахождения более одного релеватного документа поле находится в списке _relevance_ в составе неименованных ключей, иначе рядом с полем _result_. Не формируется при _result = "false"_.
        + ___rank___ - ранг или поисковый рейтинг. Это число показывает, насколько документ подходит для заданного запроса. Чем ближе это число к 1, тем релевантнее документ. В случае нахождения более одного релеватного документа поле находится в списке _relevance_ в составе неименованных ключей, иначе рядом с полем _result_. Не формируется при _result = "false"_.
