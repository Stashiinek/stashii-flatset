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
                if (!exist(other[i]))
                    setdata.push_back(other[i]);
            }
            sort();
        }

        flatset(std::initializer_list<T> list) noexcept {
            for (auto m : list){
                if (!exist(m))
                insert(m);
            }
        }

        const flatset& operator=(const flatset& other) noexcept{
            clear();
            setdata = other.setdata;
            sort();
            return *this;
        }

        flatset& operator=(flatset&& other) noexcept{
            clear();
            setdata = other.setdata;
            sort();
            other.clear();
            return *this;
        }

        flatset& operator=(mvec<T> &other) noexcept{
            clear();
            for (size_t i = 0; i < other.get_size(); i++){
                if (!exist(other[i]))
                    setdata.push_back(other[i]);
            }
            sort();
            return *this;
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
            return (setdata.get_size() == 0) ? true : false;
        }

        const size_t size() noexcept{ return setdata.get_size(); }
        const size_t capacity() noexcept{ return setdata.get_capacity(); }

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
                if (!exist(other[k]))
                    setdata.push_back(other[k]);
            }
            if (setdata.get_size() == 2) {
                if (Compare()(setdata[1], setdata[0]))
                    std::swap(setdata[1], setdata[0]);
            } else if (setdata.get_size() > 2)
                sort();
        }

        void clear(){
            setdata.clear();
        }

        void remove(const T& el){
            size_t ind = index(el);
            if (ind == setdata.get_size()){
                std::cout << "Note: deleted element '" << el <<"' does not exist\n";
                return;
            }
            setdata.del_num(ind);
            for (size_t i = ind; i < setdata.get_size() - 1; i++){
                std::swap(setdata[i], setdata[i + 1]);
            }
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
            using iterator_category = std::bidirectional_iterator_tag;

            explicit flatIterator(T *other) : miauptr(other){}
            explicit flatIterator(flatIterator &&other) : miauptr(other.miauptr){}
            explicit flatIterator(flatIterator &other) : miauptr(other.miauptr){}

            flatIterator operator=(flatIterator &other){
                miauptr = other.miauptr;
                return *this;
            }

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

            flatIterator& operator++(){
                ++(miauptr);
                return *this;
            }

            flatIterator& operator++(int){
                auto tmp = this;
                ++(miauptr);
                return *tmp; 
            }

            flatIterator& operator--(){
                --(miauptr);
                return *this;
            }

            flatIterator& operator--(int){
                auto tmp = this;
                --(miauptr);
                return *tmp; 
            }

            friend bool operator==(const flatIterator& l, const flatIterator& r) noexcept{ return l.miauptr == r.miauptr; }
            friend bool operator!=(const flatIterator& l, const  flatIterator& r) noexcept{ return !(l == r); }

            friend bool operator>(const flatIterator& l, const flatIterator& r) noexcept{ return l.miauptr > r.miauptr; }
            friend bool operator<(const flatIterator& l, const flatIterator& r) noexcept{ return l.miauptr < r.miauptr; }

            friend bool operator>=(const flatIterator& l, const flatIterator& r) noexcept{ return !(l < r); }
            friend bool operator<=(const flatIterator& l, const flatIterator& r) noexcept{ return !(l > r); }

            private:
            T* miauptr;
        };

        flatIterator begin(){ return flatIterator(setdata.begin()); }
        flatIterator end(){return flatIterator(setdata.end()); }
        flatIterator last(){return flatIterator(setdata.last());}
        flatIterator find(const T &key) noexcept{ return flatIterator(setdata.find(key)); }
        flatIterator find(T &&key) noexcept{ return flatIterator(setdata.find(key)); }
        flatIterator at(const T &key) noexcept{ return flatIterator(setdata[key]); }

        protected:
        mvec<T> setdata;

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
            return (setdata[r] >= setdata[m]) ? r : m;
        }
    };
}