# Communicator (Макар Семенов)
* Клиент
    + Реализовал GUI интерфейс 
    + Доработал интерфейс под требования ТЗ
    + Добавил историю сообщенений
    + Реализовал шифрование учетных данных(паролей) со стороны клиента при регистрации (FAQ6 Hash)
    + Добавил временной штамп в историю сообщений
    + Реализовал базовый сетевой функционал клиент-части(Клиент будет работать в двух потоках. Один для чтения сообщений, другой для отправки)
    + Реализовал класс для сериализации/десериализации текстовых данных
* Сервер
    + Реализовал базовый сетевой функционал сервер-части(Сервер будет работать в двух потоках, для отправки сообщений клиентам)
