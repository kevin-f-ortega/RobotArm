import math

def main():
    """"
    Robotic Arm Sequence Generator Tool
    -----------------------------------

    Prints a valid Fprime sequence to STDOUT. Copy the generated sequence into the GDS to execute the sequence.

    Availble commands:
        - MOVE(sero, position)
            - Move a servo to a given position
            - Valid servos are: CLAW, BASE, ARM_HEIGHT, ARM_LENGTH
            - Position is rotation in degrees
            - Optional: settle_time_sec: Number of seconds to wait for move to complete
            - Examples:
                MOVE(BASE, 20.5)
                MOVE(ARM_HEIGHT, -30.3, settle_time_sec=2)
        - MOVE_MULTI(seros, positions)
            - Move multiple servos at the same time
            - Valid servos are: CLAW, BASE, ARM_HEIGHT, ARM_LENGTH
            - Position is rotation in degrees
            - Optional: settle_time_sec: Number of seconds to wait for move to complete
            - Examples:
                MOVE([BASE, ARM_LENGTH], [20.5, 50])
                MOVE([ARM_LENGTH, ARM_HEIGHT], [20.5, 50], settle_time_sec=2)
        - WAIT(duration_sec)
            - Wait specified number of seconds
            - Examples:
                WAIT(60)
        - PRINT_MESSAGE(msg)
            - Print message to the GDS
            - Examples:
                PRINT_MESSAGE("Hello Robotic Arm!") 
    """

    PRINT_MESSAGE("Hello Robotic Arm!")
    WAIT(70)
    MOVE(CLAW, 20.5)
    MOVE_MULTI([CLAW, BASE], [20.5, -50.1])
    return

def print_comment(comment):
    print(f"; {comment}")


def print_cmd(cmd, args=[], delay_sec=0):
    fmtd_args = []
    for arg in args:
        if isinstance(arg, str):
            cleaned_arg = arg.replace('"', "")
            if " " in cleaned_arg:
                fmtd_args.append(f'"{cleaned_arg}"')
        else:
            fmtd_args.append(str(arg))

    args_str = ", ".join(fmtd_args)
    delay_min = math.floor(delay_sec / 60)
    delay_sec_round = math.floor(delay_sec) % 60
    print(f"R00:{delay_min:02}:{delay_sec_round:02} {cmd} {args_str}")


CLAW = "clawServo"
BASE = "baseServo"
ARM_HEIGHT = "armHeightServo"
ARM_LENGTH = "armLengthServo"


def NO_OP(delay_sec=0):
    print_cmd("cmdDisp.CMD_NO_OP", delay_sec=delay_sec)


def PRINT_MESSAGE(msg, delay_sec=0):
    """send a message to the GDS"""

    print_cmd("cmdDisp.CMD_NO_OP_STRING", [msg], delay_sec)


def WAIT(duration_sec):
    """Delay sequence for specified duration"""

    PRINT_MESSAGE(f"Waiting {duration_sec} seconds")
    NO_OP(duration_sec)


def MOVE(servo, position, settle_time_sec=1):
    """
    Move provided sero to specified position

    Arguments:
        :param servo: The servo motor to move. Options: CLAW, BASE, ARM_HEIGHT, ARM_LENGTH
        :param position: The angle in degrees (-90 to 90) to move the servo.
        :param settle_time_sec: Duration in seconds to wait for the movement to complete before disabling servos
    """

    assert servo in [
        CLAW,
        BASE,
        ARM_HEIGHT,
        ARM_LENGTH,
    ], "Must provide a valid servo to MOVE: CLAW, BASE, ARM_HEIGHT, ARM_LENGTH"
    assert (
        position >= -90 and position <= 90
    ), "MOVE must command servo between -90 and 90 degrees"

    print_comment("-----")
    print_comment(f"Moving {servo} to {position} degrees")
    print_cmd(f"{servo}.PS_EN")
    print_cmd(f"{servo}.PS_ANG", args=[position])
    print_cmd(f"{servo}.PS_DIS", delay_sec=settle_time_sec)
    print_comment("-----")
    print()


def MOVE_MULTI(servos, positions, settle_time_sec=1):
    """
    Move multiple servos in parallel

    Arguments:
        :param servos: List of servo motor to move. Options: CLAW, BASE, ARM_HEIGHT, ARM_LENGTH
        :param positions: List of angles in degrees (-90 to 90) to move the servos.
        :param settle_time_sec: Duration in seconds to wait for the movement to complete before disabling servos
    """

    assert len(servos) == len(
        positions
    ), "Must provide a position for every servo that is being moved"
    assert len(servos) > 0, "Must provide at least one servo to move"

    for servo in servos:
        assert servo in [
            CLAW,
            BASE,
            ARM_HEIGHT,
            ARM_LENGTH,
        ], "Must provide a valid servo to MOVE: CLAW, BASE, ARM_HEIGHT, ARM_LENGTH"

    for position in positions:
        assert (
            position >= -90 and position <= 90
        ), "MOVE must command servo between -90 and 90 degrees"

    print_comment("-----")
    print_comment(f"Moving multiple joints:")
    for servo, position in zip(servos, positions):
        print_comment(f"  - {servo} to {position} degrees")
    for servo in servos:
        print_cmd(f"{servo}.PS_EN")
    for servo, position in zip(servos, positions):
        print_cmd(f"{servo}.PS_ANG", args=[position])
    print_cmd(f"{servos[0]}.PS_DIS", delay_sec=settle_time_sec)
    for servo in servos[1:]:
        print_cmd(f"{servo}.PS_DIS")
    print_comment("-----")
    print()


if __name__ == "__main__":
    main()
