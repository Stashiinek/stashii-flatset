#include <iostream>
#include <memory>
#include <algorithm>
#include <sys/mman.h>

namespace stashii{
    template<typename T>
    class mvec{
        public:
        mvec() noexcept: data(new T[1]), size(0), capacity(1){}
        mvec(const T &def) noexcept: data(new T[2]), size(1), capacity(2){
            data[0] = def;
        }
        
        mvec(const mvec& other): data(new T[other.size]){
            std::copy(other.data, other.data + other.size, data);
            size = other.size;
            capacity = other.capacity;
        }
        mvec(mvec&& other): data(new T[other.size]){
            std::copy(other.data, other.data + other.size, data);
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 1;
        }

        mvec(std::initializer_list<T> list){
            for (auto m : list){
                push_back(m);
            }
        }

        mvec& operator=(const mvec& other) noexcept{
            clear();
            std::copy(other.data, other.data + other.size, data);
            size = other.size;
            capacity = other.capacity;

            return *this;
        }

        mvec& operator=(mvec&& other) noexcept{
            clear();
            std::copy(other.data, other.data + other.size, data);
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 1;

            return *this;
        }

        ~mvec(){
            delete[] data;
        }

        void push_back(const T& value){
            if (size + 1 == capacity){
                capacity *= 2;
                std::copy(data, data + capacity, data);
            }
            data[size] = value;
            size++;
        }

        void del_num(size_t index){
            if (index > size)
                throw (std::out_of_range("DEL_NUM: Position cannot been more than size"));
            std::swap(data[size - 1], data[index]);
            pop_back();
        }

        void clear(){
            delete[] data;
            data = new T[1];
            size = 0;
            capacity = 1;
        }

        void pop_back() noexcept{
            std::swap(data[size], data[size - 1]);
            data[size].~T();
            size--;
            capacity;
        }

        void resize(size_t new_size) noexcept{
            if ((new_size > capacity - 1)||(new_size > size)){
                size = new_size;
                capacity = new_size + 1;
            }
        }

        bool exist(const T& f) noexcept{
            for (size_t i = 0; i < size; i++){
                if (data[i] == f)
                    return true;
            }
            return false;
        }

        T& at(size_t pos){
            if (pos > size)
                throw (std::out_of_range("at(): Position cannot been more than size"));
            return data[pos];
        }

        T& operator[](size_t pos){
            if (pos > size)
                throw (std::out_of_range("operator[]: Position cannot been more than size"));
            return data[pos];
        }

        T* operator->() noexcept{
            return this;
        }

        friend bool operator==(mvec& l, mvec& r) noexcept{
            if (l.size != r.size)
                return false;
            
            for (int i = 0; i < r.size; i++){
                if (l.at(i) != r.at(i))
                    return false;
            }
            return true;
        }

        friend bool operator!=(mvec& l, mvec& r) noexcept{
            if (l.size != r.size) return false;
            return !(l == r);
        }

        friend bool operator>(mvec& l, mvec& r) noexcept{
            return l->size > r.size;
        }

        friend bool operator<(mvec& l, mvec& r) noexcept{
            return l->size < r.size;
        }

        friend bool operator>=(mvec& l, mvec& r) noexcept{
            return !(l < r);
        }

        friend bool operator<=(mvec& l, mvec& r) noexcept{
            return !(l > r);
        }

        const size_t& get_size() noexcept{
            return size;
        }

        const size_t& get_capacity() noexcept{
            return capacity;
        }

        T* begin(){ return data; }
        T* last(){
            size_t cat = size - 1;
            return data + cat; } 
        T* end(){
            size_t cat = size - 1;
            return data + size; }

        T* find (const T& f) noexcept{
            for (size_t i = 0; i < size; i++){
                if (data[i] == f)
                    return data + i;
            }
            return data + size;
        }

        private:
        T* data;

        size_t size;
        size_t capacity;
    };
}
