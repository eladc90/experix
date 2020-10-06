
#ifndef __NODE_T_H__
#define __NODE_T_H__







template<class T>
class Node_t
{
    public:
            
        Node_t(){}//TODO
        ~Node_t(){}
        Node_t& operator=(const Node_t& _node);
        void SetData(const T& _data) {m_data = _data;}
        void SetNext(const Node_t& _node){m_next = _node;}
        void SetPrev(const T _node){ m_prev = _node;}
        const T& GetData(){return m_data;}
        const Node_t& GetNext(){return m_next;}
        const Node_t& GetPrev(){return m_prev;}


    private:

        T m_data;
        Node_t *m_next;
        Node_t *m_prev;
};


template<class T>
Node_t<T>& Node_t<T>::operator=(const Node_t& _node)
{
    m_next = _node.m_next;
    m_prev = _node.m_prev;
    m_data = _node.m_data;
}

#endif //__DLIST_T_H__
