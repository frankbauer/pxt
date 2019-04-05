#ifndef __BLOCKLY_HELPER__
#define __BLOCKLY_HELPER__
#include <vector>
using namespace std;

template<class _Prop_t,
         class _ObjClass_t>
class Property
{
    typedef _Prop_t (_ObjClass_t::* _pmGet_t)() const;

    _ObjClass_t& m_objInstance;
    _pmGet_t     m_pmGet;

public:
    Property(_ObjClass_t& objInstance, _pmGet_t pmGet)
    :  m_objInstance(objInstance), m_pmGet(pmGet)
    {}
    operator _Prop_t() { return (m_objInstance.*m_pmGet)(); }
};

class BlocklyArray {
    public:
        BlocklyArray() : data(0), length(*this, &BlocklyArray::getLength) {}
        BlocklyArray(std::initializer_list<double> a_args) : BlocklyArray() {
            data.insert(std::end(data), a_args);
        }

        double& operator[] (const int index) {
            if (index < 0) return zero;
            if (index >= data.size()) {
                data.resize(index+1);
            }
            return data[index];
        }

        double& operator[] (const double indexD) {
            const int index = (int)indexD;
            if (index < 0) return zero;
            if (index >= data.size()) {
                data.resize(index+1);
            }
            return data[index];
        }

        const double& operator[] (const int index) const{
            if (index < 0 || index >= data.size()) return zero;            
            return data[index];
        }

        const double& operator[] (const double indexD) const {
            const int index = (int)indexD;
            if (index < 0 || index >= data.size()) return zero;            
            return data[index];
        }

        void push(double val){
            data = {1, 2, 3};
            data.push_back(val);
        }

        double pop(){
            const double ret = data.back();
            data.pop_back();
            return ret;
        }

        void revert(){
            std::reverse(data.begin(),data.end());
        }

        BlocklyArray& operator+=(std::initializer_list<double> l)
        {
            data.insert(std::end(data), l);
            return *this;
        }

        BlocklyArray& operator=(std::initializer_list<double> l)
        {
            data.clear();
            data.insert(std::end(data), l);
            return *this;
        }
        
        Property<double, BlocklyArray> length;
    private:
        static double zero;
        std::vector<double> data;

        double getLength() const { return data.size(); }
};
double BlocklyArray::zero = 0.0;

#endif