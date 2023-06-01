#include <iostream>
#include <memory>
#include <algorithm>
#include <sys/mman.h>

const size_t MAGIC_NUM = 32768; //2 ^ 15

namespace stashii{
    template<typename T>
    class mvec{
        public:
        mvec() noexcept: data(new T[1]), size(0), capacity(1){
            max_size = MAGIC_NUM / sizeof(T);
        }
        mvec(const T &def) noexcept: data(new T[1]), size(0), capacity(1){
            data[0] = def;
            max_size = MAGIC_NUM / sizeof(T);
        }
        
        mvec(const mvec& other): data(new T[other.size]){
            std::copy(other.data, other.data + other.size, data);
            size = other.size;
            capacity = other.capacity;
            max_size = MAGIC_NUM / sizeof(T);
        }
        mvec(mvec&& other): data(new T[other.size]){
            std::copy(other.data, other.data + other.size, data);
            size = other.size;
            capacity = other.capacity;
            max_size = MAGIC_NUM / sizeof(T);

            other.data = nullptr;
            other.size = 0;
            other.capacity = 1;
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

        ~mvec(){
            delete[] data;
        }

        void push_back(const T& value){
            if (size + 1 != MAGIC_NUM)
                if (size + 1 == capacity){
                    if (capacity + 5 > MAGIC_NUM)
                        capacity = MAGIC_NUM;
                    else capacity += 5;
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
            size--;
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

        T& find (const T& f) noexcept{
            for (size_t i = 0; i < size; i++){
                if (data[i] == f)
                    return data[i];
            }
            return data[size];
        }

        mvec& begin(){ return data[0];}
        mvec& end(){return data[size - 1];}

        mvec& rbegin(){ return data[size-1]; }
        mvec& rend(){ return data[0]; }

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

        T* operator->() noexcept{
            return this;
        }

        bool operator==(const mvec& r) noexcept{
            if (this->size != r.size)
                return false;
            
            for (int i = 0; i < r.size; i++){
                if (this->at(i) != r.at(i))
                    return false;
            }
            return true;
        }

        bool operator!=(const mvec& r) noexcept{
            return !(this == r);
        }

        bool operator>(const mvec& r) noexcept{
            return this->size > r.size;
        }

        bool operator<(const mvec& r) noexcept{
            return this->size < r.size;
        }

        bool operator>=(const mvec& r) noexcept{
            return !(this < r);
        }

        bool operator<=(const mvec& r) noexcept{
            return !(this > r);
        }

        const size_t& get_size() noexcept{
            return size;
        }

        const size_t& get_maxsize() noexcept{
            return max_size;
        }

        const size_t& get_capacity() noexcept{
            return capacity;
        }

        class mvecIterator{
            public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::forward_iterator_tag;

            explicit mvecIterator(std::shared_ptr<mvec<T>> other) : miauptr(other){}

            ~mvecIterator(){ miauptr.reset(); }

            // че сюда писать...

            friend bool operator==(const mvec& l, const mvec& r) noexcept{
                if (l.size != r.size)
                    return false;
                
                for (int i = 0; i < l.size; i++){
                    if (l.at(i) != r.at(i))
                        return false;
                }
                return true;
            }

            friend bool operator!=(const mvec& l, const mvec& r) noexcept{
                return !(l == r);
            }

            friend bool operator>(const mvec& l, const mvec& r) noexcept{
                return l.size > r.size;
            }

            friend bool operator<(const mvec& l, const mvec& r) noexcept{
                return l.size < r.size;
            }

            friend bool operator>=(const mvec& l, const mvec& r) noexcept{
                return !(l < r);
            }

            friend bool operator<=(const mvec& l, const mvec& r) noexcept{
                return !(l > r);
            }

            mvec& operator++(){
                mvec& res = *this;
                ++(this);
                return res; 
            }

            private:
            std::shared_ptr<mvec<T>> miauptr;
        };

        private:
        T* data;

        size_t size;
        size_t capacity;
        size_t max_size;
    };
}
