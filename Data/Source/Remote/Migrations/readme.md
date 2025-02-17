=======================
Расширенная документация к SQL-скрипту
Усовершенствованная банковская система
=======================

■ Что такое схемы в PostgreSQL?
-----------------------------------------
🔍 Схемы — это «виртуальные контейнеры» для организации объектов БД.
Аналогия:
  📂 Схема = Папка на компьютере
  📄 Таблицы/Функции = Файлы внутри папки

Основные преимущества:
✓ Изоляция объектов (возможность иметь таблицы с одинаковыми именами в разных схемах)
✓ Управление доступом (права на уровне схем)
✓ Логическая группировка (например: bank_system, reporting, analytics)

Пример из скрипта:
-- Создание отдельной схемы для банковской системы
DROP SCHEMA IF EXISTS bank_system CASCADE;  -- Удалить, если существует
CREATE SCHEMA bank_system;                 -- Создать новую
SET search_path TO bank_system;            -- Установить как рабочую область

■ Подробные примеры использования кода
-----------------------------------------

1. Создание доменов (типы данных с валидацией)
-- Доменный тип для номера телефона
CREATE DOMAIN phone_number AS VARCHAR(20)
CHECK (VALUE ~ '^\+?[0-9]{7,15}$');

Пример использования:
INSERT INTO clients (phone) VALUES ('+79001234567'); -- ✓ OK
INSERT INTO clients (phone) VALUES ('abc');          -- ❌ Ошибка валидации

2. Работа с клиентами
-- Добавление клиента с email
INSERT INTO clients (first_name, last_name, passport_number, phone, email)
VALUES ('Анна', 'Иванова', '1122334455', '+79161234567', 'anna@bank.ru');

-- Поиск по индексу (используется idx_clients_name)
SELECT * FROM clients 
WHERE last_name = 'Иванова' AND first_name = 'Анна'; -- ⚡ Быстрый поиск

3. Управление счетами
-- Создание нового счёта
INSERT INTO accounts (client_id, currency)
VALUES (1, 'USD'); -- Баланс по умолчанию 0.00

-- Заморозка счёта
UPDATE accounts SET status = 'FROZEN'
WHERE account_id = 1;

4. Транзакции и триггер
-- Перевод между счетами
INSERT INTO transactions (from_account_id, to_account_id, amount, operation_type)
VALUES (1, 2, 500.00, 1); -- operation_type=1 (Перевод)

Что происходит:
1) Триггер process_transaction проверяет тип операции
2) Если is_income=FALSE:
   - Списывает сумму с from_account_id
3) Меняет статус транзакции на COMPLETED
4) При ошибке (например, недостаточно средств):
   - Статус CANCELED
   - Ошибка записывается в лог PostgreSQL

5. Генерация карт через CTE
-- Создание клиента + счёта + карты в одной транзакции
WITH new_client AS (
    INSERT INTO clients (first_name, last_name, passport_number, phone, email)
    VALUES ('Алексей', 'Смирнов', '4455667788', '+79167778899', 'alex@bank.ru')
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
- Номер: 16 цифр (пример: 4765123498761234)
- Срок: текущая дата + 4 года

■ Примеры ошибок и их обработки
-----------------------------------------
1. Попытка перевода с недостаточным балансом:
INSERT INTO transactions (from_account_id, to_account_id, amount, operation_type)
VALUES (1, 2, 1000000.00, 1);

Результат:
⚠️ Статус транзакции: CANCELED
💬 Лог: "Transaction failed: New row violates CHECK constraint"

2. Неверный тип операции:
-- Попытка income-операции с from_account_id
INSERT INTO transactions (from_account_id, to_account_id, amount, operation_type)
VALUES (1, 2, 500.00, 2); -- operation_type=2 (Зарплата, is_income=TRUE)

Результат:
❌ Ошибка: нарушение CHECK-ограничения

■ Полный жизненный цикл транзакции
-----------------------------------------
1. Создание транзакции:
INSERT INTO transactions (from_account_id, to_account_id, amount, operation_type, status)
VALUES (1, 2, 1000.00, 1, 'PENDING');

2. Проверка баланса:
SELECT balance FROM accounts WHERE account_id = 1;

3. Подтверждение операции (симуляция):
UPDATE transactions SET status = 'COMPLETED'
WHERE transaction_id = 1;

4. Отмена транзакции:
UPDATE transactions SET status = 'CANCELED'
WHERE transaction_id = 1; -- Баланс не изменится

■ Продвинутые сценарии
-----------------------------------------
1. Получение выписки по счёту:
SELECT 
    t.transaction_date,
    CASE WHEN t.from_account_id = 1 THEN -t.amount ELSE t.amount END as amount,
    ot.name as operation,
    t.status
FROM transactions t
JOIN operation_types ot USING (operation_type_id)
WHERE 1 IN (t.from_account_id, t.to_account_id);

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