#pragma once

namespace jod
{
    template <class T>
    T &_()
    {
        static T instance;
        return instance;
    }

    int Hash(std::string_view text);
}