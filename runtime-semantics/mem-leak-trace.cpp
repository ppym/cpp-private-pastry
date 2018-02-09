#include <stdlib.h>  
#include <iostream>  
#include <map>  
#include <string>  
#include <string.h>  
#include <vector>  
using namespace std;  
  
class Tracer  
{  
private:  
    class Entry  
    {  
    public:  
        Entry (char const * file, int line)  
            : _file (file), _line (line)  
        {}  
        Entry ()  
            : _file (0), _line (0)  
        {}  
        char const * File () const { return _file; }  
        int Line () const { return _line; }  
    private:  
        char const * _file;  
        int _line;  
    };  
  
    class Lock  
    {  
    public:  
        Lock (Tracer & tracer)  
            : _tracer (tracer)  
        {  
            _tracer.lock ();  
        }  
        ~Lock ()  
        {  
            _tracer.unlock ();  
        }  
    private:  
        Tracer & _tracer;  
    };  
  
public:  
    Tracer ();  
    ~Tracer ();  
    void Add (void * p, char const * file, int line);  
    void Remove (void * p);  
    void Dump ();  
  
    static bool Ready;  
  
private:  
    void lock () { _lockCount++; }  
    void unlock () { _lockCount--; }  
  
private:  
    typedef std::map<void *, Entry>::iterator iterator;  
    std::map<void *, Entry> _map;  
    int _lockCount;  
};  
  
bool Tracer::Ready = false;  
  
Tracer::Tracer():_lockCount(0)  
{  
        Ready = true;  
}  
  
Tracer::~Tracer()  
{  
        Ready = false;  
        Dump();  
}  
  
void Tracer::Dump()  
{  
        if (_map.size() != 0)  
        {  
                cout << _map.size() << " memory leaks detected" << endl;  
                for (iterator itor = _map.begin(); itor != _map.end(); ++itor)  
                {  
                        char const* file = itor->second.File();  
                        int line = itor->second.Line();  
                        cout << file << ", " << line << endl;  
                }  
        }  
}  
  
void Tracer::Add(void *p, const char *file, int line)  
{  
        if (_lockCount > 0)  
                return;  
        Tracer::Lock lock(*this);  
        _map[p] = Entry(file, line);  
}  
  
void Tracer::Remove(void *p)  
{  
        if (_lockCount > 0)  
                return;  
  
        Tracer::Lock lock(*this);  
  
        iterator itor = _map.find(p);  
        if (itor != _map.end())  
                _map.erase(itor);  
}  
  
/*extern*/ Tracer gNewTracer;  
  
void* operator new (size_t size, const char* file, int line)  
{  
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, file, line);  
        return p;  
}  
  
void operator delete(void* p, const char* file, int line)  
{  
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
void* operator new (size_t size)  
{  
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, "?", 0);  
        return p;  
}  
  
void operator delete(void* p)  
{  
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
void* operator new [](size_t size, const char* file, int line)  
{  
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, file, line);  
        return p;  
}  
  
void operator delete[](void* p, const char* file, int line)  
{  
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        cout <<"delete[](void* p, const char* file, int line)" <<endl;  
        free(p);  
}  
  
void* operator new[] (size_t size)  
{  
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, "?", 0);  
        return p;  
}  
  
void operator delete[](void* p)  
{  
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        cout << "delete[](void* p)"<<endl;  
        free(p);  
}  
  
#define new new(__FILE__, __LINE__)  

class X {
private:
	long mi[1000];
};
 
int main()  
{  
        int * a = new int(3);  
        int * b = new int[3];  
	X *x = new X();
        return 0;  
}  
