#include <librgr/vector.hpp>

namespace stashii{
    template<typename T, typename Compare = std::less<>>
    class flatset{
        flatset() noexcept: setdata();
        flatset(const T& other) noexcept: setdata(other);
        
        flatset(const flatset& other) noexcept{
            setdata = other.setdata;    //тут мб оператор = через перемещение украдет данные
        }

        flatset(const mvec& other){
            for (size_t i = 0; i < size; i++){
                if (!setdata.find(other[i]))
                setdata.push_back(other[i]);
            }
            sort();
        }

        flatset(flatset&& other) noexcept{
            setdata = other.setdata;
            other.clear();
        }

        flatset(mvec&& other){
            for (size_t i = 0; i < size; i++){
                if (!setdata.find(other[i]))
                setdata.push_back(other[i]);
            }
            sort();
            other.setdata.clear();
        }

        flatset& operator=(const flatset& other) noexcept{
            setdata = other.setdata;
            return *this;
        }

        flatset& operator=(flatset&& other) noexcept{
            setdata = other.setdata;
            other.clear();
        }

        flatset& at(size_t pos){
            return setdata.at(pos);
        }

        flatset& operator[](size_t pos){
            return setdata[pos];
        }

        flatset& operator=(const mvec& other) noexcept{
            for (size_t i = 0; i < size; i++){
                if (!setdata.find(other[i]))
                setdata.push_back(other[i]);
            }
            sort();
        }

        flatset& operator=(mvec&& other) noexcept{
            for (size_t i = 0; i < size; i++){
                if (!setdata.find(other[i]))
                setdata.push_back(other[i]);
            }
            other.setdata.clear();
            sort();
        }

        ~flatset() { setdata->~mvec(); }

        mvec& lower_bound(T& key) noexcept{
        }

        mvec& upper_bound(T& key) noexcept{}

        T& find(T &key) noexcept{
            return setdata.find(key);
        }

        bool exist(T& key) noexcept{
            return setdata.exist(key);
        }

        bool empty() noexcept{
            return (size == 1) ? true : false;
        }

        bool full(){}

        mvec& begin(){ return setdata.begin();}
        mvec& end(){return setdata.end();}

        mvec& rbegin(){ return setdata.rbegin(); }
        mvec& rend(){ return setdata.rend(); }

        //тут место для обратных итераторов 

        size_t size() noexcept{ return setdata.size; }
        size_t max_size() noexcept{ return setdata.max_size; }
        size_t avaiable() noexcept{ return setdata.max_size - setdata.size; } //сколько еще можем записать

        void insert(const T& other){
            if (!find(other))
                setdata.push_back(other);
            sort(); // лучше находить место для вставки 
        }
        void insert(const mvec& other){}

        void erase(mvec& other){}
        void erase(mvec& first_it, mvec& last_it){}

        void clear(){}

        void contains(T& other){}

        //место для операторов сравнения (их надо еще написать в mvec)

        private:
        mvec<T> setdata;

        void sort(){        //надо потом заменить на более умный код
            for (size_t i = 0; i < setdata.size; i++)
                for (size_t k = 0; k < setdata.size; k++)
                    if (Compare(setdata[i], setdata[k])){
                        std::swap(setdata[i], setdata[k]);
                    }
        }
    };
}