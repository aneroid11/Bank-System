# Банковская система
__Язык: C++__  
__Фреймворк: Qt__  
__Возможности:__
1. Имитировать работу банковской системы с возможностями работы с вкладами клиентов:
   * Создание;
   * Хранение;
   * Снятие;
   * Перевод;
   * Накопление;
   * Блокировка;
   * Заморозка.
2. Возможности выдачи кредитов и рассрочек с индивидуальным и фиксированным процентом переплат по следующим условиям:
   * 3 месяца;
   * 6 месяцев;
   * 12 месяцев;
   * 24 месяца;
   * Более 24 месяцев.
3. Использование базы данных SQLite с расширением SQLCipher для шифрования данных.
4. Функционал зарплатного проекта для предприятия.
5. Роли пользователей:
   - Клиент
     - Может зарегистрироваться в системе (требуется апрув менеджера);
     - Может взаимодействовать со счетами (открывать, закрывать и т.д.);
     - Оформлять кредиты и рассрочки (требуется апрув менеджера);
     - Подать заявку на зарплатный проект от предприятия.
   - Оператор
     - Может просматривать статистику по движениям средств пользователей и 1 раз отменить действие по счёту (любой перевод кроме снятия наличных);
     - Подтверждает Заявку на зарплатный проект после получения данных от предприятия.
   - Менеджер
     - Функционал оператора;
     - Подтверждение кредитов и рассрочек;
     - Отмена операций произведённым специалистом стороннего предприятия;
   - Специалист стороннего предприятия
     - Подача документов на зарплатный проект;
     - Запрос на перевод средств другому предприятию или сотруднику его предприятия.
   - Администратор
     - Просмотр всех логов действий (логи могут быть в отдельном файле и зашифрованы);
     - Отмена всех действий пользователей.
  
![image](https://user-images.githubusercontent.com/73517902/223437304-9eb9cbc2-c77a-4aef-8377-f6c25a8742ad.png)  
  
![image](https://user-images.githubusercontent.com/73517902/223437504-b7f1fa38-a90c-4c3a-bcf2-3a84b69ac84a.png)  
  
![image](https://user-images.githubusercontent.com/73517902/223437967-aecc9735-3f16-4498-a9c3-26bc5d05dbcf.png)  
  
![image](https://user-images.githubusercontent.com/73517902/223438225-5a81bc93-0552-4068-a001-a5beb5019cb4.png)  

