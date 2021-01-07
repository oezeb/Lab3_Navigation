#include <stdlib.h>

template <typename T>
struct Priority_Queue
{
private:
    T *data;
    size_t rear;
    size_t capacity;
    int (*cmp)(const T &a, const T &b);

public:
    static void init(struct Priority_Queue &q, size_t capacity, int (*cmp)(const T &a, const T &b));
    static void destroy(struct Priority_Queue &q);
    static bool enqueue(struct Priority_Queue &q, const T &e);
    static bool dequeue(struct Priority_Queue &q, T &e);
    static bool top(const struct Priority_Queue &q, T &e);
    static size_t length(const struct Priority_Queue &q);
    static bool empty(const struct Priority_Queue &q);
    static bool full(const struct Priority_Queue &q);
};

template <typename T>
void Priority_Queue<T>::init(struct Priority_Queue<T> &q, size_t capacity, int (*cmp)(const T &a, const T &b))
{
    // TODO#
    q.data = (T*)malloc(capacity * sizeof(T));
    if (!q.data) exit(-2);
    q.rear = 0;
    q.capacity = capacity;
    q.cmp = cmp;
}

template <typename T>
void Priority_Queue<T>::destroy
(struct Priority_Queue<T> &q)
{
    // TODO#
    free(q.data);
}

template <typename T>
bool Priority_Queue<T>::enqueue(struct Priority_Queue<T> &q, const T &e)
{
    // TODO#
    if (full(q))
        return false;
    int i = q.rear - 1;
    for (; i >= 0; i--) {
        if (q.cmp(e, q.data[i]) < 0)
            break;
        q.data[i + 1] = q.data[i];
    }
    q.data[i + 1] = e;
    q.rear++;
    return true;
}

template <typename T>
bool Priority_Queue<T>::dequeue(struct Priority_Queue<T> &q, T &e)
{
    // TODO#
    if (empty(q))
        return false;
    e = q.data[--q.rear];
    return true;
}

template <typename T>
bool Priority_Queue<T>::top(const struct Priority_Queue<T> &q, T &e)
{
    // TODO#
    if (empty(q))
        return false;
    e = q.data[q.rear-1];
    return true;
}

template <typename T>
size_t Priority_Queue<T>::length(const struct Priority_Queue<T> &q)
{
    // TODO#
    return q.rear;
}

template <typename T>
bool Priority_Queue<T>::empty(const struct Priority_Queue<T> &q)
{
    // TODO#
    return q.rear == 0;
}

template <typename T>
bool Priority_Queue<T>::full(const struct Priority_Queue<T> &q)
{
    // TODO#
    return q.rear == q.capacity;
}
