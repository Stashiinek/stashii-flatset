#include <librgr/vector.hpp>

namespace stashii{
    template<typename T, typename Compare = std::less<>>
    class flatset{
        public:
        flatset() noexcept: setdata(){};
        flatset(const T& other) noexcept: setdata(other){};
        
        flatset(const flatset& other) noexcept{
            setdata = other.setdata;    //тут мб оператор = через перемещение украдет данные я хз
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

        bool diff(T r, T l){
            return Compare()(r, l);
        }

        T& lower_bound(T key) noexcept{
            if (setdata.get_size() < 2)
                return (Compare()(setdata[0], setdata[1])) ? setdata[0] : setdata[1];
            
            for (size_t i = 0; i < setdata.get_size(); i++){
                if (!Compare()(key, setdata[i])){
                    return setdata[i];
                }
            }
            return setdata[setdata.get_size()];
        }

        T& upper_bound(T key) noexcept{
            if (setdata.get_size() < 2)
                return (Compare()(setdata[1], setdata[0])) ? setdata[0] : setdata[1];

            for (size_t i = setdata.get_size(); i > 0; i++){
                if (Compare()(key, setdata[i])){
                    return setdata[i];
                }
            }
            return setdata[0];
        }

        T& find(const T &key) noexcept{
            return setdata.find(key);
        }

        bool exist(const T& key) noexcept{
            return setdata.exist(key);
        }

        const size_t index(const T& key) noexcept{
            std::size_t i = 0;
            for (i; i < setdata.get_size(); i++)
                if (setdata[i] == key)
                    return i;
            return setdata.get_size();
        }

        bool empty() noexcept{
            return (size == 1) ? true : false;
        }

        bool full() noexcept{
            return (setdata.get_capacity() == setdata.get_maxsize()) ? true : false;
        }

        mvec<T>& begin(){ return setdata.begin();}
        mvec<T>& end(){return setdata.end();}

        mvec<T>& rbegin(){ return setdata.rbegin(); }
        mvec<T>& rend(){ return setdata.rend(); }

        size_t size() noexcept{ return setdata.get_size(); }
        size_t max_size() noexcept{ return setdata.get_maxsize(); }
        size_t avaiable() noexcept{ return setdata.get_maxsize() - setdata.get_size(); }

        void insert(const T& other){
            if (exist(other) != true){
                setdata.push_back(other);
                
                if (setdata.get_size() > 2){
                    T& lower = lower_bound(other);
                    auto i = index(other) - 1;
                    
                    if (!Compare()(setdata[i - 1], setdata[setdata.get_size() - 1])){
                        std::swap(setdata[i - 1], setdata[setdata.get_size() - 1]);
                    }
                    for (size_t k = i; k < setdata.get_size() - 1; k++){
                        if (!Compare()(setdata[k], setdata[k + 1]))
                            std::swap(setdata[k], setdata[k + 1]);
                    }
                } else {
                    if ((setdata.get_size() > 1)&&(!Compare()(setdata[0], setdata[1])))
                    std::swap(setdata[0], setdata[1]);
                }
            }
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
