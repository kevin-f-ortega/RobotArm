module RobotArm {

  @ Arm Demo App component
  active component ArmDemo {

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

    @ Servo position port
    output port position: [4] RobotArm.ServoSet

    @ Run port for starting packet send cycle
    async input port Run: Svc.Sched

    @ Claw angle command
    async command AA_CLAW_ANG(
                               angle: F32 @< The commanded angle
                             ) \
      opcode 0x0

    @ Base angle command
    async command AA_BASE_ANG(
                               angle: F32 @< The commanded angle
                             ) \
      opcode 0x1

    @ Arm height angle command
    async command AA_ARM_HEIGHT_ANG(
                                     angle: F32 @< The commanded angle
                                   ) \
      opcode 0x2

    @ Arm length angle command
    async command AA_ARM_LENGTH_ANG(
                                     angle: F32 @< The commanded angle
                                   ) \
      opcode 0x3

    @ Claw Angle commanded
    event AA_ClawAngleCmd(
                           angle: F32 @< The commanded angle
                         ) \
      severity activity high \
      id 0 \
      format "Claw commanded to {f}"

    @ Base Angle commanded
    event AA_BaseAngleCmd(
                           angle: F32 @< The commanded angle
                         ) \
      severity activity high \
      id 1 \
      format "Base commanded to {f}"

    @ Arm length commanded
    event AA_ArmLengthAngleCmd(
                                angle: F32 @< The commanded angle
                              ) \
      severity activity high \
      id 2 \
      format "Arm length commanded to {f}"

    @ Arm height angle commanded
    event AA_ArmHeightAngleCmd(
                                angle: F32 @< The commanded angle
                              ) \
      severity activity high \
      id 3 \
      format "Arm height commanded to {f}"

    @ Commanded angle
    telemetry AA_ClawAngle: F32 id 0

    @ Commanded angle
    telemetry AA_BaseAngle: F32 id 1

    @ Commanded angle
    telemetry AA_ArmHeightAngle: F32 id 2

    @ Commanded angle
    telemetry AA_ArmLengthAngle: F32 id 3

    @ Scheduler cycles
    telemetry AA_Cycles: U32 id 4

  }

}
