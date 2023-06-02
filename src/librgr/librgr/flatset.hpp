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

        T lower_bound(T key) noexcept{
            if (setdata.get_size() < 1)
                return setdata[0];
            if (setdata.get_size() < 2)
                return (Compare()(setdata[0], setdata[1])) ? setdata[0] : setdata[1];
            
            for (size_t i = 0; i < setdata.get_size() - 1; i++){
                if (Compare()(key, setdata[i])){
                    if ((setdata[setdata.get_size() - 1] > setdata[0])&&(i > 0))
                        return setdata[i - 1];
                    return setdata[i];
                }
            }
            return setdata[setdata.get_size()];
        }

        T upper_bound(T key) noexcept{
            if (setdata.get_size() < 1)
                return setdata[0];
            if (setdata.get_size() < 2)
                return (Compare()(setdata[1], setdata[0])) ? setdata[0] : setdata[1];

            for (size_t i = setdata.get_size() - 1; i > 0; i--){
                if (Compare()(setdata[i], key)){
                    if ((setdata[setdata.get_size() - 1] > setdata[0])&&(setdata.get_size() - 1 > i))
                        return setdata[i + 1];
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
                    size_t ind = binarysearch(other);
                    if ((ind < setdata.get_size())){
                        if (Compare()(setdata[setdata.get_size() - 1], setdata[ind])){
                            std::swap(setdata[ind], setdata[setdata.get_size() - 1]);
                            for (size_t i = ind + 1; i < setdata.get_size() - 1; i++){
                                std::swap(setdata[i], setdata[setdata.get_size() - 1]);
                            }
                        }   
                    }
                } else if (setdata.get_size() == 2) {
                    if (Compare()(setdata[1], setdata[0]))
                        std::swap(setdata[1], setdata[0]);
                }
            }
        }
        void insert(const mvec<T>& other){}

        void erase(mvec<T>& other){}
        void erase(mvec<T>& first_it, mvec<T>& last_it){}

        void clear(){}

        //место для операторов сравнения (их надо еще написать в mvec)

        private:
        mvec<T> setdata;

        void sort() noexcept{        //надо потом заменить на более умный код
            
        }

        size_t binarysearch(T key){
            if (setdata.get_size() == 2){
                if (Compare()(setdata[0], setdata[1])) return 0;
                else return 1;
            } else if (setdata.get_size() < 2){
                return 0;
            }

            if (Compare()(key, setdata[0])) return 0;

            size_t l = 0, r  = setdata.get_size() - 2;
            size_t m = 0;

            while (r - l > 1){
                m = l + (r - l) / 2;
                if (!Compare()(setdata[m], key))
                    r = m;
                else l = m;
            }
            return (Compare()(key - setdata[r], key - setdata[m])) ? r : m;
        }
    };
}

