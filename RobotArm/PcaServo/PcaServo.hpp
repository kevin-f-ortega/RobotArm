// ======================================================================
// \title  PcaServo.hpp
// \author tcanham
// \brief  hpp file for PcaServo component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef PcaServo_HPP
#define PcaServo_HPP

#include "RobotArm/PcaServo/PcaServoComponentAc.hpp"
#include "RobotArm/PcaServo/PcaServoComponentImplCfg.hpp"
#include "Fw/Types/EnabledEnumAc.hpp"

namespace RobotArm {

  class PcaServo:
    public PcaServoComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object PcaServo
      //!
      PcaServo(
          const char *const compName /*!< The component name*/
      );

      //! Initialize chip. Should be only called once
      //! on one of the instances
      void configChip(void);

      //! Configure parameters
      //!
      void configure(
    		  U32 instance,  //!< servo instance on board
			  U32 addr //!< servo board address
			  );

      //! Destroy object PcaServo
      //!
      ~PcaServo(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for position
      //!
      void position_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 angle 
      );

      //! Implementation for PS_ANG command handler
      //! Servo angle command
      void PS_ANG_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 angle /*!< The commanded angle*/
      );

      //! Implementation for PS_DIS command handler
      //! Disable servo board
      void PS_DIS_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      //! Implementation for PS_EN command handler
      //! Enable servo board
      void PS_EN_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


      //! common position setter
      void setPos(F32 angle);

      //! private data
      U32 m_instance;
      U32 m_addr;
      U8 m_data[I2C_BUFFER_SIZE];
      Fw::Buffer m_buff;
      Fw::Enabled m_servoEnabled;
    };

} // end namespace RobotArm

#endif
