#ifndef __MYLIST__
#define __MYLIST__
#include <assert.h>
 
 
template<class Ty>
struct _Node
{
    _Node()
    {
        memset(&data, 0, sizeof(Ty));
        prev = 0;
        next = 0;
    }
 
    _Node(const Ty& val, _Node *p1, _Node *p2)
    {
        data = val;
        prev = p1;
        next = p2;
    }

    Ty data;
    _Node *prev;
    _Node *next;
};
 
template<class Ty>
class _Itor
{
public:
    _Node < Ty > * node;//_Node < Ty > 看成是一个类  ，Node
 

 
public:
    //default construct
    _Itor()
    {
        node = 0;
    }
 
    _Itor(_Node<Ty> *val)
    {
        node = val;
    }
    //copy construct
    _Itor(const _Itor<Ty>& _Right)
    {
        node = _Right.node;
    }
 
    //=
    _Itor& operator=(const _Itor<Ty> &_Right)
    {
        node = _Right.node;
        return *this;
    }
 
    //
    bool operator ==(const _Itor<Ty> &_Right)
    {
        return node == _Right.node;
    }
 
    //
    bool operator != (const _Itor<Ty> &_Right)
    {
        return node != _Right.node;
    }
 
 
    _Itor& operator++()
    {
        node = node->next;//很明显用到了容器的方法
        return *this;
    }
 
 
    _Itor& operator--()  //e.g. *(--itor) 操作
    {
        node = node->prev;
        return *this;
    }
 
    _Itor & operator+(int n)//后向偏移个数
    {
        //无法对n 作越界判断
        if (n > 0)
        {
            while (n--)
            {
                node = node->next;
            }
        }
        return *this;
    }
    _Itor & operator+=(int n)//后向偏移个数
    {
        //无法对n 作越界判断
        if (n > 0)
        {
            while (n--)
            {
                node = node->next;
            }
        }
        return *this;
    }
 
 
    _Itor & operator-(int n)//前向偏移个数
    {
        if (n > 0)
        {
            while (n--)
            {
                node = node->prev;
            }
        }
        return *this;
    }
    _Itor & operator-=(int n)//前向偏移个数
    {
        if (n > 0)
        {
            while (n--)
            {
                node = node->prev;
            }
        }
        return *this;
    }
 
    Ty & operator *()//看来返回引用类型，存取数据皆可 ,* -> 应该返回实际数据
    {
        return node->data;
    }
 
    Ty  * operator->()
    {
        return &(node->data);
    }
 
 
};
 
template<class Ty>
class MYList
{
 
 
public:
    typedef _Node<Ty> myNode;
    typedef _Itor<Ty> myItor;//MYList<Ty> myItor;  等同于 _Itor<Ty>
private:
    myNode *_myHead;
    size_t _myCount;
private:
    myNode* insert(myNode *pos, myNode *node)
    {
        assert(pos != 0 && node != 0);
 
        myNode *next = pos->next;
        pos->next = node;
        node->prev = pos;
 
        next->prev = node;
        node->next = next;
 
        up_count();
 
        return node;
    }
 
    myNode* alloc(const Ty& val)
    {
        myNode *tmp = new myNode;
        tmp->data = val;
        tmp->prev = tmp->next = 0;
        return tmp;
    }
    myNode *leaveLink(myNode*pos)//返回下一个
    {
        assert(pos != _myHead  &&pos != 0);
 
        myNode   *prev = pos->prev;
        myNode *next = pos->next;
        prev->next = next;
        next->prev = prev;
 
        down_count();
        delete pos;
        return next;
 
 
    }
    void up_count()
    {
        _myCount++;
    }
 
    void down_count()
    {
        assert(_myCount > 0);
        _myCount--;
    }
 
public:
myNode * getHead()
    {

        return _myHead;

    }
	void setHead(myNode * pHead)
	{
		_myHead=pHead;
	}

