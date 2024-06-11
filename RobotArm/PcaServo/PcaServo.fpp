module RobotArm {

  @ Servo Component
  active component PcaServo {

    @ Command registration port
    command reg port cmdRegOut

    @ Command received port
    command recv port cmdIn

    @ Command response port
    command resp port cmdResponseOut

    @ Telemetry port
    telemetry port tlmOut

    @ Text event port
    text event port logTextOut

    @ Event port
    event port logOut

    @ Time get port
    time get port timeCaller

    @ Parameter get
    param get port prmGetOut

    @ Parameter set
    param set port prmSetOut

    @ servo position port
    async input port position: RobotArm.ServoSet

    @ I2C Port
    output port i2c: Drv.I2c

    @ Servo angle command
    async command PS_ANG(
                          angle: F32 @< The commanded angle
                        ) \
      opcode 0x0

    @ Disable servo board
    async command PS_DIS \
      opcode 0x1

    @ Enable servo board
    async command PS_EN \
      opcode 0x2

    @ FPP from XML: could not translate format string "Motor %d commanded to angle %f (0x%04X)"
    @ Angle commanded
    event PS_AngleCmd(
                       inst: U8 @< The motor instance
                       angle: F32 @< The commanded angle
                       $reg: U16 @< The register value
                     ) \
      severity activity high \
      id 0 \
      format "{} {} {}"

    @ Angle for position is out of bounds
    event PS_AngleIsOutOfBounds(
      angle: F32 @< The commanded angle
      minDegree: F32 @< Lower limit
      maxDegree: F32 @< Upper limit
    ) \
    severity warning low \
    id 1 \
    format "Commanded angle {} is not within bounds [{}, {}]"

    @ Commanded angle
    telemetry PS_Angle: F32 id 0

    @ FPP from XML: could not translate format string "0x%04X"
    @ Register value
    telemetry PS_Reg: U16 id 1

    @ Enable or Disable status of PcaServo
    telemetry PS_Enabled: Fw.Enabled id 2

    @ Parameter to control the lower limit of the servo
    param minDegree: F32 default -10.0 @< Lower limit in which the servo cannot pass

    @ Parameter to control the upper limit of the servo
    param maxDegree: F32 default 10.0 @< Upper limit in which the servo cannot pass

  }

}
