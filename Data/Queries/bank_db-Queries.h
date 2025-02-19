#ifndef QUERIES_H
#define QUERIES_H

#include "../../Core/Libs/dataConfig.h"

namespace Queries
{
    // Accounts
    const string CREATE_ACCOUNTS_TABLE =
        "CREATE TABLE IF NOT EXISTS accounts ("
        "account_id SERIAL PRIMARY KEY, "
        "client_id INT NOT NULL REFERENCES clients(client_id) ON DELETE CASCADE, "
        "balance NUMERIC(15,2) DEFAULT 0.00 CHECK (balance >= 0), "
        "currency VARCHAR(3) NOT NULL DEFAULT 'RUB', "
        "opened_date DATE NOT NULL DEFAULT CURRENT_DATE, "
        "closed_date DATE CHECK (closed_date IS NULL OR closed_date > opened_date), "
        "status VARCHAR(20) DEFAULT 'ACTIVE' CHECK (status IN ('ACTIVE', 'FROZEN', 'CLOSED')));";

    const string INSERT_ACCOUNT =
        "INSERT INTO accounts (accountId, clientId, balance, currency, openedDate, closedDate, status) "
        "VALUES ($1, $2, $3, $4, $5, $6, $7)";

    const string GET_ACCOUNTS_BY_CLIENT =
        "SELECT * FROM bank_system.accounts WHERE client_id = $1;";

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
    const string CREATE_CLIENTS_TABLE =
        "CREATE TABLE IF NOT EXISTS clients ("
        "client_id SERIAL PRIMARY KEY, "
        "first_name VARCHAR(50) NOT NULL, "
        "last_name VARCHAR(50) NOT NULL, "
        "passport_number VARCHAR(20) UNIQUE NOT NULL, "
        "phone VARCHAR(20) UNIQUE NOT NULL, "
        "email VARCHAR(100) UNIQUE NOT NULL, "
        "registration_date DATE DEFAULT CURRENT_DATE);";

    const string INSERT_CLIENT =
        "INSERT INTO clients (first_name, last_name, passport_number, phone, email) "
        "VALUES ($1, $2, $3, $4, $5) RETURNING client_id;";

    const string GET_ALL_CLIENTS = "SELECT * FROM bank_system.clients;";

    // Operation Types
    const string CREATE_OPERATION_TYPES_TABLE =
        "CREATE TABLE IF NOT EXISTS operation_types ("
        "operation_type_id SERIAL PRIMARY KEY, "
        "name VARCHAR(50) NOT NULL UNIQUE, "
        "is_income BOOLEAN NOT NULL, "
        "needs_approval BOOLEAN DEFAULT FALSE);";

    const string INSERT_OPERATION_TYPE =
        "INSERT INTO operation_types (name, is_income, needs_approval) "
        "VALUES ($1, $2, $3) RETURNING operation_type_id;";

    const string GET_ALL_OPERATION_TYPES = "SELECT * FROM bank_system.operation_types;";

    // Transactions
    const string CREATE_TRANSACTIONS_TABLE =
        "CREATE TABLE IF NOT EXISTS transactions ("
        "transaction_id SERIAL PRIMARY KEY, "
        "from_account_id INT REFERENCES accounts(account_id), "
        "to_account_id INT NOT NULL REFERENCES accounts(account_id), "
        "amount NUMERIC(15,2) NOT NULL CHECK (amount > 0), "
        "operation_type INT NOT NULL, "
        "transaction_date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP, "
        "description TEXT, "
        "status VARCHAR(20) DEFAULT 'PENDING' CHECK (status IN ('PENDING', 'COMPLETED', 'CANCELED')));";

    const string INSERT_TRANSACTION =
        "INSERT INTO transactions (from_account_id, to_account_id, amount, operation_type, description) "
        "VALUES ($1, $2, $3, $4, $5) RETURNING transaction_id;";

    const string GET_TRANSACTIONS_BY_ACCOUNT =
        "SELECT * FROM bank_system.transactions WHERE from_account_id = $1 OR to_account_id = $1;";
}

#endif