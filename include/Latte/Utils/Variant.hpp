#pragma once

#include <variant>

template<typename ...Types>
class Variant: public std::variant<Types...>{
    public:
        using std::variant<Types...>::variant;

        template<typename T>
        bool is() const {
            return std::holds_alternative<T>(*this);
        }

        template<typename T>
        T to() const {
            return std::get<T>(*this);
        }

        template<typename T>
        const T* getIf() const {
            return std::get_if<T>(this);
        }

         template<typename T>
        bool operator == (const T &other) const{
            return to<T>()==other;
        }

        template<typename T>
        bool operator != (const T &other) const{
            return to<T>()!=other;
        }
        
        template<typename T>
        bool operator > (const T &other) const{
            return to<T>()>other;
        }

        template<typename T>
        bool operator >= (const T &other) const{
            return to<T>()>=other;
        }

        template<typename T>
        bool operator < (const T &other) const{
            return to<T>()<other;
        }

        template<typename T>
        bool operator <= (const T &other) const{
            return to<T>()<=other;
        }
};