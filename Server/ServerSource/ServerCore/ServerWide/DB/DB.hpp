/*
 * DB.hpp
 * Copyright 2024 Andreas Åkerberg <zmallwood@proton.me>
 */

#pragma once

namespace JoD {
class DB {
  public:
    DB();
    
    void RegisterNewUser(std::string_view userName, int passwordHash);
    
  private:
    void SetupDB();
};
}
