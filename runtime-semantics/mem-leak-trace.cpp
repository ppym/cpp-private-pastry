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
	cout << "Tracer::~Tracer" << endl;
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
	cout << "Tracer::Add" << endl;
        _map[p] = Entry(file, line);  
	cout << "Tracer::Add-------" << endl;
}  
  
void Tracer::Remove(void *p)  
{  
        if (_lockCount > 0)  
                return;  
  
        Tracer::Lock lock(*this);  
  
        iterator itor = _map.find(p);  
        if (itor != _map.end())  {
		cout << "Tracer::Remove" << endl;
                _map.erase(itor);  
		cout << "Tracer::Remove--" << endl;
	}
}  
  
/*extern*/ Tracer gNewTracer;  
  
void* operator new (size_t size, const char* file, int line)  
{  
	//cout << "operator new (size_t size, const char* file, int line)" << endl;
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, file, line);  
	cout << "operator new (size_t, const char*, int)=" <<size << " p=" << (long*)p << endl;
        return p;  
}  
  
void operator delete(void* p, const char* file, int line)  
{  
	cout << "operator delete(void*, const char*, int)=" << (long*)p << endl;
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
void* operator new (size_t size)  
{  
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, "?", 0);  
	cout << "operator new (size_t )=" << size <<" p=" << (long*)p << endl;
        return p;  
}  
  
void operator delete(void* p)  
{  
	cout << "operator delete(void*)=" << (long*)p<< endl;
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
void* operator new [](size_t size, const char* file, int line)  
{  
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, file, line);  
	cout << "operator new [](size_t, const char*, int)=" << size << " p= " << (long*)p <<  endl;
        return p;  
}  
  
void operator delete[](void* p, const char* file, int line)  
{  
	cout << "operator delete[](void*, const char*, int)=" <<(long*)p << endl;
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
void* operator new[] (size_t size)  
{  
        void* p = malloc(size);  
        if (Tracer::Ready)  
                gNewTracer.Add(p, "?", 0);  
	cout << "operator new[] (size_t)=" << size << " p=" << (long*)p << endl;
        return p;  
}  
  
void operator delete[](void* p)  
{  
        cout << "delete[](void* )=" << (long*)p <<endl;  
        if (Tracer::Ready)  
                gNewTracer.Remove(p);  
        free(p);  
}  
  
#define new new(__FILE__, __LINE__)  
  
class X {
private:
	long mi[1000];
};

int main(int argc, char *argv[])  
{  
	cout << "============== start " << argv[0] << "===============" << endl;
        int * a = new int(3);  
        int * b = new int[3];  
        int * c = new int[3];  
	X *x = new X[100];
	cout << "a=" << (long*)a << " b=" << (long*)b << endl;
	delete b;
	cout << "============== exit" << argv[0] << "===============" << endl;

        return 0;  
}    
