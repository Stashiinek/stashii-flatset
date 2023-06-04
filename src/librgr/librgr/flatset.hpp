#include <librgr/vector.hpp>

namespace stashii{
    template<typename T, typename Compare = std::less<>>
    class flatset{
        public:
        flatset() noexcept: setdata(){};
        flatset(const T& other) noexcept: setdata(other){};
        
        flatset(const flatset& other) noexcept{
            setdata = other.setdata;
        }

        flatset(flatset&& other) noexcept{
            setdata = other.setdata;
            other.clear();
        }

        flatset(mvec<T> &other)noexcept{
            for (size_t i = 0; i < other.get_size(); i++){
                setdata.push_back(other[i]);
            }
            sort();
        }

        const flatset& operator=(const flatset& other) noexcept{
            setdata = other.setdata;
            sort();
        }

        flatset& operator=(flatset&& other) noexcept{
            setdata = other.setdata;
            sort();
            other.clear();
        }

        flatset& operator=(mvec<T> &other) noexcept{
            for (size_t i = 0; i < other.get_size(); i++){
                if (!exist(other[i]))
                    setdata.push_back(other[i]);
            }
            sort();
        }

        T& at(size_t pos){
            return setdata.at(pos);
        }

        T& operator[](size_t pos){
            return setdata[pos];
        }

        ~flatset() {}

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
            return (Compare()(key, setdata[setdata.get_size() - 1])) ? setdata[setdata.get_size() - 2] : setdata[setdata.get_size() - 1];
        }

