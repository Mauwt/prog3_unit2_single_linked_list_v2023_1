//
// Created by rudri on 10/11/2020.
//

#include <initializer_list>
#include <iostream>
#include <memory>
#include <type_traits>

#ifndef PROG3_UNIT2_SINGLE_LINKED_LIST_V2023_1_SINGLE_LINKED_LIST_H
#define PROG3_UNIT2_SINGLE_LINKED_LIST_V2023_1_SINGLE_LINKED_LIST_H
namespace utec{


    template<typename T>
    struct Node {

    public:
        using Shared_N = std::shared_ptr<Node<T>>;

        //Constructors
        Node() = default;
        explicit Node(T val) : value(val) {}
        Node(Node<T>& o) : value(o.value), next(o.next){}
        Node(Node<T>&& o) noexcept: value(std::move(o.value)), next(std::move(o.next)){}

        virtual ~Node()=default;

        //Getters
        T& get_value() { return value; }
        Shared_N get_next() { return next; }

        //Setters
        void set_next(Shared_N new_next) { next = new_next; }
    private:
        T value {}; //Inicializa value con el valor por defecto
        Shared_N next = nullptr;
    };

    template<typename T>
    class sll_iter{
    public:
        using iterator_category     = std::forward_iterator_tag;
        using difference_type       = std::ptrdiff_t;
        using value_type            = T;
        using pointer               = T*;
        using reference             = T&;
        using const_reference       = const T&;

        using Shared_N = std::shared_ptr<Node<T>>;

        sll_iter() = default;
        explicit sll_iter(Shared_N _p): current(_p){};

        T& operator  * ()  {return current->get_value();}
        T* operator -> ()  {return *current;}

        sll_iter& operator++() {
            current = current->get_next();
            return *this;
        }
        sll_iter operator++(int) {
            auto it = *this;
            ++*this;
            return it;
        }

        bool operator==(sll_iter o ){
            return current == o.current;
        }
        bool operator!=(sll_iter o ){
            return current != o.current;
        }
    private:
        Shared_N  current;
    };

    template<typename T>
    class single_linked_list {
    private:
        using Shared_N = std::shared_ptr<Node<T>>;
        Shared_N head = nullptr;
    public:
        //Constructors
        single_linked_list() = default;
        single_linked_list(std::initializer_list<T> lst) {
            head = std::make_shared<Node<T>>( *(std::prev(lst.end())) );

            Shared_N current = head;

            for (int i = lst.size()-2; i >= 0; i--) {
                Shared_N temp = std::make_shared<Node<T>>( *(std::next(lst.begin(),i)) );
                current->set_next(temp);
                current = current->get_next();
            }
        }
        single_linked_list(const single_linked_list<T>& o) {
            if (o.head) {
                head = std::make_shared<Node<T>> (*(o.head));
                Shared_N current = head;
                Shared_N currentOther = o.head->get_next();

                while (currentOther != nullptr) {
                    current->set_next(std::make_shared<Node<T>>(*(currentOther)));
                    current = current->get_next();
                    currentOther = currentOther->get_next();
                }
            }
        }
        single_linked_list(single_linked_list&& o) noexcept : head(std::move(o.head)){}

        virtual ~single_linked_list() = default;

        //Getters
        std::shared_ptr<Node<T>>& get_head()  {return head;}


        //Methods
        void push_front(T val){
            Shared_N new_node = std::make_shared<Node<T>>(val);
            if(!head){
                head = new_node;
            }else {
                new_node->set_next(head);
                head = new_node;
            }
        }
        void pop_front(){
            if(!head) throw std::runtime_error("Out of range");
            head = head->get_next();
        }

        template<typename ...Tparams  >
        void emplace_front(Tparams...params ){

        }

        single_linked_list<T>& operator = (const single_linked_list<T>& o){
            return *this ;
        }

        //iterators
        using iter = sll_iter<T>;
        iter begin(){return iter(head);}
        iter end(){
            auto current = head;
            while(current != nullptr){
                current = current->get_next();
            }
            return iter(current);
        }


        //Ostream operator overloads
        friend std::ostream& operator<<(std::ostream& o, single_linked_list<T>& _sll){
            auto current = std::begin(_sll);
            while(current != std::end(_sll)){
                std::cout << *current << " ";
                ++current;
            }
            std::cout << '\n';
            return o;
        }
    };


}

#endif //PROG3_UNIT2_SINGLE_LINKED_LIST_V2023_1_SINGLE_LINKED_LIST_H
