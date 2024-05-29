// ======================================================================
// \title  PcaServo.cpp
// \author tcanham
// \brief  cpp file for PcaServo component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <RobotArm/PcaServo/PcaServo.hpp>
#include "FpConfig.hpp"
#include "Os/Task.hpp"

namespace RobotArm {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

PcaServo ::PcaServo(const char* const compName) : PcaServoComponentBase(compName), m_instance(0), m_addr(0), m_servoEnabled(Fw::Enabled::DISABLED) {
    this->m_buff.setData(this->m_data);
    this->m_buff.setSize(I2C_BUFFER_SIZE);
}

PcaServo ::~PcaServo(void) {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void PcaServo ::position_handler(const NATIVE_INT_TYPE portNum, F32 angle) {
    // call common handler
    this->setPos(angle);
}

void PcaServo ::PS_ANG_cmdHandler(const FwOpcodeType opCode, const U32 cmdSeq, F32 angle) {
    // call common handler
    this->setPos(angle);
    // return command status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void PcaServo::setPos(F32 angle) {
    // See https://www.nxp.com/docs/en/data-sheet/PCA9685.pdf and
    // https://learn.sparkfun.com/tutorials/pi-servo-hat-hookup-guide#software---python
    // for scaling

    // set zero point. Pick the register set for this servo
    this->m_data[0] = 0x6 + 4 * this->m_instance;
    this->m_data[1] = 0;
    this->m_buff.setSize(2);
    // call I2C port
    this->i2c_out(0, SERVO_BRD_ADDR, this->m_buff);

    // compute the PWM duty cycle for angle
    U16 reg = MINUS_90 + (PLUS_90 - MINUS_90) * ((90.0 + angle) / 180.0);
    // put values in I2c buffer
    this->m_data[0] = 0x8 + 4 * this->m_instance;
    this->m_data[1] = reg & 0xFF;
    this->m_data[2] = (reg >> 8) & 0xFF;
    this->m_buff.setSize(3);
    // call I2C port
    this->i2c_out(0, SERVO_BRD_ADDR, this->m_buff);

    // send event
    this->log_ACTIVITY_HI_PS_AngleCmd(this->m_instance, angle, reg);
    // send telemetry
    this->tlmWrite_PS_Angle(angle);
    this->tlmWrite_PS_Reg(reg);
}

void PcaServo::configure(U32 instance,  //!< servo instance on board
                         U32 addr       //!< servo board address
) {
    this->m_instance = instance;
    this->m_addr = addr;
}

void PcaServo::configChip(void) {
    // enable chip
    this->m_data[0] = 0;
    this->m_data[1] = 0x20;  //!< enable PWM
    this->m_buff.setSize(2);
    // call I2C port
    this->i2c_out(0, SERVO_BRD_ADDR, this->m_buff);

    // enable prescale setting
    this->m_data[0] = 0;
    this->m_data[1] = 0x10;  //!< put to sleep
    this->m_buff.setSize(2);
    // call I2C port
    this->i2c_out(0, SERVO_BRD_ADDR, this->m_buff);

    // delay for reset
    Os::Task::delay(500);

    // set prescale value
    this->m_data[0] = 0xfe;
    this->m_data[1] = 0x79;  //!< enable PWM
    this->m_buff.setSize(2);
    // call I2C port
    this->i2c_out(0, SERVO_BRD_ADDR, this->m_buff);

    // re-enable chip
    this->m_data[0] = 0;
    this->m_data[1] = 0x20;  //!< enable PWM
    this->m_buff.setSize(2);
    // call I2C port
    this->i2c_out(0, SERVO_BRD_ADDR, this->m_buff);

    // enable multi-byte
    this->m_data[0] = 0xfe;
    this->m_data[1] = 0x1e;  //!< enable multi-byte
    this->m_buff.setSize(2);
    // call I2C port
    this->i2c_out(0, SERVO_BRD_ADDR, this->m_buff);
}

void PcaServo ::PS_DIS_cmdHandler(const FwOpcodeType opCode, const U32 cmdSeq) {
    // enable prescale setting
    this->m_data[0] = 0;
    this->m_data[1] = 0x10;  //!< put to sleep
    this->m_buff.setSize(2);
    // call I2C port
    this->i2c_out(0, SERVO_BRD_ADDR, this->m_buff);
    this->m_servoEnabled = Fw::Enabled::DISABLED;
    this->tlmWrite_PS_Enabled(this->m_servoEnabled);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void PcaServo ::PS_EN_cmdHandler(const FwOpcodeType opCode, const U32 cmdSeq) {
    this->configChip();
    this->m_servoEnabled = Fw::Enabled::ENABLED;
    this->tlmWrite_PS_Enabled(this->m_servoEnabled);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // end namespace RobotArm
