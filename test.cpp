
#include "test.h"
#include "motorscontroller.h"
#include <stdio.h>
#include <iostream>

TestDemo::TestDemo() : m_bHasLaunched(false)
{
}

TestDemo::~TestDemo()
{
}

void TestDemo::operationFinished(uint8_t id, uint8_t type)
{
    switch (type)
    {
    case MotorsController::Recognize_Finished:
    {
        vector<uint8_t> idArray = controllerInst->getMotorIdArray();
        for(int i=0;i<idArray.size();++i)
        {
            if(controllerInst->getMotorAttribute(idArray.at(i),MotorData::MOTOR_SWITCH)
                    != UserDefine::MOTOR_SWITCH_ON)
            {
                controllerInst->launchMotor(idArray.at(i));
				//controllerInst->switchAutoRefresh(idArray.at(i),true);
				//controllerInst->setAutoRefreshInterval(idArray.at(i),1000);
            }
            else
            {
                m_bHasLaunched = true;
            }
        }
    }

        break;
    case MotorsController::Launch_Finished:
    {
        m_bHasLaunched = true;
        // vector<uint8_t> idArray;
        // idArray.push_back(id);
        // controllerInst->activeMotorsMode(idArray, MotorData::Mode_Profile_Pos);
    }
    break;
    default:
        break;
    }
}

void TestDemo::cmdOperation(uint8_t directive, double value)
{
    if (!m_bHasLaunched)
        return;
    vector<uint8_t> idArray = controllerInst->getMotorIdArray();
    switch (directive)
    {
    case 'a':
        controllerInst->activeMotorsMode(idArray, MotorData::Motor_Mode(value));
        break;
    case 's':
        controllerInst->closeAllMotors();
        break;
    case 'p':
        for (int i = 0; i < idArray.size(); ++i)
        {
            controllerInst->setPosition(idArray.at(i), value);
        }
        break;
    case 'c':
        for (int i = 0; i < idArray.size(); ++i)
        {
            controllerInst->setCurrent(idArray.at(i), value);
        }
        break;
    case 'v':
        for (int i = 0; i < idArray.size(); ++i)
        {
            controllerInst->setVelocity(idArray.at(i), value);
        }
        break;
    case 'r':
        {
            int nTag = (int)value;
            MotorData::Motor_Data_Id dataId = MotorData::CUR_ACTURAL;
            if (nTag == 2)
            {
                dataId = MotorData::VEL_ACTURAL;
            }
            else if (nTag == 3)
            {
                dataId = MotorData::POS_ACTURAL;
            }

            for (int i = 0; i < idArray.size(); ++i)
            {
                controllerInst->regainAttrbute(idArray.at(i), dataId);
            }
        }
        break;
    default:
        break;
    }
}

void TestDemo::motorAttrChanged(uint8_t id, uint8_t attrId, double value)
{
    switch (attrId)
    {
    case MotorData::CUR_ACTURAL:
        cout << "motor " << (int)id << " current:" << value << endl;
        break;
    case MotorData::VEL_ACTURAL:
        cout << "motor " << (int)id << " velocity:" << value <<endl;
        break;
    case MotorData::POS_ACTURAL:
        cout << "motor " << (int)id << " position:" << value <<endl;
        break;
    default:
        break;
    }
}

void TestDemo::errorOccur(uint8_t id,uint16_t errorId, string errorInfo)
{
    cout << id << " error " << errorId << " " << errorInfo.c_str() << endl;
}
