#ifndef __BLOCKLY_ARRAY__
#define __BLOCKLY_ARRAY__

#include <vector>
#include "Property.h"

using namespace std;


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