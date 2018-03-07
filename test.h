#ifndef _TEST_H__
#define _TEST_H__

#include <stdlib.h>
#include <stdint.h>
#include <string>
using namespace std;

class TestDemo
{
  public:
    TestDemo();
    ~TestDemo();
    void operationFinished(uint8_t id, uint8_t type);
    void cmdOperation(uint8_t directive, double value);
    void motorAttrChanged(uint8_t id,uint8_t attrId, double value);
    void errorOccur(uint8_t id,uint16_t errorId, string errorInfo);
  private:
    bool m_bHasLaunched;
};

#endif