	void setSize(size_t tSize)
	{
		_myCount=tSize;
	}
    // default construct
    void clear()
    {
        myNode *node = _myHead->next;
        while (node->next != node)
        {
            node = leaveLink(node);
        }
    }
    size_t size()
    {
        return _myCount;
    }
    bool isEmpty()
    {
        return _myCount == 0;
    }
    MYList()
    {
        _myHead = new myNode;
        _myHead->next = _myHead->prev = _myHead;
        _myCount = 0;
    }
 
    ~MYList()
    {
 
        clear();
        if (_myHead != NULL)
            delete _myHead;
    }
 
     
 
 
    MYList(const Ty& val)
    {
        _myHead = new myNode;
        _myHead->next = _myHead->prev = _myHead;
        _myCount = 0;
 
        myNode *tmp = alloc(val);
        insert(_myHead, tmp);
    }
 
 
    MYList(const Ty& val, size_t count)
    {
        _myHead = new myNode;
        _myHead->next = _myHead->prev = _myHead;
        _myCount = 0;
 
        for (size_t i = 0; i < count; ++i)
        {
            myNode *tmp = alloc(val);
            insert(_myHead->prev, tmp); //尾部插入
        }
    }
 
  void swap(MYList< Ty >& val)
		
    {
		
		myNode * pTmpHead=_myHead;
		_myHead=val.getHead();
		val.setHead(pTmpHead);
		
		size_t nTmp=_myCount;
		_myCount=val.size();
		val.setSize(nTmp);
        
		
    }
    //copy construct
    MYList(MYList< Ty >& val)
    {
        _myHead = new myNode;
        _myHead->next = _myHead->prev = _myHead;
        _myCount = 0;
 
        myNode * head = val.getHead();
        myNode *next = head->next;
        myNode *tmp = NULL;
        while (next != head)
        {
            myNode *tmp = alloc(next->data);
            insert(_myHead->prev, tmp); //尾部插入
            next = next->next;
        }
    }
 
    Ty & operator[] (size_t i)
    {
        assert(i< _myCount);
        size_t j = 0;
 
        myNode *next = _myHead->next;
        while (j<i)
        {
            next = next->next;
            j++;
        }
        return next->data;
    }
 
    // front value
   Ty front()

    {

        return _myHead->next->data;

    }

 

    // back value

    Ty back()

    {

        return _myHead->prev->data;

    }
 
    // first itor
    myItor begin()
    {
        return myItor(_myHead->next);
    }
    myItor end()
    {
        return myItor(_myHead);
    }
 
    void push_front(Ty val)
    {
        myNode * tmp = alloc(val);
        insert(_myHead, tmp); //头部插入
    }
 
    void push_back(Ty val)
    {
 
        myNode *tmp = alloc(val);
        insert(_myHead->prev, tmp); //尾部插入
 
    }
    myNode *  pop_front()
    {
        return leaveLink(_myHead->next);
    }
 
    myNode *  pop_back()
    {
        return leaveLink(_myHead->prev);
    }
 
 
    void resize(size_t _N)
    {
        assert(_N<_myCount);
 
        if (_N == 0)
        {
            clear();
            return;
        }
        //默认将先push_back()的元素删除
        if (_N<_myCount && _N>0)
        {
            int nCutCount = _myCount - _N;
            while (nCutCount--)
            {
                pop_front();
            }
        }
 
    }
 
    MYList<Ty> & operator =(MYList<Ty>& val)
    {
 
        /*_myHead = new myNode;
        _myHead->next = _myHead->prev = _myHead;
        _myCount = 0;*/
        clear();
 
        myNode * head = val.getHead();
        myNode *next = head->next;
        myNode *tmp = NULL;
        while (next != head)
        {
            myNode *tmp = alloc(next->data);
            insert(_myHead->prev, tmp); //尾部插入
            next = next->next;
        }
 
        return *this;
    }
 
    MYList<Ty> & operator += (MYList<Ty>& val)
    {
        myNode * head = val.getHead();
        myNode *next = head->next;
         
        while (next != head)
        {
            myNode *tmp = alloc(next->data);
            insert(_myHead->prev, tmp); //尾部插入
            next = next->next;
        }
 
        return *this;
    }
 
};
 
#endif
