#include <iostream>
#include <sys/mman.h>

namespace stashii{
    template<typename T>
    class mvec{
        public:
        mvec() noexcept: data(new T[1]), size(0), capacity(1){}
        mvec(const T &def) noexcept: data(new T[1]), size(0), capacity(1){
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

        ~mvec(){
            delete[] data;
        }

        mvec& operator=(const mvec& other) noexcept{
            std::copy(other.data, other.data + other.size, data);
            size = other.size;
            capacity = other.capacity;

            return *this;
        }

        mvec& operator=(mvec&& other) noexcept{
            std::copy(other.data, other.data + other.size, data);
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 1;

            return *this;
        }

        void push_back(const T& value){
            if (size + 1 == capacity){
                capacity += 5;
                std::copy(data, data + capacity, data);
            }
            data[size] = value;
            size++;
        }

        void emplace_back(const std::initializer_list<T> &l){
            if (size + l.size() == capacity){
                capacity += l.size;
                std::copy(data, data + capacity + l.size(), data);
            }
            size += l.size();
            for (auto &i: l){
                push_back(i);
            }
        }

        void del_num(size_t index){
            if (index > size)
                throw (std::out_of_range("DEL_NUM: Position cannot been more than size"));
            std::swap(data[size - 1], data[index]);
            pop_back();
        }

        void clear(){
            data = new T[1];
            size = 0;
            capacity = 1;
        }

        mvec& at(size_t pos){
            if (pos > size)
                throw (std::out_of_range("at(): Position cannot been more than size"));
            return data[pos];
        }

        T& operator[](size_t pos){
            if (pos > size)
                throw (std::out_of_range("operator[]: Position cannot been more than size"));
            return data[pos];
        }

        const size_t& get_size() noexcept{
            return size;
        }

        const size_t& get_capacity() noexcept{
            return capacity;
        }

        void pop_back() noexcept{
            size--;
        }

        void resize(size_t new_size) noexcept{
            if ((new_size > capacity - 1)||(new_size > size)){
                size = new_size;
                capacity = new_size + 1;
            }
        }

        private:
        T* data;
        size_t size;
        size_t capacity;
    };
}
