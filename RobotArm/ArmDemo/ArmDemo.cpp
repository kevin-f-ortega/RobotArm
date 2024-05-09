// ======================================================================
// \title  ArmDemo.cpp
// \author tcanham
// \brief  cpp file for ArmDemo component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <RobotArm/ArmDemo/ArmDemo.hpp>
#include <RobotArm/ArmDemo/ArmDemoCfg.hpp>
#include "FpConfig.hpp"

namespace RobotArm {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

ArmDemo ::ArmDemo(const char* const compName) : ArmDemoComponentBase(compName), m_cycles(0) {}

void ArmDemo ::init(const NATIVE_INT_TYPE queueDepth, const NATIVE_INT_TYPE instance) {
    ArmDemoComponentBase::init(queueDepth, instance);
}

ArmDemo ::~ArmDemo(void) {}

// ----------------------------------------------------------------------
// Command handler implementations
// ----------------------------------------------------------------------

void ArmDemo ::AA_CLAW_ANG_cmdHandler(const FwOpcodeType opCode, const U32 cmdSeq, F32 angle) {
    // write to motor port
    this->position_out(CLAW_PORT, angle);
    // send event
    this->log_ACTIVITY_HI_AA_ClawAngleCmd(angle);
    // send telemetry
    this->tlmWrite_AA_ClawAngle(angle);
    // return command status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void ArmDemo ::AA_BASE_ANG_cmdHandler(const FwOpcodeType opCode, const U32 cmdSeq, F32 angle) {
    // write to motor port
    this->position_out(BASE_PORT, angle);
    // send event
    this->log_ACTIVITY_HI_AA_BaseAngleCmd(angle);
    // send telemetry
    this->tlmWrite_AA_BaseAngle(angle);
    // return command status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void ArmDemo ::AA_ARM_HEIGHT_ANG_cmdHandler(const FwOpcodeType opCode, const U32 cmdSeq, F32 angle) {
    // write to motor port
    this->position_out(ARM_HEIGHT_PORT, angle);
    // send event
    this->log_ACTIVITY_HI_AA_ArmHeightAngleCmd(angle);
    // send telemetry
    this->tlmWrite_AA_ArmHeightAngle(angle);
    // return command status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void ArmDemo ::AA_ARM_LENGTH_ANG_cmdHandler(const FwOpcodeType opCode, const U32 cmdSeq, F32 angle) {
    // write to motor port
    this->position_out(ARM_LENGTH_PORT, angle);
    // send event
    this->log_ACTIVITY_HI_AA_ArmLengthAngleCmd(angle);
    // send telemetry
    this->tlmWrite_AA_ArmLengthAngle(angle);
    // return command status
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void ArmDemo ::Run_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    this->tlmWrite_AA_Cycles(this->m_cycles++);
}

}  // end namespace RobotArm
