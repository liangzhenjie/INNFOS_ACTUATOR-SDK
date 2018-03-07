#include <stdlib.h>
#include <stdio.h>
#include "motorscontroller.h"
#include "test.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <string>
using namespace std;
atomic_uchar directive{0xff};
atomic_int value{0};

void keyboardInput()
{
    char d;
    char v[16];
    while (true)
    {
        cin >> d;       
        cin >> v;
        value = atof(v)*1000;
        directive = d;
        cout << directive << " value:" << value << endl;
    }
}

int main(int argc, char *argv[])
{
    thread t1(keyboardInput);
    MotorsController::initController(argc, argv);
    MotorsController *pController = MotorsController::getInstance();
    pController->autoRecoginze();
    TestDemo t;
    pController->m_sOperationFinished.connect_member(&t, &TestDemo::operationFinished);
    pController->m_sMotorAttrChanged.connect_member(&t,&TestDemo::motorAttrChanged);
    pController->m_sError.connect_member(&t,&TestDemo::errorOccur);
    while (true)
    {
        MotorsController::progressEvents();
        if(directive != 0xff)
        {
            t.cmdOperation(directive,value/1000.0);
            directive = 0xff;
            value = 0;
        }
    }

    return 0;
}