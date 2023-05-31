#include <librgr/vector.hpp>

namespace stashii{
    template<typename T, typename Compare = std::less<>>
    class flatset{
        public:
        flatset() noexcept: setdata(){};
        flatset(const T& other) noexcept: setdata(other){};
        
        flatset(const flatset& other) noexcept{
            setdata = other.setdata;    //тут мб оператор = через перемещение украдет данные
        }

        flatset(flatset&& other) noexcept{
            setdata = other.setdata;
            other.clear();
        }

        flatset(mvec<T>&& other){
            for (size_t i = 0; i < size; i++){
                if (!setdata.find(other[i]))
                setdata.push_back(other[i]);
            }
            sort();
            other.setdata.clear();
        }

        const flatset& operator=(const flatset& other) noexcept{
            setdata = other.setdata;
            //return *this;
        }

        flatset& operator=(flatset&& other) noexcept{
            setdata = other.setdata;
            other.clear();
        }

        T& at(size_t pos){
            return setdata.at(pos);
        }

        T& operator[](size_t pos){
            return setdata[pos];
        }

        ~flatset() {}

        //mvec& lower_bound(T& key) noexcept{}
        //mvec& upper_bound(T& key) noexcept{}

        T& find(const T &key) noexcept{
            return setdata.find(key);
        }

        bool exist(const T& key) noexcept{
            return setdata.exist(key);
        }

        bool empty() noexcept{
            return (size == 1) ? true : false;
        }

        //bool full(){}

        mvec<T>& begin(){ return setdata.begin();}
        mvec<T>& end(){return setdata.end();}

        mvec<T>& rbegin(){ return setdata.rbegin(); }
        mvec<T>& rend(){ return setdata.rend(); }

        //тут место для обратных итераторов 

        size_t size() noexcept{ return setdata.get_size(); }
        size_t max_size() noexcept{ return setdata.get_maxsize(); }
        size_t avaiable() noexcept{ return setdata.get_maxsize() - setdata.size(); }

        void insert(const T& other){
            if (exist(other) != true)
                setdata.push_back(other);
            sort(); // лучше находить место для вставки 
        }
        void insert(const mvec<T>& other){}

        void erase(mvec<T>& other){}
        void erase(mvec<T>& first_it, mvec<T>& last_it){}

        void clear(){}

        void contains(T& other){}

        //место для операторов сравнения (их надо еще написать в mvec)

        private:
        mvec<T> setdata;

        void sort() noexcept{        //надо потом заменить на более умный код
            for (size_t i = 0; i < setdata.get_size(); i++)
                for (size_t k = 0; k < setdata.get_size(); k++)
                    if (Compare()(setdata[i], setdata[k])){
                        std::swap(setdata[i], setdata[k]);
                    }
        }
    };
}