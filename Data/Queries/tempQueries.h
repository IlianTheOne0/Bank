namespace TempQueries
{
    // Accounts
    const string INSERT_ACCOUNT =
        "INSERT INTO accounts (client_id, balance, currency, status) "
        "VALUES ($1, $2, $3, $4)";

    const string GET_ACCOUNT_BY_ACCOUNTID = "SELECT client_id, balance, currency, opened_date, closed_date, status FROM accounts WHERE account_id = $1";
    const string GET_ACCOUNT_BY_CLIENTID = "SELECT client_id, balance, currency, opened_date, closed_date, status FROM accounts WHERE client_id = $1";

    // Cards
    const string CREATE_CARDS_TABLE =
        "CREATE TABLE IF NOT EXISTS cards ("
        "card_id SERIAL PRIMARY KEY, "
        "account_id INT NOT NULL REFERENCES accounts(account_id) ON DELETE CASCADE, "
        "card_number CHAR(16) UNIQUE NOT NULL CHECK (card_number ~ '^[0-9]{16}$'), "
        "expiry_date DATE NOT NULL CHECK (expiry_date > CURRENT_DATE), "
        "is_blocked BOOLEAN NOT NULL DEFAULT FALSE, "
        "issue_date DATE NOT NULL DEFAULT CURRENT_DATE);";

    const string INSERT_CARD =
        "INSERT INTO cards (account_id, card_number, expiry_date) "
        "VALUES ($1, $2, $3) RETURNING card_id;";

    const string GET_CARDS_BY_ACCOUNT =
        "SELECT * FROM bank_system.cards WHERE account_id = $1;";

    // Clients
    const string INSERT_CLIENT =
        "INSERT INTO clients (first_name, last_name, passport_number, phone, email) "
        "VALUES ($1, $2, $3, $4, $5) RETURNING client_id;";

    const string GET_ALL_CLIENTS = "SELECT * FROM bank_system.clients;";

    // Operation Types
    const string INSERT_OPERATION_TYPE =
        "INSERT INTO operation_types (name, is_income, needs_approval) "
        "VALUES ($1, $2, $3) RETURNING operation_type_id;";

    const string GET_ALL_OPERATION_TYPES = "SELECT * FROM bank_system.operation_types;";

    // Transactions
    const string INSERT_TRANSACTION =
        "INSERT INTO transactions (from_account_id, to_account_id, amount, operation_type, description) "
        "VALUES ($1, $2, $3, $4, $5) RETURNING transaction_id;";

    const string GET_TRANSACTIONS_BY_ACCOUNT =
        "SELECT * FROM bank_system.transactions WHERE from_account_id = $1 OR to_account_id = $1;";
}