        T upper_bound(T key) noexcept{
            if (setdata.get_size() < 1)
                return setdata[0];
            if (setdata.get_size() < 2)
                return (Compare()(setdata[1], setdata[0])) ? setdata[0] : setdata[1];

            for (size_t i = setdata.get_size() - 1; i > 0; i--){
                if (Compare()(setdata[i], key)){
                    if ((setdata[setdata.get_size() - 1] > setdata[0])&&(setdata.get_size() > i - 1))
                        return setdata[i + 1];
                    return setdata[i];
                }
            }
            return (Compare()(setdata[0], key)) ? setdata[1] : setdata[0];
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

        size_t size() noexcept{ return setdata.get_size(); }
        size_t capacity() noexcept{ return setdata.get_capacity(); }

        void insert(const T& other){
            if (exist(other) != true){
                setdata.push_back(other);
                if (setdata.get_size() > 2){
                    size_t ind = binarysearch(other);
                    if ((ind < setdata.get_size())&&(Compare()(setdata[setdata.get_size() - 1], setdata[ind]))){
                        for (size_t i = ind; i < setdata.get_size() - 1; i++){
                            std::swap(setdata[i], setdata[setdata.get_size() - 1]);
                        }  
                    }
                } else if (setdata.get_size() == 2) {
                    if (Compare()(setdata[1], setdata[0]))
                        std::swap(setdata[1], setdata[0]);
                }
            }
        }
        void insert(const mvec<T>& other){
            for (size_t k = 0; k < other.get_size(); k++){
                if (exist(other[k]) != true){
                    setdata.push_back(other[k]);
                    if (setdata.get_size() > 2){
                        size_t ind = binarysearch(other[k]);
                        if ((ind < setdata.get_size())&&(Compare()(setdata[setdata.get_size() - 1], setdata[ind]))){
                            for (size_t i = ind; i < setdata.get_size() - 1; i++){
                                std::swap(setdata[i], setdata[setdata.get_size() - 1]);
                            }  
                        }
                    } else if (setdata.get_size() == 2) {
                        if (Compare()(setdata[1], setdata[0]))
                            std::swap(setdata[1], setdata[0]);
                    }
                }
            }
        }

        void clear(){
            setdata.clear();
        }

        void remove(const T& el){
            size_t ind = index(el);
            if (ind == setdata.get_size()){
                std::cout << "Note: deleted element does not exist\n";
                return;
            }
            setdata.del_num(ind);
            for (size_t i = ind; i < setdata.get_size() - 1; i++){
                std::swap(setdata[i], setdata[i + 1]);
            }
        }

        void sort() noexcept{
            for (size_t i = 0; i < setdata.get_size(); i++){
                for (size_t k = 0; k < setdata.get_size(); k++){
                    if (Compare()(setdata[i], setdata[k]))
                    std::swap(setdata[i], setdata[k]);
                }
            }
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

        friend bool operator==(flatset &l, flatset& r) noexcept{
            if (l.size() != r.size())
                return false;
            for (size_t i = 0; i < l.size(); i++){
                if (l[i] != r[i])
                    return false;
            }
            return true;
        }

        friend bool operator!=(flatset &l, flatset &r) noexcept{
            return !(l == r);
        }

        class flatIterator{
            public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::forward_iterator_tag;

            //flatIterator(flatIterator &other): mvec<T>::mvecIterator(other.miauptr.get()){}
            //flatIterator(flatIterator &&other): mvec<T>::mvecIterator(other.miauptr.get()){}

            //flatIterator(T* other) : mvec<T>::mvecIterator(other){}

            explicit flatIterator(T *other) : miauptr(other){}
            explicit flatIterator(flatIterator &&other) : miauptr(other.miauptr){}
            explicit flatIterator(flatIterator &other) : miauptr(other.miauptr){}

            ~flatIterator(){}

            T& operator*() noexcept{
                return *miauptr;
            }

            T* operator->() noexcept{
                return miauptr;
            }

            T* operator&() noexcept{
                return miauptr;
            }

            flatIterator& operator++(int){
                (miauptr)++;
                return *this;
            }

            flatIterator& operator++(){
                T* tmp = miauptr;
                ++(*this);
                return *this; 
            }

            flatIterator& operator--(int){
                (miauptr)--;
                return *this;
            }

            flatIterator& operator--(){
                T* tmp = miauptr;
                --(*this);
                return *this; 
            }

            friend bool operator==(const flatIterator& l, const flatIterator& r) noexcept{ return l.miauptr == r.miauptr; }
            friend bool operator==(const flatIterator& l, flatIterator&& r) noexcept{ return l.miauptr == r.miauptr; }
            friend bool operator==(flatIterator&& l, const flatIterator& r) noexcept{ return l.miauptr == r.miauptr; }
            friend bool operator==(flatIterator&& l, flatIterator&& r) noexcept{ return l.miauptr == r.miauptr; }

            friend bool operator!=(const flatIterator& l, const  flatIterator& r) noexcept{ return !(l == r); }
            friend bool operator!=(const flatIterator& l, flatIterator&& r) noexcept{ return !(l == r); }
            friend bool operator!=(flatIterator&& l, const flatIterator& r) noexcept{ return !(l == r); }
            friend bool operator!=(flatIterator&& l, flatIterator&& r) noexcept{ return !(l == r); }

            friend bool operator>(const flatIterator& l, const flatIterator& r) noexcept{ return l.miauptr > r.miauptr; }
            friend bool operator>(const flatIterator& l, flatIterator&& r) noexcept{ return l.miauptr > r.miauptr; }
            friend bool operator>(flatIterator&& l, const flatIterator& r) noexcept{ return l.miauptr > r.miauptr; }
            friend bool operator>(flatIterator&& l, flatIterator&& r) noexcept{ return l.miauptr > r.miauptr; }

            friend bool operator<(const flatIterator& l, const flatIterator& r) noexcept{ return l.miauptr < r.miauptr; }
            friend bool operator<(const flatIterator& l, flatIterator&& r) noexcept{ return l.miauptr < r.miauptr; }
            friend bool operator<(flatIterator&& l, const flatIterator& r) noexcept{ return l.miauptr < r.miauptr; }
            friend bool operator<(flatIterator&& l, flatIterator&& r) noexcept{ return l.miauptr < r.miauptr; }

            friend bool operator>=(const flatIterator& l, const flatIterator& r) noexcept{ return !(l < r); }
            friend bool operator>=(const flatIterator& l, flatIterator&& r) noexcept{ return !(l < r); }
            friend bool operator>=(flatIterator&& l, const flatIterator& r) noexcept{ return !(l < r); }
            friend bool operator>=(flatIterator&& l, flatIterator&& r) noexcept{ return !(l < r); }

            friend bool operator<=(const flatIterator& l, const flatIterator& r) noexcept{ return !(l > r); }
            friend bool operator<=(const flatIterator& l, flatIterator&& r) noexcept{ return !(l > r); }
            friend bool operator<=(flatIterator&& l, const flatIterator& r) noexcept{ return !(l > r); }
            friend bool operator<=(flatIterator&& l, flatIterator&& r) noexcept{ return !(l > r); }

            private:
            T* miauptr;
        };

        flatIterator begin(){ return flatIterator(setdata.begin()); }
        flatIterator end(){return flatIterator(setdata.end()); }
        flatIterator last(){return flatIterator(setdata.last());}
        flatIterator find(const T &key) noexcept{ return flatIterator(setdata.find(key)); }
        flatIterator find(T &&key) noexcept{ return flatIterator(setdata.find(key)); }

        protected:
        mvec<T> setdata;
    };
}