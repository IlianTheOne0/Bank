=======================
Расширенная документация к SQL скрипту
Улучшенная банковская система
=======================

■ Что такое схемы (Schemas) в PostgreSQL?
-----------------------------------------
🔍 Схемы — это "виртуальные контейнеры" для организации объектов БД. 
Аналогия: 
  📂 Схема = Папка на компьютере
  📄 Таблицы/Функции = Файлы внутри папки

Основные преимущества:
✓ Изоляция объектов (можно иметь таблицы с одинаковыми именами в разных схемах)
✓ Управление правами доступа (разрешения на уровне схемы)
✓ Логическая группировка (например: bank_system, reporting, analytics)

Пример из скрипта:
-- Создание отдельной схемы для всей банковской системы
DROP SCHEMA IF EXISTS bank_system CASCADE;  -- Удалить если существует
CREATE SCHEMA bank_system;                 -- Создать новую
SET search_path TO bank_system;            -- Установить как рабочую область

■ Подробные примеры работы с кодом
-----------------------------------------

1. Создание доменов (типы данных с валидацией)
-- Домен для телефона
CREATE DOMAIN phone_number AS VARCHAR(20)
CHECK (VALUE ~ '^\+?[0-9]{7,15}$');

Пример использования:
INSERT INTO clients (phone) VALUES ('+79001234567'); -- ✓ OK
INSERT INTO clients (phone) VALUES ('abc');          -- ❌ Ошибка проверки

2. Работа с клиентами
-- Добавление клиента с email
INSERT INTO clients (first_name, last_name, passport_number, phone, email)
VALUES ('Anna', 'Ivanova', '1122334455', '+79161234567', 'anna@bank.ru');

-- Поиск по индексу (использует idx_clients_name)
SELECT * FROM clients 
WHERE last_name = 'Ivanova' AND first_name = 'Anna'; -- ⚡ Быстрый поиск

3. Управление счетами
-- Создание нового счета
INSERT INTO accounts (client_id, currency)
VALUES (1, 'USD'); -- Баланс 0.00 по умолчанию

-- Заморозка счета
UPDATE accounts SET status = 'FROZEN'
WHERE account_id = 1;

4. Транзакции и триггер
-- Перевод между счетами
INSERT INTO transactions (from_account, to_account, amount, operation_type)
VALUES (1, 2, 500.00, 1); -- operation_type=1 (Перевод)

Что происходит:
1) Триггер process_transaction проверяет тип операции
2) Если is_income=FALSE:
   - Списывает сумму с from_account
3) Меняет статус транзакции на COMPLETED
4) При ошибке (например, нехватка средств):
   - Статус CANCELED
   - Ошибка записывается в лог PostgreSQL

5. Генерация карт через CTE
-- Создание клиента + счета + карты в одной транзакции
WITH new_client AS (
    INSERT INTO clients (first_name, last_name, passport_number, phone)
    VALUES ('Alex', 'Smirnov', '4455667788', '+79167778899')
    RETURNING client_id
),
new_account AS (
    INSERT INTO accounts (client_id) 
    SELECT client_id FROM new_client
    RETURNING account_id
)
INSERT INTO cards (account_id, card_number, expiry_date)
SELECT 
    account_id,
    lpad((random()*10000000000000000)::bigint::text, 16, '0'),
    CURRENT_DATE + INTERVAL '4 years'
FROM new_account;

Результат:
💳 Автоматически сгенерированная карта:
- Номер: 16 цифр (например: 4765123498761234)
- Срок: текущая дата + 4 года

■ Примеры ошибок и обработка
-----------------------------------------
1. Попытка перевода с недостаточным балансом:
INSERT INTO transactions (from_account, to_account, amount, operation_type)
VALUES (1, 2, 1000000.00, 1);

Результат:
⚠️ Статус транзакции: CANCELED
💬 В логе: "Transaction failed: Новая строка в отношение ... нарушает ограничение CHECK"

2. Неправильный тип операции:
-- Попытка income-операции с from_account
INSERT INTO transactions (from_account, to_account, amount, operation_type)
VALUES (1, 2, 500.00, 2); -- operation_type=2 (Зарплата, is_income=TRUE)

Результат:
❌ Ошибка: CHECK-ограничение нарушено

■ Полный жизненный цикл транзакции
-----------------------------------------
1. Создание транзакции:
INSERT INTO transactions (from_account, to_account, amount, operation_type, status)
VALUES (1, 2, 1000.00, 1, 'PENDING');

2. Проверка баланса:
SELECT balance FROM accounts WHERE account_id = 1;

3. Одобрение операции (имитация):
UPDATE transactions SET status = 'COMPLETED'
WHERE transaction_id = 1;

4. Отмена транзакции:
UPDATE transactions SET status = 'CANCELED'
WHERE transaction_id = 1; -- Баланс не изменится

■ Расширенные сценарии
-----------------------------------------
1. Получение выписки по счету:
SELECT 
    t.transaction_date,
    CASE WHEN t.from_account = 1 THEN -t.amount ELSE t.amount END as amount,
    ot.name as operation,
    t.status
FROM transactions t
JOIN operation_types ot USING (operation_type_id)
WHERE 1 IN (t.from_account, t.to_account);

2. Поиск заблокированных карт:
SELECT 
    c.card_number,
    a.balance,
    cl.first_name || ' ' || cl.last_name as client
FROM cards c
JOIN accounts a USING (account_id)
JOIN clients cl USING (client_id)
WHERE c.is_blocked = TRUE;

3. Анализ операций за период:
SELECT 
    DATE(transaction_date) as day,
    COUNT(*) as total_transactions,
    SUM(amount) as total_amount
FROM transactions
WHERE transaction_date BETWEEN '2024-01-01' AND '2024-12-31'
GROUP BY day;

■ Советы по развитию системы
-----------------------------------------
1. Безопасность:
   🔒 Реализовать шифрование для card_number:
   CREATE EXTENSION pgcrypto;
   UPDATE cards SET card_number = pgp_sym_encrypt(card_number, 'secret_key');

2. Производительность:
   🚀 Добавить индексы:
   CREATE INDEX idx_transactions_date ON transactions(transaction_date);
   CREATE INDEX idx_accounts_status ON accounts(status);

3. Мониторинг:
   📊 Добавить представление для активных клиентов:
   CREATE VIEW active_clients AS
   SELECT * FROM clients
   WHERE client_id IN (SELECT DISTINCT client_id FROM accounts WHERE status = 'ACTIVE');