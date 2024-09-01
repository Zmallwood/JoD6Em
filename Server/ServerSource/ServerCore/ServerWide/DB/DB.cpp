/*
 * DB.cpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#include "DB.hpp"

namespace JoD {
namespace {
    pqxx::connection c(
        "host=localhost port=5432 dbname=jod user=jod_user password=testtest");
}

DB::DB() {
    SetupDB();
}

void DB::RegisterNewUser(std::string_view userName, int passwordHash) {
    pqxx::work txn(c);
    
    txn.exec_prepared0("insert_account", userName, passwordHash);
    
    pqxx::result r = txn.exec(
        "SELECT id "
        "FROM Account "
        "WHERE username =" + txn.quote(userName) + " order by id desc limit 1");
    
    if (r.size() != 1){
        std::cerr
            << "Expected 1 account with username '" <<  userName << "', "
            << "but found " << r.size() << std::endl;
        return;
    }
    
    /*
       int account_id = r[0][0].as<int>();
       std::cout << "Updating account#" << account_id << std::endl;

       txn.exec(
        "UPDATE ACCOUNT "
        "SET passwordHash = passwordHash+ 1 "
        "WHERE id = " + txn.quote(account_id));

     */
    txn.commit();
}


bool DB::TryLoginUser(std::string_view userName, int passwordHash) {
    
    pqxx::work txn(c);
    
    pqxx::result r = txn.exec(
        "SELECT id "
        "FROM Account "
        "WHERE username =" + txn.quote(userName) + " AND passwordHash = " +
        std::to_string(passwordHash) + " order by id desc limit 1");
    
    if (r.size() != 1){
        std::cerr
            << "Expected 1 account with username '" <<  userName << "', "
            << "but found " << r.size() << std::endl;
        return false;
    }
    return true;
}

void DB::SetupDB() {
    {
        pqxx::work txn(c);
        
        pqxx::result r = txn.exec(
            "create table if not exists account(id serial primary key, username text, passwordHash integer)");
        
        txn.commit();
        
        
        c.prepare(
            "insert_account",
            "insert into account(username, passwordHash) values($1, $2)");
        
    }
    
}
}
