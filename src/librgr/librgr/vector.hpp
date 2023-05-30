#include <iostream>
#include <sys/mman.h>

namespace kwangya{
    template<typename T>
    class miauVector{
        public:
        miauVector() noexcept: data(new T[1]), size(0), capacity(1){}
        miauVector(const T &def) noexcept: data(new T[1]), size(0), capacity(1){
            data[0] = def;
        }
        miauVector(const size_t &s){
            if (s < 0)
                throw std::invalid_argument("Size of miauVector must be equal or more than 0");
            else {
                data = new T[s];
                size = s;
                capacity = s + 1;
            }
        }
        miauVector(const miauVector& other){
            data = other.data;
            size = other.size;
            capacity = other.capacity;
        }
        miauVector(miauVector&& other){
            data = other.data;
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 1;
        }
        miauVector(const std::allocator<T> &al){
            std::copy(al.address, al.address + al.max_size, data);
            size = al.max_size;
            capacity = size + 1;
        }

        ~miauVector() = default;

        miauVector& operator=(const miauVector& other) noexcept{
            data = other.data;
            size = other.size;
            capacity = other.capacity;
        }

        miauVector& operator=(miauVector&& other) noexcept{
            data = other.data;
            size = other.size;
            capacity = other.capacity;

            other.data = nullptr;
            other.size = 0;
            other.capacity = 1;
        }

        miauVector& operator=(const std::initializer_list<T> &l){
            std::copy(l.begin(), l.end(), data);
            size = l.size();
            capacity = l.size() + 5;
        }

        miauVector& operator=(const std::allocator<T> &al){
            std::copy(al.address, al.address + al.max_size, data);
            size = al.max_size;
            capacity = size + 1;
        }

        void push_back(const T& value){
            if (size + 1 == capacity){
                capacity += 5;
                T* timely = new T[capacity];    //valgrind жалуется на это
                std::copy(data, data + size, timely);
                data = timely;
                delete[] timely;        //и на это
            }
            data[size] = value;         //а еще на это
            size++;
        }

        void emplace_back(const std::initializer_list<T> &l){
            if (size + l.size() == capacity){
                capacity += l.size;
                T* timely = new T[capacity];
                std::copy(data, data + size + l.size(), timely);
                data = timely;
                delete[] timely;
            }
            size += l.size();
            for (auto &i: l){
                push_back(i);
            }
        }

        void del_num(size_t index){
            if (index > size)
                throw (std::out_of_range("DEL_NUM: Position cannot been more than size"));
            std::swap(data[size], data[index]);
            pop_back();
        }

        void clear(){
            T* timely = new T[1];
            delete[]data;
            data = timely;
            size = 0;
            capacity = 1;
        }

        miauVector& at(size_t pos){
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
            //delete &data[size]; //надо по православноу очистить этот участок памяти чтобы утечки не было
            free(&data[size]);
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
